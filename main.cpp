#include <iostream>

#include "Tensor.h"

int main() {
  Tensor::Tensor<double> t1({100, 100, 100}, "a");
  Tensor::Tensor<double> t2({100, 100, 100}, "b");
  Tensor::Tensor<double> t3({100, 100, 100}, "c");

  // Initialize tensors
  for (size_t i = 0; i < t1.size(); ++i) {
    t1[i] = i + 1;
    t2[i] = (i + 1) * 2;
    t3[i] = (i + 1) * 3;
  }
  
  return 0;
}