#include "RiemannIntegral.hh"

RiemannIntegral::RiemannIntegral(double a, double b, std::function<double(double)> f)
    : a(a), b(b), f(f) {}

double RiemannIntegral::compute(unsigned int N) {
    if (N == 0) return 0.;

    double sum = 0.;
    double h = (b - a) / N;
    for (unsigned int i = 0; i < N; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

void RiemannIntegral::setFunction(std::function<double(double)> new_f) {
    f = new_f;
}

void RiemannIntegral::setLimits(double new_a, double new_b) {
    a = new_a;
    b = new_b;
}