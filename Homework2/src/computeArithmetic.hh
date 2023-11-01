#ifndef COMPUTEARITHMETIC_HH
#define COMPUTEARITHMETIC_HH

#include"series.hh"


class ComputeArithmetic: public Series{
public:
    double compute(unsigned int N) override;
    double getAnalyticPrediction() override;
};

#endif