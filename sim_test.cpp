#include <math.h>
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch2/catch.hpp"
#include "simul.hpp"
#include <cmath>
#include <numeric>
#include <vector>
#include <Eigen/Dense>

TEST_CASE("test operaciones de percolacion", "[classic]") {
    int i,j;
    int lo=100;
    Eigen::MatrixXi  zeros ((lo+2),(2+lo));
    zeros.block(1,1,lo,lo) = Eigen::MatrixXi::Zero(lo,lo);
    int l1=75;
    Eigen::MatrixXi unos ((2+l1),(l1+2));
    unos.setZero();
    for(i=1;i<=l1; i++){
        for(j=1;j <= l1; j++){
            unos(i,j)=1;
        }
    }
    int l2=60;
    Eigen::MatrixXi threelines ((l2+2),(l2+2));
    threelines.setZero();
    for ( i=1;i<=l2;i++){
        threelines(i,i)=1;}
    for ( i=1;i <l2;i++){
        threelines(i,(i+1))=1;
        threelines((i+1),i)=1;}

    Eigen::MatrixXi threelineshor ((l2+2),(l2+2));
    threelineshor.setZero();
    for ( i=2;i<=l2;i++){
        threelineshor(i,i)=1;}
    for ( i=2;i <l2;i++){
        threelineshor(i,(i+1))=1;}
    for ( i=1;i <l2;i++){
        threelineshor((i+1),i)=1;}

    int l3=5;
   Eigen::MatrixXi tee ((l3+2),(l3+2));
   tee.setZero();
    for ( i=1;i<=l3;i++){
        tee(3,i)=1;}
    for ( i=1;i <l3;i++){
        tee(i,2)=1;}


    Eigen::MatrixXi  cross ((l2+2),(l2+2));
    cross.setZero();
    for ( i=1;i<=l2;i++){
        cross(19,i)=1;}
    for ( i=1;i <=l2;i++){
        cross(i,20)=1;}

     int l4 = 6;
    Eigen::MatrixXi m_do(l4+2,l4+2);
    m_do.setZero();
    m_do.block(1,1,l4,l4) << 1,0,1,0,0,1,
                             1,0,1,0,0,1,
                             1,0,1,1,0,1,
                             1,0,1,1,0,1,
                             1,0,1,0,1,1,
                             1,0,1,1,0,1;
    // Verificar que para la tanspuesta tambien toma el más grande
    Eigen::MatrixXi m_doT= m_do.transpose();

    REQUIRE(Big_Perco_size(lo, zeros)==0);
    REQUIRE(Big_Perco_size(l1, unos)==l1*l1);
    REQUIRE(Big_Perco_size(l2, threelines)==l2+2*(l2-1));
    REQUIRE(Big_Perco_size(l2, threelineshor)==(l2+2*(l2-1)-2));
    REQUIRE(Big_Perco_size(l3, tee)==8);
    REQUIRE(Big_Perco_size(l2, cross)==2*l2-1);
    REQUIRE(Big_Perco_size(l4, m_do)==9);
    REQUIRE(Big_Perco_size(l4, m_doT)==9);
}
