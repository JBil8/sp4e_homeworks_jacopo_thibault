#ifndef DUMPERSERIES_HH
#define DUMPERSERIES_HH

#include "series.hh" // Include the base class header file
#include <iostream>

class DumperSeries {
public:
    // Constructor
    DumperSeries(Series & series, unsigned int precision = 4)
        : series(series), precision(precision) {};
    // Destructor
    virtual ~DumperSeries() {};

protected:
    Series & series;        // Reference to the series object
    unsigned int precision; // The precision for formatting output

public:
    // Virtual function to dump series data to the specified output stream
    virtual void dump(std::ostream & os) = 0;
    
    // Function to set the precision for formatting output
    virtual void setPrecision(unsigned int precision);
};

// Non-member function that allows using << to dump series data to an output stream
inline std::ostream & operator<<(std::ostream & stream, DumperSeries & _this) {
    _this.dump(stream);
    return stream;
};

#endif
