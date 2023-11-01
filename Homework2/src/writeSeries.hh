#ifndef WRITESERIES_HH
#define WRITESERIES_HH

#include"series.hh"
#include"dumperSeries.hh"
#include<string>

class WriteSeries: public DumperSeries{
public:
    WriteSeries(Series& series, int maxiter, const std::string& filename); // Constructor
    void dump(std::ostream &os) override;
    void setSeparator(std::string s);
    void setPrecision(unsigned int precision) override;
private:
    int maxiter;
    std::string filename;
    std::string separator;
};


#endif