#include "simul.hpp"
#include <cmath>
#include <numeric>
#include <vector>

double mean(const std::vector<double> &data) {
  return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}
double desviacion(const std::vector<double> &data, double average) {
  double sum = 0;
  int i;
  double size = data.size();
  for (i = 0; i < size; i++) {
    sum += std::pow(data[i]-average,2);
  }
  double sigma;
  sigma = std::sqrt(sum / size);
  return sigma;
}
