#ifndef SYNCH_QUEUE_HPP
#define SYNCH_QUEUE_HPP

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>

template <typename T>
class SynchronizedQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(value);
        cv.notify_one();
    }

    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        while (q.empty()) {
            if (done) return false;
            cv.wait(lock);
        }
        
        if (q.empty()) return false;
        value = q.front();
        q.pop();
        return true;
    }

    void finish() {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
        cv.notify_all();
    }

private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
    bool done = false;
};

#endif // SYNCH_QUEUE_HPP