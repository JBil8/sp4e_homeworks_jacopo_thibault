#ifndef PRINTSERIES_HH
#define PRINTSERIES_HH

#include"series.hh"
#include"dumperSeries.hh"

class PrintSeries: public DumperSeries{
    
public:
    // Constructor
    PrintSeries(Series & series, int frequency, int maxiter);

    // Destructor
    ~PrintSeries() {};

private:
    int frequency;
    int maxiter;

public:
    void dump(std::ostream & os) override;
    void setPrecision(unsigned int precision) override;

};

#endif