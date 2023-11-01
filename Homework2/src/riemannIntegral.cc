#include "riemannIntegral.hh"

RiemannIntegral::RiemannIntegral(double a, double b, std::function<double(double)> f, std::function<double(double)> integral_f)
    : a(a), b(b), f(f), integral_f(integral_f) {}

double RiemannIntegral::compute(unsigned int N) {
    if (N == 0) return 0.;

    double sum = 0.;
    double h = (b - a) / N;
    for (unsigned int i = 0; i < N; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

// If not provided, the function and the integration limits can be set with the following methods, otherwise not used
void RiemannIntegral::setFunction(std::function<double(double)> new_f) {
    f = new_f;
}

void RiemannIntegral::setLimits(double new_a, double new_b) {
    a = new_a;
    b = new_b;
}

double RiemannIntegral::getAnalyticPrediction(){
    return integral_f(b) - integral_f(a);
}; 