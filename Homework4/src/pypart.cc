#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

#include "compute.hh"
#include "compute_interaction.hh"
#include "compute_gravity.hh"
#include "compute_temperature.hh"
#include "compute_verlet_integration.hh"

#include "csv_writer.hh"

#include "system.hh"

PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project";


  /***************************************************************************************/

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
    .def("createSimulation", py::overload_cast<const std::string &, Real, py::function>(&ParticlesFactoryInterface::createSimulation<py::function>),
         py::return_value_policy::reference_internal,
         py::arg("fname"), py::arg("timestep"), py::arg("func")
     )
        
    .def_static("getInstance", 
            &ParticlesFactoryInterface::getInstance,
            py::return_value_policy::reference // C++ side is responsible for managing the object’s lifetime
        )
    .def_property_readonly("system_evolution", &ParticlesFactoryInterface::getSystemEvolution);

  // PlanetsFactory
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(
            m, "PlanetsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    ) 
    .def("getInstance", &PlanetsFactory::getInstance,
             py::return_value_policy::reference);

  // PingPongBallsFactory
  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
            m, "PingPongBallsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )  
    .def("getInstance", &PingPongBallsFactory::getInstance,
             py::return_value_policy::reference);
  
  // MaterialPointsFactory
  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
            m, "MaterialPointsFactory",
            py::dynamic_attr() // to allow new members to be created dynamically
    )  
    .def("getInstance", &MaterialPointsFactory::getInstance,
            py::return_value_policy::reference);


  /***************************************************************************************/

  // Compute
  py::class_<Compute, std::shared_ptr<Compute>>(
            m, "Compute",
            py::dynamic_attr() // to allow new members to be created dynamically
    );

  // ComputeInteraction
  py::class_<ComputeInteraction, Compute, std::shared_ptr<ComputeInteraction>>(
            m, "ComputeInteraction",
            py::dynamic_attr() // to allow new members to be created dynamically
    );

  // ComputeGravity
  py::class_<ComputeGravity, ComputeInteraction, std::shared_ptr<ComputeGravity>>(
            m, "ComputeGravity",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<>())
    .def("setG", &ComputeGravity::setG);
  
  // Compute temperature
  py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(
            m, "ComputeTemperature",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    .def(py::init<>())
    // Give read write access to the properties through acessors
    .def_property("conductivity", 
            &ComputeTemperature::getConductivity,
            [](ComputeTemperature& c, Real val){c.getConductivity() = val; }
            )
    .def_property("capacity",
            &ComputeTemperature::getCapacity,
            [](ComputeTemperature& c, Real val){c.getCapacity() = val; }
            )
    .def_property("density",
            &ComputeTemperature::getDensity,
            [](ComputeTemperature& c, Real val){c.getDensity() = val; }
            )
    .def_property("L",
            &ComputeTemperature::getL,
            [](ComputeTemperature& c, Real val){c.getL() = val; }
            )
    .def_property("delta_t",
            &ComputeTemperature::getDeltat,
            [](ComputeTemperature& c, Real val){c.getDeltat() = val; }
            );

  // ComputeVerletIntegration
  py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(
            m, "ComputeVerletIntegration",
            py::dynamic_attr() // to allow new members to be created dynamically
    )
    //.def(py::init<>())
    .def("setDeltaT", &ComputeVerletIntegration::setDeltaT)
    .def("addInteraction", &ComputeVerletIntegration::addInteraction);

  // CSVWriter
  py::class_<CsvWriter>(
            m, "CsvWriter",
            py::dynamic_attr() // to allow new members to be created dynamically
    ) 
    .def(py::init<const std::string&>())
    .def("write", &CsvWriter::write);

  // System
  py::class_<System>(
            m, "System",
            py::dynamic_attr() // to allow new members to be created dynamically
    ) 
    .def(py::init<>());
    

}
