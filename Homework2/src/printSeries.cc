#include "printSeries.hh"
#include <iostream>
#include <iomanip>
#include <cmath>

// Constructor for PrintSeries, initializes the PrintSeries object with a series, frequency, and maxiter
PrintSeries::PrintSeries(Series & series, int frequency, int maxiter)
    : DumperSeries(series),  // Call the constructor of DumperSeries
      frequency(frequency),
      maxiter(maxiter) {};

// Implementation of the dump function, responsible for printing series data
void PrintSeries::dump(std::ostream &os)  {
    
    // Check if precision is not set and print a message if it's not
    if (!precision) {
        os << "Precision not set." << std::endl;
    } else {
        // Print the set precision and apply it to the output stream
        os << "Precision: " << precision << std::endl;
        PrintSeries::setPrecision(precision);
        os << std::setprecision(this->precision);
    }

    // Print the frequency and maximum number of iterations
    os << "Frequency: " << frequency << std::endl;
    os << "Max iterations: " << maxiter << std::endl;

    // Get the analytic prediction from the series object
    double analytic_prediction = series.getAnalyticPrediction();

    // Check if an analytic prediction is available and print it
    if (!std::isnan(analytic_prediction)) {
        std::cout << "Analytic prediction: " << analytic_prediction << std::endl;
    } else {
        std::cout << "Analytic prediction is not available." << std::endl;
    }

    // Iterate over iterations up to maxiter with the specified frequency
    for (int i = 1; i < maxiter + 1; i += frequency) {
        // Compute the series value at the current iteration
        double series_value = series.compute(i);
        os << "Series value at iteration " << i << ": " << series_value;

        // Calculate and print the convergence if an analytic prediction is available
        if (!std::isnan(analytic_prediction)) {
            double convergence = std::abs(series_value - analytic_prediction);
            os << " | Convergence: " << convergence << std::endl;
        } else {
            os << std::endl;
        }
    }
};

// Implementation of the setPrecision function to set the precision for formatting output
void PrintSeries::setPrecision(unsigned int precision){
    this->precision = precision;
};
