#include "fft.hh"
#include "compute_temperature.hh"
#include "system.hh"
#include "matrix.hh"
#include "material_point.hh"
#include "my_types.hh"
#include <cmath>
#include <gtest/gtest.h>

/*****************************************************************/

class InitialConditions : public ::testing::Test {
protected:
    void SetUp() override {

        N = 100;
        dt = 0.1;

        // Initialize the points 
        std::vector<MaterialPoint> points;
            for (UInt i = 0; i < N; ++i) {
                MaterialPoint p;
                p.getTemperature() = 1.0;
                points.push_back(p);
            }

        // Add particles to system
        for (auto& p : points) {
            system.addParticle(std::make_shared<MaterialPoint>(p));
        }

    }

    System system;
    UInt N;
    double dt;
    std::shared_ptr<ComputeTemperature> temperature;

  
};

/*****************************************************************/

TEST_F(InitialConditions, homogeneous) {

    for (UInt i = 0; i < N; ++i) {
        MaterialPoint &p = dynamic_cast<MaterialPoint&>(system.getParticle(i));
        p.getTemperature() = 0.0;
    }

    Matrix<complex> heat_source(N);
    for (auto&& entry : index(heat_source)) {
            auto& val = std::get<2>(entry);
            val = 0.0;
        }

    temperature = std::make_shared<ComputeTemperature>(dt, 1.0, 1.0, 1.0, heat_source);
    temperature->compute(system);
    for (UInt i = 0; i < N; ++i) {
        MaterialPoint &p = dynamic_cast<MaterialPoint&>(system.getParticle(i));
        ASSERT_NEAR(0.0, p.getTemperature(), 1e-10);
    }
}

TEST_F(InitialConditions, volumetric_heat_source) {

    Real x_min, x_max, y_min, y_max;
    x_min = -1.0;
    x_max = 1.0;
    y_min = -1.0;
    y_max = 1.0;

    for (UInt i = 0; i < sqrt(N); ++i) {
        for (UInt j = 0; j < sqrt(N); ++j) {
            MaterialPoint &p = dynamic_cast<MaterialPoint&>(system.getParticle(i*sqrt(N) + j));
            p.getPosition()[0] = x_min + (x_max - x_min) / sqrt(N) * i;
            //p.getPosition()[1] = y_min + (y_max - y_min) / sqrt(N) * j;
            p.getTemperature() = sin(2*M_PI*p.getPosition()[0]/(x_max - x_min));
        }
    }

    Matrix<complex> heat_source(N);
    Real scalar_factor = pow(2*M_PI/(x_max-x_min), 2) ;
    for (auto&& entry : index(heat_source)) {
        //assign value of sin similar to initial temperature distribution defined above
        auto& i = std::get<0>(entry);
        auto& j = std::get<1>(entry);
        auto& val = std::get<2>(entry);
        val = scalar_factor* sin(2*M_PI*i/(x_max-x_min));
        }

    temperature = std::make_shared<ComputeTemperature>(dt, 1.0, 1.0, 1.0, heat_source);
    temperature->compute(system);

    for (UInt i = 0; i < sqrt(N); ++i) {
        for (UInt j = 0; j < sqrt(N); ++j) {
            MaterialPoint &p = dynamic_cast<MaterialPoint&>(system.getParticle(i*sqrt(N) + j));
            ASSERT_NEAR(p.getTemperature(), sin(2*M_PI*p.getPosition()[0]/(x_max - x_min)), 1e-5);
        }
    }
}