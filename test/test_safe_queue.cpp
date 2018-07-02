#include <gtest/gtest.h>

#include <safe_queue/safe_queue.hpp>

TEST(SafeQueue, MainTest)
{
    safe_queue<std::string> queue1;

    bool ret = queue1.push("Test message1");
    ASSERT_EQ(ret, true);

    ret = queue1.push("Test message2");
    ASSERT_EQ(ret, true);

    safe_queue<std::string> queue2(queue1);

    std::string recv_msg;
    queue2.pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message1");
    queue2.pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message2");

    safe_queue<std::string> queue3;

    queue3 = queue1;
    queue3.pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message1");
    queue3.pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message2");

    safe_queue<std::string> queue4(std::move(queue1));

    queue4.pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message1");
    queue4.pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message2");

    safe_queue<std::string> queue5;

    ret = queue5.push("Test message1");
    ASSERT_EQ(ret, true);

    ret = queue5.push("Test message2");
    ASSERT_EQ(ret, true);

    safe_queue<std::string> queue6;
    queue6 = std::move(queue5);
    queue6.move_pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message1");
    queue6.move_pop(recv_msg);
    ASSERT_EQ(recv_msg, "Test message2");

    safe_queue<std::string> queue7;
    queue7.set_max_num_items(2);

    ret = queue7.push("Test message1");
    ASSERT_EQ(ret, true);

    ret = queue7.push("Test message2");
    ASSERT_EQ(ret, true);

    ret = queue7.push("Test message3");
    ASSERT_EQ(ret, false);

    std::string send_msg = "Test message3";
    ret = queue7.push(send_msg);
    ASSERT_EQ(ret, false);
}

TEST(SafeQueue, PushPop)
{
    safe_queue<std::string> queue;

    std::string send_msg = "Test message";
    bool ret = queue.push(send_msg);
    ASSERT_EQ(ret, true);

    std::string recv_msg;
    queue.pop(recv_msg);
    ASSERT_EQ(send_msg, recv_msg);
}

TEST(SafeQueue, MovePushPop)
{
    safe_queue<std::string> queue;

    bool ret = queue.push("Test message");
    ASSERT_EQ(ret, true);

    std::string recv_msg;
    queue.move_pop(recv_msg);
    ASSERT_EQ("Test message", recv_msg);
}

TEST(SafeQueue, TryPop)
{
    safe_queue<std::string> queue;

    bool ret = queue.push("Test message");
    ASSERT_EQ(ret, true);

    std::string recv_msg;
    ret = queue.try_pop(recv_msg);
    ASSERT_EQ(ret, true);
    ASSERT_EQ("Test message", recv_msg);

    ret = queue.try_pop(recv_msg);
    ASSERT_EQ(ret, false);
}

TEST(SafeQueue, TryMovePop)
{
    safe_queue<std::string> queue;

    bool ret = queue.push("Test message");
    ASSERT_EQ(ret, true);

    std::string recv_msg;
    ret = queue.try_move_pop(recv_msg);
    ASSERT_EQ(ret, true);
    ASSERT_EQ("Test message", recv_msg);

    ret = queue.try_move_pop(recv_msg);
    ASSERT_EQ(ret, false);
}

TEST(SafeQueue, TimeoutPop)
{
    safe_queue<std::string> queue;

    bool ret = queue.push("Test message");
    ASSERT_EQ(ret, true);

    std::string recv_msg;
    ret = queue.timeout_pop(recv_msg, 0);
    ASSERT_EQ(ret, true);
    ASSERT_EQ("Test message", recv_msg);

    ret = queue.timeout_pop(recv_msg, 0);
    ASSERT_EQ(ret, false);

    ret = queue.timeout_pop(recv_msg, 100);
    ASSERT_EQ(ret, false);
}

TEST(SafeQueue, TimeoutMovePop)
{
    safe_queue<std::string> queue;

    bool ret = queue.push("Test message");
    ASSERT_EQ(ret, true);

    std::string recv_msg;
    ret = queue.timeout_move_pop(recv_msg, 0);
    ASSERT_EQ(ret, true);
    ASSERT_EQ("Test message", recv_msg);

    ret = queue.timeout_move_pop(recv_msg, 0);
    ASSERT_EQ(ret, false);

    ret = queue.timeout_move_pop(recv_msg, 100);
    ASSERT_EQ(ret, false);
}