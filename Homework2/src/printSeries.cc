#include "printSeries.hh"
#include <iostream>
#include <cmath>

PrintSeries::PrintSeries(Series & series, int frequency, int maxiter)
    : DumperSeries(series),  // Call the constructor of DumperSeries
      frequency(frequency),
      maxiter(maxiter) {};

void PrintSeries::dump() {
    std::cout << "Frequency: " << frequency << std::endl;
    std::cout << "Max iterations: " << maxiter << std::endl;

    double analytic_prediction = series.getAnalyticPrediction();

    /* if (!std::isnan(analytic_prediction)) {
        std::cout << "Analytic prediction: " << analytic_prediction << std::endl;
    } else {
        std::cout << "Analytic prediction is not available." << std::endl;
    } */

    for (int i = 1; i < maxiter+1; i += frequency) {
        double series_value = series.compute(i);
        std::cout << "Series value at iteration " << i << ": " << series_value;

        if (!std::isnan(analytic_prediction)) {
            double convergence = std::abs(series_value - analytic_prediction);
            std::cout << " | Convergence: " << convergence << std::endl;
        }
    }
};