#include "printSeries.hh"
#include <iostream>

PrintSeries::PrintSeries(Series & series, double frequency, int maxiter)
    : DumperSeries(series),  // Call the constructor of DumperSeries
      frequency(frequency),
      maxiter(maxiter) {};


void PrintSeries::dump() {
    std::cout << "Series: " << series.compute(10) << std::endl;
};