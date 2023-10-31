#ifndef WRITESERIES_HH
#define WRITESERIES_HH

#include"series.hh"
#include"dumperSeries.hh"
#include<string>

class WriteSeries: public DumperSeries{
public:
    WriteSeries(Series& series, int maxiter, const std::string& filename);
    void dump() override;
private:
    int maxiter;
    std::string filename;
};


#endif