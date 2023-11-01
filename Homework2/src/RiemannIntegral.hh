#ifndef RIEMANNINTEGRAL_HH
#define RIEMANNINTEGRAL_HH

#include "series.hh"
#include <functional>

class RiemannIntegral: public Series{

public:
    // Constructor
    RiemannIntegral(double a, double b, std::function<double(double)> f);

    // Destructor
    ~RiemannIntegral() {};

private:

    double a, b;
    std::function<double(double)> f;

public:
    double compute(unsigned int N) override;
    void setFunction(std::function<double(double)> new_f);
    void setLimits(double new_a, double new_b);

};

#endif