#include"computeArithmetic.hh"
#include<cmath>

double ComputeArithmetic::compute(unsigned int N) {
    for(unsigned int i=this->current_index; i<N+1; ++i){
        this->current_value +=i;
        this->current_index +=1;    
    }
    return this->current_value;
}

double ComputeArithmetic::getAnalyticPrediction() {
    return nan("");
}