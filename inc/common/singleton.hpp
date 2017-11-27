/**
 *  File: singleton.hpp
 *
 *  Description: Singleton base class
 */

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <cassert>
#include <memory>

template <typename T>
class singleton
{
protected:
    singleton() = default;
	~singleton() = default;

protected:
	//! Static instance of the class
	static std::shared_ptr<T> instance_;

public:
	/**
	 * @brief create instance
	 *
	 * @return reference to the instance
	 */
	static T & instance(void) noexcept
	{
		if (instance_ == nullptr) instance_ = std::make_shared<T>();
		assert(instance_);
		return (*instance_);
	}

	/**
	 * @brief create instance
	 *
	 * @return pointer to the instance
	 */
	static std::shared_ptr<T> instance_ptr(void) noexcept
	{
		if (instance_ == nullptr) instance_ = std::make_shared<T>();
		assert(instance_);
		return (instance_);
	}
};

template <class T> std::shared_ptr<T> singleton<T>::instance_ = nullptr;

#endif
