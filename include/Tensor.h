#pragma once

#include <memory>
#include <string>
#include <vector>

#include "TensorInterface.h"

#define TENSOR_SFINAE(POLICY) \
  template <typename RP = ResourcePolicy,\
  typename = std::enable_if_t<std::is_same<RP, POLICY>::value>>

namespace Tensor {

  /**
   * @brief Tensor class for multi-dimensional arrays
   * 
   * @tparam Scalar_ 
   * @tparam Index_ 
   * @tparam ResourcePolicy_ 
   * 
   * This class implements a multi-dimensional array (tensor).info
   * 
   * SFINAE (Substitution Failure Is Not An Error) is used to allow 
   * the use of different constructors for different resource policies.
   */
  template <typename Scalar_, typename Index_ = std::size_t, typename ResourcePolicy_ = UniqueResourcePolicy>
  class Tensor : public TensorInterface<Tensor<Scalar_, Index_, ResourcePolicy_>> {
    public:
      typedef Scalar_ Scalar;
      typedef Index_ Index;
      typedef ResourcePolicy_ ResourcePolicy;
      typedef typename ResourcePolicy::template ptr<Scalar> ScalarPtr;
      typedef TensorInterface<Tensor<Scalar_, Index_, ResourcePolicy_>> Base;

      // Metadata
      Scalar* data() const { return _data.get(); } // Do we want to expose this when it is a map?
      Index size() const { return _size; }
      Index rank() const { return _shape.size(); }
      std::vector<Index> shape() const {return _shape; }

      // Accessors
      Scalar& operator[](const Index& index) { return _data[index]; }
      const Scalar& operator[](const Index& index) const { return _data[index]; }

      // Access element by multi-dimensional indices
      Scalar& operator()(const std::vector<Index>& indices)
      {
        if (indices.size() != _shape.size())
          throw std::out_of_range("Number of indices does not match tensor dimensions.");

        return _data[_flattenIndex(indices)];
      }

      const Scalar& at(const std::vector<Index>& indices) {
        Index flattenIndex = _flattenIndex(indices);
        if (flattenIndex >= _size)
          throw std::runtime_error("Index out of range");
        return _data[flattenIndex];
      }

      // Constructors
      TENSOR_SFINAE(UniqueResourcePolicy)
      Tensor() : _size(0) {}

      TENSOR_SFINAE(UniqueResourcePolicy)
      Tensor(const std::vector<Index>& shape, const std::string& name = "")
        : Base(name),
          _size(utils::product(shape)),
          _data(std::make_unique<Scalar[]>(_size)), 
          _shape(shape)
      {
        if (_size == 0) {
          throw std::runtime_error("Tensor size cannot be zero.");
        }
      }

      TENSOR_SFINAE(UniqueResourcePolicy)
      Tensor(std::initializer_list<Index> shape)
        : Tensor(std::vector<Index>(shape)) 
      { /* do nothing */ }

      TENSOR_SFINAE(SharedResourcePolicy)
      Tensor(const std::vector<Index>& shape, Scalar* data, const std::string& name = "")
        : Base(name),
          _size(utils::product(shape)),
          _data(data), // No ownership transfer
          _shape(shape)
      {
        if (_size == 0) {
          throw std::runtime_error("Tensor size cannot be zero.");
        }
        std::cout << "SharedResourcePolicy constructor called" << std::endl;
      }

    private:
      Index                _size;
      ScalarPtr            _data;
      std::vector<Index>   _shape; // 8 bytes in 64-bit system

      Index _flattenIndex(const std::vector<Index>& indices) const {
        Index flatIndex = 0;
        Index stride = 1;
        // Implementing row-major order
        for (int i = _shape.size() - 1; i >= 0; --i) {
          flatIndex += stride * indices[i];
          stride *= _shape[i];
        }
        return flatIndex;
      }
  };

  // Specialization for Tensor
  template <typename Scalar_, typename Index_, typename ResourcePolicy_>
  struct TensorInfo<Tensor<Scalar_, Index_, ResourcePolicy_>> {
      
    typedef Scalar_ Scalar;
    typedef Index_ Index;
    typedef ResourcePolicy_ ResourcePolicy;
  };
  

}