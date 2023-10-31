#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include "series.hh"
#include "computeArithmetic.hh"
#include "computePi.hh"
#include "dumperSeries.hh"
#include "printSeries.hh"
#include "writeSeries.hh"

// Function to display usage information
void usage() {
    std::cerr << "Usage: ./src/snippet <type> <N> <f> <filename> <dump> [<sep>]" << std::endl;
    std::cerr << "  type: pi or arithmetic" << std::endl;
    std::cerr << "  N: number of iterations" << std::endl;
    std::cerr << "  f: frequency of dumping" << std::endl;
    std::cerr << "  filename: name of the output file" << std::endl;
    std::cerr << "  dump: print or write" << std::endl;
    std::cerr << "  sep: separator for the output file (optional, default is space)" << std::endl;
}

int main(int argc, char* argv[]) {

    // Ensure the correct number of arguments are provided
    if (argc < 6) {
        usage();
        return 1;
    }

    // Parse command line arguments
    unsigned int num_iterations, frequency;
    std::string series_type, separator, filename, dump_type;

    std::stringstream args;
    for (int i = 1; i < argc; ++i) {
        args << argv[i] << " ";
        // std::cout << argv[i] << std::endl;
    }

    if (argc == 7) {
        args >> series_type >> num_iterations >> frequency >> filename >> dump_type >> separator;
    } else {
        args >> series_type >> num_iterations >> frequency >> filename >> dump_type;
    }


    // Create the appropriate series object based on the input type
    std::shared_ptr<Series> series_object;
    if (series_type == "pi") {
        series_object = std::make_shared<ComputePi>();
    } else if (series_type == "arithmetic") {
        series_object = std::make_shared<ComputeArithmetic>();
    } else {
        std::cerr << "Unknown series type: " << series_type << std::endl;
        usage();
        return 1;
    }

    // Perform the requested dump operation
    if (dump_type == "print") {
        PrintSeries print_series(*series_object, frequency, num_iterations);
        print_series.dump();
    } else if (dump_type == "write") {
        WriteSeries write_series(*series_object, num_iterations, filename);
        write_series.setSeparator(separator);
        write_series.dump();
    } else {
        std::cerr << "Unknown dump type: " << dump_type << std::endl;
        usage();
        return 1;
    }

    return 0;
}
