#pragma once
#include <queue>
#include <tuple>
#include <cmath>
#include <cstdlib>
#include <random>
#include <iostream>
#include <Eigen/Dense>
std::tuple<int,bool> Perco_size(int i,int j, Eigen::MatrixXi M);
int Big_Perco_size(int L,Eigen::MatrixXi &M);
double mean(const std::vector<double> &data);
double desviacion(const std::vector<double> &data, double average);
