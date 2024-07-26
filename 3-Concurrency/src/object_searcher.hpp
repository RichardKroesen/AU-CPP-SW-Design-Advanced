#ifndef OBJECT_SEARCHER_HPP
#define OBJECT_SEARCHER_HPP

#include <vector>
#include <algorithm>
#include <thread>

namespace SEARCHER
{

template <typename T>
class Finder {
public:
    Finder(const std::vector<T>& input) : arr(input) {}

    template<uint8_t numThreads = 1>
    std::vector<T*> findAll(const T& key) {
        static_assert(numThreads > 0, "Number of threads must be greater than 0");
        
        std::vector<std::jthread> threads;
        std::vector<std::vector<T*>> results(numThreads);
        std::atomic<int> counter(0);

        auto worker = [&](int start, int end, int index) {
            for (int i = start; i < end; ++i) {
                if (arr[i] == key) {
                    results[index].push_back(&arr[i]);
                }
            }
            counter++;
        };

        const size_t segmentSize = arr.size() / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            int start = i * segmentSize;
            int end = (i == numThreads - 1) ? arr.size() : (i + 1) * segmentSize;
            threads.emplace_back(worker, start, end, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        while (counter.load() < numThreads);

        std::vector<T*> combinedResults;
        for (const auto& res : results) {
            combinedResults.insert(combinedResults.end(), res.begin(), res.end());
        }

        return combinedResults;
    }

private:
    std::vector<T> arr;
};

} // namespace SEARCHER
#endif // OBJECT_SEARCHER_HPP