#pragma once
#include <numeric>

namespace Tensor {
  namespace utils {
    template <typename T1, typename T2>
    concept ConvertibleTo = std::convertible_to<T2,T1>;

    template <typename Iterable>
    static auto product(const Iterable& iterable) {
      return std::accumulate(iterable.begin(), iterable.end(), 1, std::multiplies<size_t>());
    }
  }
}