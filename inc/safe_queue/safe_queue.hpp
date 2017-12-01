/**
 * File: safe_queue.hpp
 *
 * Description: Thread-safe queue
*/

#ifndef SAFE_QUEUE_HPP_
#define SAFE_QUEUE_HPP_

#include <queue>
#include <list>
#include <mutex>
#include <thread>
#include <cstdint>
#include <condition_variable>


/** A thread-safe asynchronous queue */
template <class T, class container = std::list<T>>
class safe_queue
{
    typedef typename container::value_type value_type;
    typedef typename container::size_type size_type;
    typedef container container_type;

public:

    /*! Create safe queue. */
    safe_queue() = default;

    /*! Move constructor */
    safe_queue(safe_queue&& sq)
    {
        queue_ = std::move(sq.queue_);
    }

    /*! Copy constructor */
    safe_queue(const safe_queue& sq)
    {
        std::lock_guard<std::mutex> lock(sq.mutex_);
        queue_ = sq.queue_;
    }

    /*! Destroy safe queue. */
    ~safe_queue()
    {
        std::lock_guard<std::mutex> lock(mutex_);
    }

    /**
     * @brief Sets the maximum number of items in the queue. Defaults is 0: No limit
     * @param[in] item An item.
     */
    void set_max_num_items(unsigned int max_num_items)
    {
        max_num_items_ = max_num_items;
    }

    /**
     * @brief Pushes the item into the queue.
     * @param[in] item An item.
     * @return true if an item was pushed into the queue
     */
    bool push(const value_type& item)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (max_num_items_ > 0 && queue_.size() > max_num_items_)
        {
            return false;
        }

        queue_.push(item);
        condition_.notify_one();

        return true;
    }

    /**
     * @brief Pushes the item into the queue.
     * @param[in] item An item.
     * @return true if an item was pushed into the queue
     */
    bool push (const value_type&& item)
    {
        std::lock_guard<std::mutex>lock(mutex_);

        if (max_num_items_ > 0 && queue_.size() > max_num_items_)
        {
            return false;
        }

        queue_.push(item);
        condition_.notify_one();

        return true;
    }

    /**
     * @brief Pops item from the queue. If queue is empty, this function blocks until item becomes available.
     * @param[out] item The item.
     */
    void pop(value_type& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        condition_.wait(lock, [this]() { return !queue_.empty(); } );
        item = queue_.front();
        queue_.pop();
    }

    /**
     * @brief Pops item from the queue using the contained type's move assignment operator, if it has one..
     *  This method is identical to the pop() method if that type has no move assignment operator.
     *  If queue is empty, this function blocks until item becomes available.
     * @param[out] item The item.
     */
    void move_pop(value_type& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        condition_.wait(lock, [this]() { return !queue_.empty(); } );
        item = std::move(queue_.front());
        queue_.pop();
    }

    /**
     * @brief Tries to pop item from the queue.
     * @param[out] item The item.
     * @return False is returned if no item is available.
     */
    bool try_pop(value_type& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if (queue_.empty())
        {
            return false;
        }

        item = queue_.front();
        queue_.pop();

        return true;
    }

    /**
     * @brief Tries to pop item from the queue using the contained type's move assignment operator, if it has one..
     *  This method is identical to the try_pop() method if that type has no move assignment operator.
     * @param[out] item The item.
     * @return False is returned if no item is available.
     */
    bool try_move_pop(value_type& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if (queue_.empty())
        {
            return false;
        }

        item = std::move(queue_.front());
        queue_.pop();

        return true;
    }

    /**
     * @brief Pops item from the queue. If the queue is empty, blocks for timeout microseconds, or until item becomes available.
     * @param[out] t An item.
     * @param[in] timeout The number of microseconds to wait.
     * @return true if get an item from the queue, false if no item is received before the timeout.
     */
    bool timeout_pop(value_type& item, std::uint64_t timeout)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if (queue_.empty())
        {
            if (timeout == 0)
            {
                return false;
            }

            if (condition_.wait_for(lock, std::chrono::microseconds(timeout)) == std::cv_status::timeout)
            {
                return false;
            }
        }

        item = queue_.front();
        queue_.pop();

        return true;
    }

    /**
     *  @brief item from the queue using the contained type's move assignment operator, if it has one..
     *  If the queue is empty, blocks for timeout microseconds, or until item becomes available.
     *  This method is identical to the try_pop() method if that type has no move assignment operator.
     * @param[out] t An item.
     * @param[in] timeout The number of microseconds to wait.
     * @return true if get an item from the queue, false if no item is received before the timeout.
     */
    bool timeout_move_pop(value_type& item, std::uint64_t timeout)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if (queue_.empty())
        {
            if (timeout == 0)
            {
                return false;
            }

            if (condition_.wait_for(lock, std::chrono::microseconds(timeout)) == std::cv_status::timeout)
            {
                return false;
            }
        }

        item = std::move(queue_.front());
        queue_.pop();

        return true;
    }

    /**
     * @brief Gets the number of items in the queue.
     * @return Number of items in the queue.
     */
    size_type size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    /**
     * @brief Check if the queue is empty.
     * @return true if queue is empty.
     */
    bool empty() const
    {
        std::lock_guard<std::mutex>lock(mutex_);
        return queue_.empty();
    }

    /**
     * @brief Swaps the contents.
     * @param[out] sq The SafeQueue to swap with 'this'.
     */
    void swap(safe_queue& sq)
    {
        if (this != &sq)
        {
            std::lock_guard<std::mutex> lock1(mutex_);
            std::lock_guard<std::mutex> lock2(sq.mutex_);
            queue_.swap(sq.queue_);

            if (!queue_.empty())
            {
                condition_.notify_all();
            }

            if (!sq.queue_.empty())
            {
                sq.condition_.notify_all();
            }
        }
    }

    /*! The copy assignment operator */
    safe_queue& operator= (const safe_queue& sq)
    {
        if (this != &sq)
        {
            std::lock_guard<std::mutex> lock1(mutex_);
            std::lock_guard<std::mutex> lock2(sq.mutex_);
            std::queue<T, container> temp {sq.queue_};
            queue_.swap(temp);

            if (!queue_.empty())
            {
                condition_.notify_all();
            }
        }

        return *this;
    }

    /*! The move assignment operator */
    safe_queue& operator= (safe_queue && sq)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_ = std::move(sq.queue_);

        if (!queue_.empty())
        {
            condition_.notify_all();
        }

        return *this;
    }


private:

    std::queue<T, container> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    unsigned int max_num_items_ = 0;
};

/*! Swaps the contents of two SafeQueue objects. */
template <class T, class container>
void swap (safe_queue<T, container>& q1, safe_queue<T, container>& q2)
{
    q1.swap(q2);
}

#endif // SAFE_QUEUE_HPP_
