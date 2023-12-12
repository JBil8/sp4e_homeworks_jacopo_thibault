#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include "system.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

ComputeTemperature::ComputeTemperature(Real timestep, Real heat_conductivity, Real density, Real heat_capacity, Matrix<complex> heat_source)
    : dt(timestep), heat_conductivity(heat_conductivity), density(density), heat_capacity(heat_capacity), heat_source(heat_source) {}

/* -------------------------------------------------------------------------- */

void ComputeTemperature::setDeltaT(Real dt) { this->dt = dt; }


void ComputeTemperature::compute(System& system) {

    UInt size = system.getNbParticles();
    UInt N = std::sqrt(size);

    Matrix<complex> temp(size);
    Matrix<complex> heat_source(size);
    Matrix<complex> temp_rate_fft(size);
    Matrix<complex> temp_fft(size);
    Matrix<complex> heat_source_fft(size); 
    Matrix<complex> temp_rate(size);


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

    temp_fft = FFT::transform(temp); 
    heat_source_fft = FFT::transform(heat_source);
    // printing temperature fft



    auto q = FFT::computeFrequencies(N);

    for (auto&& entry : index(temp_rate_fft)) {
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);

        val = (heat_source_fft(i, j) - heat_conductivity * temp_fft(i, j) * (pow(q(i, j).real(), 2) + pow(q(i, j).imag(), 2)));
        val *= 1/(density * heat_capacity);
    }

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
