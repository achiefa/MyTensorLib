#include <memory>

namespace Tensor {

  class SharedResourcePolicy {
    public:
      template <typename T>
      using ptr = std::shared_ptr<T>;
  };

  class UniqueResourcePolicy {
    public:
      template <typename T>
      using ptr = std::unique_ptr<T>;
  };

}