#ifndef PRINTSERIES_HH
#define PRINTSERIES_HH

#include"series.hh"
#include"dumperSeries.hh"

class PrintSeries: public DumperSeries{
public:
    PrintSeries(Series & series, double frequency, int maxiter);
    void dump() override;
private:
    double frequency;
    int maxiter;
};

#endif