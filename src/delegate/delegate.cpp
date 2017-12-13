#include <delegate.hpp>

//////////////////////////////////////////////////////////////////////////
std::uint64_t delegate<void>::connect(std::function<void()> const & delegate) const noexcept
{
    table_.insert(std::make_pair(id_, delegate));
    return id_;
}

//////////////////////////////////////////////////////////////////////////
void delegate<void>::disconnect(std::uint64_t delegate) const noexcept
{
    table_.erase(delegate);
}

//////////////////////////////////////////////////////////////////////////
void delegate<void>::call() noexcept
{
    for(const auto& it : table_)
    {
        it.second();
    }
}
