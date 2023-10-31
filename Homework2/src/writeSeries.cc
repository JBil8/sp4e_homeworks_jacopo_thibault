#include "writeSeries.hh"
#include <fstream>
#include <iostream>
#include <cmath>

WriteSeries::WriteSeries(Series &series, int maxiter, const std::string& filename) 
    : DumperSeries(series),  // Call the constructor of DumperSeries
      maxiter(maxiter),
      filename(filename),
      separator(" ") {};


void WriteSeries::setSeparator(std::string s) {
    if (!s.empty()) {
        this->separator = s;
    }
}


void WriteSeries::dump() {
    
    // Add the file extension to the filename based on the separator
    if (separator == ",") {
            filename += ".csv";
        } else if (separator == "|") {
            filename += ".psv";
        } else {
            filename += ".txt";
        }

    // Open the file
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write the series to the file
    double analytic_prediction = series.getAnalyticPrediction();
    file << "Iterations" << this->separator << "Series_Value" << this->separator << "Analytic_Prediction" << std::endl;
    
    /*
    if (!std::isnan(analytic_prediction)) {
        file << analytic_prediction << std::endl;
    } else {
        file << "Not available" << std::endl;
    }*/

    for (int i = 1; i < maxiter+1; i++) {
        double series_value = series.compute(i);
        file << i << this->separator << series_value << this->separator << analytic_prediction << std::endl;
    }

    file.close();

    std::cout << "Series written to file " << filename << std::endl;
}


