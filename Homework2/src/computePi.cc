#include <cmath>
#include"computePi.hh"

double ComputePi::compute(unsigned int N) {
    for (unsigned int i = this->current_index; i <= N; ++i) {
        this->current_value += 6.0 / (i * i);
        this->current_index += 1;
    }

    return sqrt(this->current_value);
}

double ComputePi::getAnalyticPrediction() {
    return M_PI;
}