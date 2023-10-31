#include <iostream>
#include <string>
#include <memory>
#include "series.hh"
#include "computeArithmetic.hh"
#include "computePi.hh"
#include "dumperSeries.hh"
#include "printSeries.hh"

int main(int argc, char* argv[]) {

    std::string series_type = std::string(argv[1]);

    // Creation of objects
    std::shared_ptr<Series> series_object;
    if (series_type == "pi") {
        series_object = std::make_shared<ComputePi>();
    } else if (series_type == "arithmetic") {
        series_object = std::make_shared<ComputeArithmetic>();
    }
    else{
            std::cerr << "Unknown series type: " << series_type << std::endl;
            return 1;
    }

    unsigned int N = 20;

    // Dump the series
    PrintSeries print_series(*series_object, 2, N);
    print_series.dump();

    return 0;
}
