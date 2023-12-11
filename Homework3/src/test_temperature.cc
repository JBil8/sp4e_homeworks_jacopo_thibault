#include "fft.hh"
#include "compute_temperature.hh"
#include "system.hh"
#include "matrix.hh"
#include "material_point.hh"
#include "my_types.hh"
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
    }

    Matrix<complex> heat_source(N);
    for (auto&& entry : index(heat_source)) {
            auto& val = std::get<2>(entry);
            val = 0.0;
        }

    temperature = std::make_shared<ComputeTemperature>(dt, 1.0, 1.0, 1.0, heat_source);

}
