#include "thread_raii.hpp"

thread_raii::~thread_raii() noexcept
{
    if (thread_.joinable())
    {
        thread_raii::cancel();
    }
}

void thread_raii::cancel() noexcept
{
    token_.cancel();
    thread_.join();
}
