#ifndef LINEAR_SEARCH_HPP
#define LINEAR_SEARCH_HPP

#include <vector>
#include <algorithm>

template <typename T>
const static int linearSearch(const std::vector<T>& arr, const T& key) {
    auto it = std::find(arr.begin(), arr.end(), key);
    
    if (it != arr.end()) {
        return std::distance(arr.begin(), it);
    } else {
        return -1;
    }
}

#endif // LINEAR_SEARCH_HPP