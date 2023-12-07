#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "matrix.hh"
#include "my_types.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {

  // Virtual implementation
public:
  // Constructor
  ComputeTemperature(Real timestep, Real heat_conductivity, Real density, Real heat_capacity, Matrix<complex> heat_source);

public:
  //! Set time step
  void setDeltaT(Real dt);
  //! Penalty contact implementation
  void compute(System& system) override;

private:
  Real dt;
  Real heat_conductivity;
  Real density;
  Real heat_capacity;
  Matrix<complex> heat_source;

};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
