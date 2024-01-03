#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute_temperature.hh"
#include "csv_writer.hh"
#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project";

  // ParticlesFactoryInterface
  py::class_<ParticlesFactoryInterface>(
            m, "ParticlesFactoryInterface",
            py::dynamic_attr() // to allow new members to be created dynamically
    )

    .def("createSimulation", 
            [](ParticlesFactoryInterface &self, const std::string &fname, Real timestep) -> SystemEvolution& {
                return self.createSimulation(fname, timestep);
            },
            py::return_value_policy::reference_internal, // Keeps the object alive as long as the parent object is alive
            py::arg("fname"), py::arg("timestep")
        )
    .def("createSimulation", 
            [](ParticlesFactoryInterface &self, const std::string &fname, Real timestep, py::function func) -> SystemEvolution& {
                auto wrapper = [func](Real timestep) { func(timestep); };
                return self.createSimulation(fname, timestep, wrapper);
            },
            py::return_value_policy::reference_internal, // Keeps the object alive as long as the parent object is alive
            py::arg("fname"), py::arg("timestep"), py::arg("func")
        )
    .def_static("getInstance", 
            &ParticlesFactoryInterface::getInstance,
            py::return_value_policy::reference // C++ side is responsible for managing the object’s lifetime
        )
    .def_property_readonly("system_evolution", &ParticlesFactoryInterface::getSystemEvolution)

  // PlanetsFactory
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(
            m, "PlanetsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    ) 
    .def("getInstance", &PlanetsFactory::getInstance,
             py::return_value_policy::reference)

  // PingPongBallsFactory
  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
            m, "PingPongBallsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )  
    .def("getInstance", &PingPongBallsFactory::getInstance,
             py::return_value_policy::reference)
  
  // MaterialPointsFactory
  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
            m, "MaterialPointsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )  
    .def("getInstance", &MaterialPointsFactory::getInstance,
             py::return_value_policy::reference)

}
