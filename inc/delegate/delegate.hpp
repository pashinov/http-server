/**
 * File: delegate.hpp
 *
 * Description:
 */

#ifndef DELEGATE_H_
#define DELEGATE_H_

#include <functional>
#include <map>

/**  */
template<typename... Args>
class delegate
{
public:
    /*! Create delegate */
    delegate() : id_(0) {};

    /*! Destroy delegate */
    ~delegate() = default;

    /**
     * @brief
     * @param
     * @return
     */
    std::uint64_t connect(std::function<void(Args...)> const & delegate) const noexcept
    {
        table_.insert(std::make_pair(++id_, delegate));
        return id_;
    }

    /**
     * @brief
     * @param
     */
    void disconnect(std::uint64_t delegate) const noexcept
    {
        table_.erase(delegate);
    }

    /**
     * @brief
     * @param
     */
    void call(Args... args) noexcept
    {
        for(const auto& it : table_)
        {
            it.second(args...);
        }
    }

private:
    //!
    mutable std::uint64_t id_;
    //!
    mutable std::map<std::uint64_t, std::function<void(Args...)>> table_;
};

/**  */
template<>
class delegate<void>
{
public:
    /*! Create delegate */
    delegate() : id_(0) {};

    /*! Destroy delegate */
    ~delegate() = default;

    /**
     * @brief
     * @param
     * @return
     */
    std::uint64_t connect(std::function<void()> const & delegate) const noexcept;

    /**
     * @brief
     * @param
     */
    void disconnect(std::uint64_t delegate) const noexcept;

    /**
     * @brief
     * @param
     */
    void call() noexcept;

private:
    //!
    mutable std::uint64_t id_;
    //!
    mutable std::map<std::uint64_t, std::function<void()>> table_;

};

#endif // DELEGATE_H_
