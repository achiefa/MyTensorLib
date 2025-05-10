#include <iostream>

#include "Tensor.h"

int main() {
  Tensor::Tensor<double> t1({100, 100, 100}, "a");
  Tensor::Tensor<double> t2({100, 100, 100}, "b");
  Tensor::Tensor<double> t3({100, 100, 100}, "c");

  //double data[100 * 100 * 100];
  std::unique_ptr<double[]> data(new double[100 * 100 * 100]);
  
  // Initialize tensors
  for (size_t i = 0; i < t1.size(); ++i) {
    t1[i] = i + 1;
    t2[i] = (i + 1) * 2;
    t3[i] = (i + 1) * 3;
    data[i] = (i + 1) * 4;
  }

  Tensor::Tensor<double, Tensor::SharedResourcePolicy> t4({100, 100, 100}, data.get(), "d");
  std::cout << t4[0] << std::endl;

  data[0] = 123132.0;
  std::cout << t4[0] << std::endl;

  t4[0] = 9999.9;
  std::cout << data[0] << std::endl;
  std::cout << t4[0] << std::endl;
  return 0;
}