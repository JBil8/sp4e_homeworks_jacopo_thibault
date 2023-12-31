#include "material_point.hh"

/* -------------------------------------------------------------------------- */
void MaterialPoint::printself(std::ostream& stream) const {
  Particle::printself(stream);
  stream << " " << temperature << " " << heat_source;
}

/* -------------------------------------------------------------------------- */

void MaterialPoint::initself(std::istream& sstr) {
  Particle::initself(sstr);
  sstr >> temperature >> heat_source;
}
