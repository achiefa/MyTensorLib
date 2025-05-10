#pragma once

#include <string>
#include <vector>

#include "ResourcePolicy.h"
#include "TensorInfo.h"
#include "utils.h"

namespace Tensor {

  template <typename T>
  struct TensorInfo;

  // Implementation using CRTP
  template <typename Derived>
  class TensorInterface {
    public:
      // ====== Type definitions ======
      typedef TensorInfo<Derived> DerivedInfo;
      typedef typename DerivedInfo::Scalar Scalar;
      typedef typename DerivedInfo::Index Index;

      const Derived& derived() const 
      {
        return static_cast<const Derived&>(*this);
      }

      std::string name() const { return _name; }

    protected:
      TensorInterface(const std::string& name) : _name(name) {}
      TensorInterface(const TensorInterface&) = default;
      ~TensorInterface() = default;

      // Assignment operator from expression
      // template <typename OtherExpr>
      // Derived& operator=(const OtherExpr& expr) {
      //   std::cout << "DynamicTensor::operator= <OtherExpr>" << std::endl;
      //   TensorEvalManager<OtherExpr>::run(expr);
      //   return *this;
      // }

      std::string _name;
  };

}