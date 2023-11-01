#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH

#include"series.hh"
#include <iostream>

class DumperSeries{
public:
    DumperSeries(Series & series, unsigned int precision) : series(series), precision(4) {}; // Constructor
    //virtual void dump() = 0;
    virtual void dump(std::ostream & os) = 0;
    virtual void setPrecision(unsigned int precision);
    virtual ~DumperSeries() {};
protected:
    Series & series;
    unsigned int precision;
};

// Non-member function
inline std::ostream & operator <<(std::ostream & stream, DumperSeries & _this) {
    _this.dump(stream);
    return stream;};

#endif