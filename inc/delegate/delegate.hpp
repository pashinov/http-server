/**
 * File: delegate.hpp
 *
 * Description:
 */

#ifndef DELEGATE_H_
#define DELEGATE_H_

#include <functional>
#include <map>

/** Delegate for functions with valid arguments */
template<typename... Args>
class delegate
{
public:
    /*! Create delegate */
    delegate() : id_(0) {};

    /*! Destroy delegate */
    ~delegate() = default;

    /**
     * @brief Connect function
     * @param Delegated function
     * @return Identification number
     */
    std::uint32_t connect(std::function<void(Args...)> const & delegate) const noexcept
    {
        table_.insert(std::make_pair(++id_, delegate));
        return id_;
    }

    /**
     * @brief Disconnect function
     * @param Identification number
     */
    void disconnect(std::uint32_t id) const noexcept
    {
        table_.erase(id);
    }

    /**
     * @brief Calling a function
     * @param Arguments of the called function
     */
    void call(Args... args) noexcept
    {
        for(const auto& it : table_)
        {
            it.second(args...);
        }
    }

private:
    //! Identification number
    mutable std::uint32_t id_;
    //! Delegated function table
    mutable std::map<std::uint32_t, std::function<void(Args...)>> table_;
};

/** Delegate for functions with void arguments */
template<>
class delegate<void>
{
public:
    /*! Create delegate */
    delegate() : id_(0) {};

    /*! Destroy delegate */
    ~delegate() = default;

    /**
     * @brief Connect function
     * @param Delegated function
     * @return Identification number
     */
    std::uint32_t connect(std::function<void()> const & delegate) const noexcept;

    /**
     * @brief Disconnect function
     * @param Identification number
     */
    void disconnect(std::uint32_t delegate) const noexcept;

    /**
     * @brief Calling a function
     * @param Arguments of the called function
     */
    void call() noexcept;

private:
    //! Identification number
    mutable std::uint32_t id_;
    //! Delegated function table
    mutable std::map<std::uint32_t, std::function<void()>> table_;
};

#endif // DELEGATE_H_
