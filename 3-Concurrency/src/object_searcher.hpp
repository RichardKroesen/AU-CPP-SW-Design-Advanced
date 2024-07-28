#ifndef OBJECT_SEARCHER_HPP
#define OBJECT_SEARCHER_HPP

#include <vector>
#include <algorithm>
#include <thread>
#include "synch_queue.hpp"

namespace SEARCHER
{

template <typename T>
class Finder {
public:
    Finder(const std::vector<T>& input) : arr(input) {}

    auto single_findAll(const T& key) {
        std::vector<T*> results;
        for (auto& elem : arr) {
            if (elem == key) {
                results.push_back(&elem);
            }
        }
        return results;
    }

    template <size_t NumTasks = 4>
    std::vector<T*> findAll(const T& key) {
        std::vector<T*> results;
        std::atomic<bool> solutionFound{false};
        std::mutex resultsMutex;

        std::vector<std::thread> threads;
        threads.reserve(NumTasks);

        size_t chunkSize = arr.size() / NumTasks;
        size_t remainder = arr.size() % NumTasks;

        auto searchTask = [this, &key, &results, &solutionFound, &resultsMutex](size_t start, size_t end) {
            for (size_t i = start; i < end && !solutionFound.load(); ++i) {
                if (arr[i] == key) {
                    std::lock_guard<std::mutex> lock(resultsMutex);
                    results.push_back(const_cast<T*>(&arr[i]));
                    solutionFound.store(true);
                    break;
                }
            }
        };

        size_t start = 0;
        for (size_t i = 0; i < NumTasks; ++i) {
            size_t end = start + chunkSize + (i < remainder ? 1 : 0);
            threads.emplace_back(searchTask, start, end);
            start = end;
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return results;
    }

private:
    std::vector<T> arr;
};

} // namespace SEARCHER
#endif // OBJECT_SEARCHER_HPP