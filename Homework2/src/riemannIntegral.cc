#include "riemannIntegral.hh"

// Constructor for RiemannIntegral, initializes the object with lower bound (a), upper bound (b), function f, and integral_f
RiemannIntegral::RiemannIntegral(double a, double b, std::function<double(double)> f, std::function<double(double)> integral_f)
    : a(a), b(b), f(f), integral_f(integral_f) {}

// Implementation of the compute function for Riemann integral calculation
double RiemannIntegral::compute(unsigned int N) {
    if (N == 0) return 0.;

    double sum = 0.;
    double h = (b - a) / N;
    for (unsigned int i = 0; i < N; i++) {
        sum += f(a + i * h);
    }
    return h * sum; // Return the Riemann integral approximation
}

// Function to set a new function to integrate
void RiemannIntegral::setFunction(std::function<double(double)> new_f) {
    f = new_f;
}

// Function to set new integration limits
void RiemannIntegral::setLimits(double new_a, double new_b) {
    a = new_a;
    b = new_b;
}

// Implementation of the getAnalyticPrediction function, returning the analytic prediction of the integral
double RiemannIntegral::getAnalyticPrediction(){
    return integral_f(b) - integral_f(a); // Calculate the integral prediction using provided integral functions
}
