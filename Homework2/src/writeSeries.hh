#ifndef WRITESERIES_HH
#define WRITESERIES_HH

#include "series.hh"      // Include the base class header file
#include "dumperSeries.hh" // Include the DumperSeries class header file
#include <string>

class WriteSeries : public DumperSeries {
public:
    // Constructor for WriteSeries, which takes a series, maximum iterations (maxiter), and a filename
    WriteSeries(Series & series, int maxiter, const std::string & filename);

    // Destructor for WriteSeries (empty implementation as no additional cleanup is needed)
    ~WriteSeries() {};
    
private:
    int maxiter;     // Maximum number of iterations
    std::string filename;   // Output filename
    std::string separator; // Separator for formatting output

public:
    // Override the dump function to write series data to the specified output stream
    void dump(std::ostream &os) override;

    // Function to set the separator for formatting output
    void setSeparator(std::string s);

    // Override the setPrecision function to set the precision for formatting output
    void setPrecision(unsigned int precision) override;
};

#endif
