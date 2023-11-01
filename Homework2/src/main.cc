#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>
#include <cmath>
#include "series.hh"
#include "computeArithmetic.hh"
#include "computePi.hh"
#include "dumperSeries.hh"
#include "printSeries.hh"
#include "writeSeries.hh"
#include "riemannIntegral.hh"

// Function to display usage information
void usage() {
    std::cerr << "Usage: ./src/snippet <type> <N> <f> <dump> [<p>]" << std::endl;
    std::cerr << "  type: pi, arithmetic, or riemann" << std::endl;
    std::cerr << "  N: number of iterations for pi and arithmetic or number of discretization for riemann" << std::endl;
    std::cerr << "  f: frequency of dumping" << std::endl;
    std::cerr << "  dump: print or write" << std::endl;
    std::cerr << "  p: (Optional) precision of the output" << std::endl;
}

int main(int argc, char* argv[]) {
    // Ensure the correct number of arguments are provided
    if (argc < 5) {
        usage();
        return 1;
    }

    // Parse command line arguments
    unsigned int num_iterations, frequency, precision;
    std::string series_type, filename, dump_type;

    std::stringstream args;
    for (int i = 1; i < argc; ++i) {
        args << argv[i] << " ";
    }

    args >> series_type >> num_iterations >> frequency >> dump_type;
    if (argc == 6) {
        args >> precision;
    } else {
        precision = 10;
    }

    // Create the appropriate series object based on the input type
    std::shared_ptr<Series> series_object;
    if (series_type == "pi") {
        series_object = std::make_shared<ComputePi>();
    } else if (series_type == "arithmetic") {
        series_object = std::make_shared<ComputeArithmetic>();
    } else if (series_type == "riemann") {
        // Parse the remaining arguments for Riemann integral
        double a, b;
        std::string f_type;

        std::cout <<"Enter the lower bound (a):";
        std::cin >> a;
        std::cout <<"Enter the upper bound (b):";
        std::cin >> b;
        std::cout << "Choose the function type ('cubic', 'cos', or 'sin'): ";
        std::cin >> f_type;

        // Define the function and its integral
        std::function<double(double)> f;
        std::function<double(double)> integral_f;

        if (f_type == "cubic") {
            f = [](double x) { return 1.0 * x * x * x; };
            integral_f = [](double x) { return pow(x, 4) / 4; };
        } else if (f_type == "cos") {
            f = [](double x) { return std::cos(x); };
            integral_f = [](double x) { return std::sin(x); };
        } else if (f_type == "sin") {
            f = [](double x) { return std::sin(x); };
            integral_f = [](double x) { return -1.0 * std::cos(x); };
        } else {
            std::cerr << "Unknown function type: " << f_type << std::endl;
            usage();
            return 1;
        }
        series_object = std::make_shared<RiemannIntegral>(a, b, f, integral_f);
    } else {
        std::cerr << "Unknown series type: " << series_type << std::endl;
        usage();
        return 1;
    }

    // Perform the requested dump operation
    if (dump_type == "print") {
        // Print the series data
        PrintSeries print_series(*series_object, frequency, num_iterations);
        print_series.setPrecision(precision);
        print_series.dump(std::cout);
    } else if (dump_type == "write") {
        // Parse the remaining arguments for writing to a file
        std::string separator;
        std::cout << "Enter the filename for the output file (no extension necessary): ";
        std::cin >> filename;
        std::cout << "Enter the separator for the output file (, for .csv, | for .psv or a generic key for default (.txt)): ";
        std::cin >> separator;
        std::string plot;
        std::cout << "Do you want to plot the output? (y/n): ";
        std::cin >> plot;

        // Add the file extension to the filename based on the separator
        if (separator == ",") {
            filename += ".csv";
        } else if (separator == "|") {
            filename += ".psv";
        } else {
            filename += ".txt";
            separator = " ";
        }

        std::ofstream file(filename);
        WriteSeries write_series(*series_object, num_iterations, filename);
        write_series.setSeparator(separator);
        write_series.setPrecision(precision);
        write_series.dump(file);

        // Calling python script to plot data
        if (plot == "y") {
            std::string command = "python3 ../src/plotData.py " + filename;
            system(command.c_str());
        }
    } else {
        std::cerr << "Unknown dump type: " << dump_type << std::endl;
        usage();
        return 1;
    }

    return 0;
}
