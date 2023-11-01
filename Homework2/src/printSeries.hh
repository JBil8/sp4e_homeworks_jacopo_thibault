#ifndef PRINTSERIES_HH
#define PRINTSERIES_HH

#include "series.hh"      // Include the base class header file
#include "dumperSeries.hh" // Include the DumperSeries class header file

class PrintSeries : public DumperSeries {
public:
    // Constructor for PrintSeries, which takes a series, frequency, and maxiter as parameters
    PrintSeries(Series & series, int frequency, int maxiter);

    // Destructor for PrintSeries (empty implementation as no additional cleanup is needed)
    ~PrintSeries() {};

private:
    int frequency; // Frequency of dumping
    int maxiter;   // Maximum number of iterations

public:
    // Override the dump function to print series data to the specified output stream (e.g., std::ostream)
    void dump(std::ostream & os) override;

    // Override the setPrecision function to set the precision for formatting output
    void setPrecision(unsigned int precision) override;
};

#endif
