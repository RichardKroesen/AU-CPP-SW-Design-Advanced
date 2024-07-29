#include <gtest/gtest.h>
#include <chrono>
#include <random>

#include "../src/synch_queue.hpp" // CUD

TEST(Queue_Test, Test1) {
    SynchronizedQueue<int> q;
    int value = 0;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    q.pop(value);
    EXPECT_EQ(value, 1);

    q.pop(value);
    EXPECT_EQ(value, 2);

    q.pop(value);
    EXPECT_EQ(value, 3);

    q.pop(value);
    EXPECT_EQ(value, 4);

    q.pop(value);
    EXPECT_EQ(value, 5);
}

TEST(Queue_Test, Test2) {
    SynchronizedQueue<int> q;

    std::jthread producer([&q] {
        for (int i = 0; i < 100; ++i) {
            q.push(i);
        }
    });

    q.finish(); // Notify all consumers that the queue is done

    std::jthread consumer([&q] {
        int value = 0;
        for (int i = 0; i < 100; ++i) {
            q.pop(value);
            EXPECT_EQ(value, i);
        }
    });

    producer.join();
    consumer.join();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}