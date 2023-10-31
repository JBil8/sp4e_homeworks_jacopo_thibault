#include <cmath>
#include"computePi.hh"

double ComputePi::compute(unsigned int N) {
    double result=0;
    for (int i = 1; i <= N; ++i) {
        result += 1.0 / (i * i);
    }

    result *= 6;
    result = sqrt(result);
    return result;
}

double ComputePi::getAnalyticPrediction() {
    return M_PI;
}