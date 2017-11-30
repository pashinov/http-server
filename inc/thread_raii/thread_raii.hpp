/**
 * File: raii_thread.hpp
 *
 * Description: RAII std::thread
 */

#ifndef RAII_THREAD_H_
#define RAII_THREAD_H_

#include <atomic>
#include <thread>

class cancellation_token
{
public:
    cancellation_token() : cancelled_(false) {};
    ~cancellation_token() = default;

    /**
     * @brief TODO
     */
	explicit operator bool() const { return !cancelled_; };

    /**
     * @brief TODO
     */
    void cancel() { cancelled_ = true; };

private:
    //!
    std::atomic<bool> cancelled_;
};

class thread_raii
{
public:
    /**
     * @brief start thread
     */
    template <typename Function, typename... Args>
    thread_raii(Function&& f, Args&&... args) noexcept;

    /**
     * @brief join thread
     */
    ~thread_raii() noexcept;

    /**
     * @brief correct termination thread
     */
    void cancel() noexcept;

    thread_raii(const thread_raii& copy) = delete;
    thread_raii& operator=(const thread_raii& copy) = delete;

private:
    //! TODO
    std::thread thread_;

    //! TODO
    cancellation_token token_;
};

template <typename Function, typename... Args>
thread_raii::thread_raii(Function&& f, Args&&... args) noexcept
{
    thread_ = std::thread(std::forward<Function>(f), std::ref(token_), std::forward<Args>(args)...);
}

#endif // RAII_THREAD_H_
