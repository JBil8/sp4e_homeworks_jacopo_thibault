#include "printSeries.hh"
#include <iostream>

PrintSeries::PrintSeries(Series & series, int frequency, int maxiter)
    : DumperSeries(series),  // Call the constructor of DumperSeries
      frequency(frequency),
      maxiter(maxiter) {};

void PrintSeries::dump() {
    // std::cout << "Series dump:" << std::endl;
    std::cout << "Frequency: " << frequency << std::endl;
    std::cout << "Max iterations: " << maxiter << std::endl;

    for (int i = 1; i < maxiter+1; i += frequency) {
        std::cout << "Series value: " << series.compute(i) << std::endl;}
};