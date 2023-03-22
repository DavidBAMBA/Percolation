#include "simul.hpp"
#include <vector>
#include <random>
#include <iostream>



int main(int argc, char **argv)
{
  int l = std::atoi(argv[1]);
  double p = std::atof(argv[2]); // la probabilidad
  const int  j= std::atoi(argv[3]) ;
  int dim=j*10;
  // Creación de la matriz extendida llena de ceros
  Eigen::MatrixXi malla(l+2,l+2);
  std::vector<double> tamanos(dim,0);
  std::vector<double> probability(j,0);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution dis(p);
  int   k, perlocal;
  std::vector<double> existence(10,0);
  for(int i=0; i <j ; i++){
    for (k = 0; k < 10; k++) {
       malla.setZero();
      // LLenado aleatorio de la matriz LxL con una distribucion Bernoulli
    malla.block(1,1,l,l) = Eigen::MatrixXi::Zero(l,l).unaryExpr([&](int){return dis(gen)? 1 : 0;});
        perlocal=Big_Perco_size(l,malla);
        if (perlocal > 0) {
          existence[k] = 1;
          tamanos[i*10+k] = perlocal/(l*l*1.0);
        }
        else  existence[k] = 0;}
        probability[i]=mean(existence);
  }
   std::cout.setf(std::ios::fixed);
      std::cout.precision(2);
      std::cout << l  << "\t" << p << "\t";
      std::cout.precision(6);
      double prom= mean(tamanos);
      double promprob=mean(probability);
      std::cout<< prom << "\t"<< desviacion(tamanos, prom) << "\t" << promprob << "\t"
               << desviacion(probability, promprob) << "\n";
      return 0;
}
