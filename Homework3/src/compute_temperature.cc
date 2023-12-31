#include "fft.hh"
#include "material_point.hh"
#include "system.hh"
#include "compute_temperature.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

ComputeTemperature::ComputeTemperature(Real timestep, Real heat_conductivity, Real density, Real heat_capacity)
    : dt(timestep), heat_conductivity(heat_conductivity), density(density), heat_capacity(heat_capacity) {}

/* -------------------------------------------------------------------------- */

void ComputeTemperature::setDeltaT(Real dt) { this->dt = dt; }


void ComputeTemperature::compute(System& system) {

    UInt size = system.getNbParticles();
    UInt N = std::sqrt(size);

    Matrix<complex> temp(N);
    Matrix<complex> heat_source(N);
    Matrix<complex> temp_rate_fft(N);
    Matrix<complex> temp_fft(N);
    Matrix<complex> heat_source_fft(N); 
    Matrix<complex> temp_rate(N);


    int i = 0;
    int j = 0;
    for (auto& par : system) {
        auto& mp = dynamic_cast<MaterialPoint&>(par);

        temp(i, j).real(mp.getTemperature());
        heat_source(i, j).real(mp.getHeatSource());
        
        j++;
        if (j == N) {
            j = 0;
            i++;
        }
    }


    // FFT
    temp_fft = FFT::transform(temp); 
    heat_source_fft = FFT::transform(heat_source);


    // Frequencies
    auto q = FFT::computeFrequencies(N);

    Real NN = (Real) N*N;
    for (auto&& entry : index(q)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);

        val /= NN;
    }



    for (auto&& entry : index(temp_rate_fft)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);

        val = (heat_source_fft(i, j) - heat_conductivity * temp_fft(i, j) * (pow(q(i, j).real(), 2) + pow(q(i, j).imag(), 2)));
        val *= 1/(density * heat_capacity);
    }

    // Inverse FFT
    temp_rate = FFT::itransform(temp_rate_fft);
    

    int k = 0;
    int l = 0;
    for (auto& par : system) {
        auto& mp = dynamic_cast<MaterialPoint&>(par);

        mp.getTemperature() = temp(k, l).real() + temp_rate(k, l).real() * this->dt;

        l++;
        if (l == N) {
            l = 0;
            k++;
        }
    }


}




/* -------------------------------------------------------------------------- */
