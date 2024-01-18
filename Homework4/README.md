# Homework 4: Application to a heat equation solver





1.2 - The createSimulation function in the ParticlesFactory class is an overloaded template function. It takes a functor func as a parameter, which is then assigned to createComputes. This createSimulation function is designed to allow users to define custom behavior (via func) that is executed at each timestep of the simulation. 

2.2 - Using **pybind11**, to ensure that references to Compute objects (or any C++ objects) are correctly managed when exposed to Python, it is necessary to specify appropriate return value policies in the bindings. This controls how the lifetime of the object is managed and how references are handled between C++ and Python (e.g. with py::return_value_policy::reference, C++ side is responsible for managing the object’s lifetime). This is done in `.def()`.