#include"computeArithmetic.hh"

double ComputeArithmetic::compute(unsigned int N) {
    double result=0;
    for(double i=0.; i<N; ++i){
        result +=i;
    }
    return result;
}