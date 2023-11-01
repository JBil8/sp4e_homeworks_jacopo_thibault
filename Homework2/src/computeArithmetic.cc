#include "computeArithmetic.hh"
#include <cmath>

// Function to compute an arithmetic series sum up to the specified number of iterations (N)
double ComputeArithmetic::compute(unsigned int N) {
    for (unsigned int i = this->current_index; i <= N; ++i) {
        this->current_value += i; // Add the current index to the accumulated value
        this->current_index += 1; // Increment the current index
    }
    return this->current_value; // Return the computed arithmetic sum
}

// Function to get the analytic prediction, which is set to NaN (not-a-number)
double ComputeArithmetic::getAnalyticPrediction() {
    return nan(""); // Return NaN as the analytic prediction
}
