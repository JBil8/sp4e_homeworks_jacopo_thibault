#include <cmath>
#include "computePi.hh"

// Function to compute an approximation of Pi using the specified number of iterations (N)
double ComputePi::compute(unsigned int N) {
    for (unsigned int i = this->current_index; i <= N; ++i) {
        this->current_value += 6.0 / (i * i);
        this->current_index += 1;
    }

    return sqrt(this->current_value); // Return the square root of the accumulated value as an approximation of Pi
}

// Function to get the actual value of Pi (M_PI is defined in the cmath library)
double ComputePi::getAnalyticPrediction() {
    return M_PI; // Return the constant value of Pi (π) from the cmath library
}
