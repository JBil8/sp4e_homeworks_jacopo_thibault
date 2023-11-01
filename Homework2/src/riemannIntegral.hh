#ifndef RIEMANNINTEGRAL_HH
#define RIEMANNINTEGRAL_HH

#include "series.hh"
#include <functional>

class RiemannIntegral: public Series{

public:
    // Constructor
    RiemannIntegral(double a, double b, std::function<double(double)> f, std::function<double(double)> integral_f);

    // Destructor
    ~RiemannIntegral() {};

private:
    double a, b;
    std::function<double(double)> f;
    std::function<double(double)> integral_f;
    

public:
    double compute(unsigned int N) override;
    void setFunction(std::function<double(double)> new_f);
    void setLimits(double new_a, double new_b);
    double getAnalyticPrediction() override;
};

#endif