#ifndef PRINTSERIES_HH
#define PRINTSERIES_HH

#include"series.hh"
#include"dumperSeries.hh"

class PrintSeries: public DumperSeries{
public:
    PrintSeries(Series & series, int frequency, int maxiter);
    void dump(std::ostream & os) override;
    void setPrecision(unsigned int precision) override;

private:
    int frequency;
    int maxiter;
};

#endif