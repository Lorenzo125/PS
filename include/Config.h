#ifndef Config_h
#define Config_h

#include "ParametersDomain.h"

class Config {
public:

  int num_particles;
  double cognitive_par;
  double social_par;
  double Vmax;

  ParametersDomain ParDomain;

  int NumberOfParameters() const {
    return ParDomain.NumberOfParameters();
  };

  int ShowNumParticles() {
    return num_particles;
  };

};

#endif
