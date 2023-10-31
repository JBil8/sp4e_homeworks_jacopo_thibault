#ifndef COMPUTEPI_HH
#define COMPUTEPI_HH

#include"series.hh"

class ComputePi: public Series{
public:
    double compute(unsigned int N) override;
    double getAnalyticPrediction() override;
};

#endif