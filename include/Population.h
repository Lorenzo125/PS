#ifndef Population_h
#define Population_h

#include <iostream>
#include <numeric>

#include "Config.h"
#include "Particle.h"

class Population {
public:
  Population(const Config&);

  Population(const Population&);

  void Init();

  size_t Size() const;

  void Sort();

  Config Configuration();

  Particle& AccessParticle(size_t i) {
    return m_particle[i];
  };

  Particle& operator[](size_t i) {
    return m_particle[i];
  };

  friend std::ostream& operator<<(std::ostream& os, Population& rhs) {
    os << "--- Population ---\n";
  /*for (size_t i = 0; i < rhs.Size(); ++i) { //stampa tutta la popolazione
    os << rhs[i];
  };*/
  os << rhs[0]; //stampa migliore

  os << "------------------\n";
  return os;
};

private:
  std::vector<Particle> m_particle;
  Config m_conf;
};

#endif
