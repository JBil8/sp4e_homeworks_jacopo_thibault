#include "writeSeries.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

// Constructor for WriteSeries, initializes the object with a series, maximum iterations (maxiter), and a filename
WriteSeries::WriteSeries(Series &series, int maxiter, const std::string &filename) 
    : DumperSeries(series),  // Call the constructor of DumperSeries
      maxiter(maxiter),
      filename(filename),
      separator(" ") {};

// Function to set the separator for formatting output
void WriteSeries::setSeparator(std::string s) {
    if (!s.empty()) {
        this->separator = s;
    }
}

// Function to set the precision for formatting output
void WriteSeries::setPrecision(unsigned int precision){
    this->precision = precision;
}

// Implementation of the dump function, responsible for writing series data to the specified output stream (e.g., a file)
void WriteSeries::dump(std::ostream &os) {
    
    // Open the file for writing
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Get the analytic prediction from the series object
    double analytic_prediction = series.getAnalyticPrediction();

    // Write column headers to the file
    file << "Iterations" << this->separator << "Series_Value" << this->separator << "Analytic_Prediction" << std::endl;

    // Set the precision for output
    if (precision) {
        WriteSeries::setPrecision(precision);
        file << std::setprecision(this->precision);
    }

    // Write series data to the file
    for (int i = 1; i < maxiter + 1; i++) {
        double series_value = series.compute(i);
        file << i << this->separator << series_value << this->separator << analytic_prediction << std::endl;
    }

    // Close the file
    file.close();

    std::cout << "Series written to file " << filename << std::endl;
}
