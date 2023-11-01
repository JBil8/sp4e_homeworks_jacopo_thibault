#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH

#include"series.hh"
#include <iostream>

class DumperSeries{

public:
    // Constructor
    DumperSeries(Series & series, unsigned int precision = 4)
        : series(series), precision(precision) {}; 
    // Destructor
    virtual ~DumperSeries() {};

protected:
    Series & series;
    unsigned int precision;

public:
    virtual void dump(std::ostream & os) = 0;
    virtual void setPrecision(unsigned int precision);

};

// Non-member function
inline std::ostream & operator <<(std::ostream & stream, DumperSeries & _this) {
    _this.dump(stream);
    return stream;};

#endif