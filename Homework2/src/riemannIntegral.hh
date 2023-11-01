#ifndef RIEMANNINTEGRAL_HH
#define RIEMANNINTEGRAL_HH

#include "series.hh"      // Include the base class header file
#include <functional>

class RiemannIntegral : public Series {
public:
    // Constructor for RiemannIntegral, which takes lower bound (a), upper bound (b), and functions f and integral_f
    RiemannIntegral(double a, double b, std::function<double(double)> f, std::function<double(double)> integral_f);

    // Destructor for RiemannIntegral (empty implementation as no additional cleanup is needed)
    ~RiemannIntegral() {};

private:
    double a;                               // Lower bound
    double b;                               // Upper bound
    std::function<double(double)> f;        // Function to integrate
    std::function<double(double)> integral_f; // Integral of the function

public:
    // Override the compute function to calculate the Riemann integral up to the specified number of iterations (N)
    double compute(unsigned int N) override;

    // Function to set a new function to integrate
    void setFunction(std::function<double(double)> new_f);

    // Function to set new limits for integration
    void setLimits(double new_a, double new_b);

    // Override the getAnalyticPrediction function to return the analytic prediction of the integral
    double getAnalyticPrediction() override;
};

#endif
