#include "writeSeries.hh"
#include <fstream>
#include <iostream>
#include <cmath>

WriteSeries::WriteSeries(Series & series, int maxiter, const std::string& filename) 
    : DumperSeries(series),  // Call the constructor of DumperSeries
      maxiter(maxiter),
      filename(filename) {};

void WriteSeries::dump() {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    double analytic_prediction = series.getAnalyticPrediction();
    file << "Analytic prediction: ";
    if (!std::isnan(analytic_prediction)) {
        file << analytic_prediction << std::endl;
    } else {
        file << "Not available" << std::endl;
    }

    for (int i = 1; i < maxiter+1; i++) {
        double series_value = series.compute(i);
        file << "Series value at iteration " << i << ": " << series_value << std::endl;
    }

    file.close();

    std::cout << "Series written to file " << filename << std::endl;
}