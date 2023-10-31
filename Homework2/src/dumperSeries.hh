#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH

#include"series.hh"

class DumperSeries{
public:
    DumperSeries(Series & series) : series(series) {}; // Constructor
    virtual void dump() = 0;
protected:
    Series & series;
};

#endif