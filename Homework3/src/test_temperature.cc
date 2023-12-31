#include "fft.hh"
#include "compute_temperature.hh"
#include "system.hh"
#include "matrix.hh"
#include "material_point.hh"
#include "material_points_factory.hh"
//#include "my_types.hh"
#include <gtest/gtest.h>

/*****************************************************************/

class InitialConditions : public ::testing::Test {
protected:
    void SetUp() override {

        nb_particles = 144;
        dt = 0.1;

        // Initialize the points 
        std::vector<MaterialPoint> points;
        for (UInt i = 0; i < nb_particles; ++i) {
            MaterialPoint p;
            p.getTemperature() = 0.0;
            p.getHeatSource() = 0.0;
            p.getTemperatureRate() = 0.0;
            points.push_back(p);
            }

        // Add particles to system
        for (auto& p : points) {
            system.addParticle(std::make_shared<MaterialPoint>(p));
        }

    }

    System system;
    UInt nb_particles;
    double dt;
    std::shared_ptr<ComputeTemperature> temperature;

};

/*****************************************************************/

TEST_F(InitialConditions, homogeneous) {

    for (UInt i = 0; i < nb_particles; ++i) {
        MaterialPoint &p = static_cast<MaterialPoint&>(system.getParticle(i));
        p.getTemperature() = 1.0;
        p.getHeatSource() = 0;
    }    

    temperature = std::make_shared<ComputeTemperature>(dt, 1.0, 1.0, 1.0);
    temperature->compute(system);
    for (UInt i = 0; i < nb_particles; ++i) {
        MaterialPoint &p = static_cast<MaterialPoint&>(system.getParticle(i));
        ASSERT_NEAR(1.0, p.getTemperature(), 1e-10);
    }
}

TEST_F(InitialConditions, volumetric_heat_source) {

    Real x_min, x_max, y_min, y_max;
    x_min = -1.0;
    x_max = 1.0;
    y_min = -1.0;
    y_max = 1.0;

    for (UInt i = 0; i < sqrt(nb_particles); ++i) {
        for (UInt j = 0; j < sqrt(nb_particles); ++j) {
            MaterialPoint &p = static_cast<MaterialPoint&>(system.getParticle(i*sqrt(nb_particles) + j));
            p.getPosition()[0] = x_min + (x_max - x_min) / sqrt(nb_particles) * i;
            //p.getPosition()[1] = y_min + (y_max - y_min) / sqrt(N) * j;
            p.getTemperature() = sin(2*M_PI*p.getPosition()[0]/(x_max - x_min));
        }
    }

    Matrix<complex> heat_source(sqrt(nb_particles));
    Real scalar_factor = pow(2*M_PI/(x_max-x_min), 2) ;
    for (auto&& entry : index(heat_source)) {
        //assign value of sin similar to initial temperature distribution defined above
        auto& i = std::get<0>(entry);
        auto& j = std::get<1>(entry);
        auto& val = std::get<2>(entry);
        val = scalar_factor* sin(2*M_PI*i/(x_max-x_min));
        }

    temperature = std::make_shared<ComputeTemperature>(dt, 1.0, 1.0, 1.0);
    temperature->compute(system);

    for (UInt i = 0; i < sqrt(nb_particles); ++i) {
        for (UInt j = 0; j < sqrt(nb_particles); ++j) {
            MaterialPoint &p = static_cast<MaterialPoint&>(system.getParticle(i*sqrt(nb_particles) + j));
            ASSERT_NEAR(p.getTemperature(), sin(2*M_PI*p.getPosition()[0]/(x_max - x_min)), 1e-5);
        }
    }
}