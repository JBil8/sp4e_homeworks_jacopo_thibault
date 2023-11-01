#include "printSeries.hh"
#include <iostream>
#include <iomanip>
#include <cmath>

PrintSeries::PrintSeries(Series & series, int frequency, int maxiter)
    : DumperSeries(series, 4),  // Call the constructor of DumperSeries
      frequency(frequency),
      maxiter(maxiter) {};

void PrintSeries::dump(std::ostream &os = std::cout)  {
    if (!precision) {
        os << "Precision not set." << std::endl;
    } else {
        os << "Precision: " << precision << std::endl;
        PrintSeries::setPrecision(precision);
        os << std::setprecision(this->precision);
    }
    os << "Frequency: " << frequency << std::endl;
    os << "Max iterations: " << maxiter << std::endl;

    double analytic_prediction = series.getAnalyticPrediction();

    /* if (!std::isnan(analytic_prediction)) {
        std::cout << "Analytic prediction: " << analytic_prediction << std::endl;
    } else {
        std::cout << "Analytic prediction is not available." << std::endl;
    } */

    for (int i = 1; i < maxiter+1; i += frequency) {
        double series_value = series.compute(i);
        os << "Series value at iteration " << i << ": " << series_value;

        if (!std::isnan(analytic_prediction)) {
            double convergence = std::abs(series_value - analytic_prediction);
            os << " | Convergence: " << convergence << std::endl;
        }
    }
};

void PrintSeries::setPrecision(unsigned int precision){
    this->precision = precision;
};