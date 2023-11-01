#include "writeSeries.hh"
#include <fstream>
#include <iostream>
#include <iomanip>
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


void WriteSeries::setPrecision(unsigned int precision){
    this->precision = precision;
};


void WriteSeries::dump(std::ostream &os) {
    
    // Open the file
    if (!os) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write the series to the file
    double analytic_prediction = series.getAnalyticPrediction();
    os << "Iterations" << this->separator << "Series_Value" << this->separator << "Analytic_Prediction" << std::endl;
    
    /*
    if (!std::isnan(analytic_prediction)) {
        file << analytic_prediction << std::endl;
    } else {
        file << "Not available" << std::endl;
    }*/

    // set precision
    if (precision) {
        WriteSeries::setPrecision(precision);
        os << std::setprecision(this->precision);
    }

    for (int i = 1; i < maxiter+1; i++) {
        double series_value = series.compute(i);
        os << i << this->separator << series_value << this->separator << analytic_prediction << std::endl;
    }

    std::cout << "Series written to file " << filename << std::endl;
}





