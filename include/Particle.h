#ifndef Particle_h
#define Particle_h

#include "TF1.h"
#include <vector>
#include <iostream>
#include <iomanip>

class Particle {
public:
  Particle(size_t);

  /*Particle(const std::vector<double>&);

  Particle(const Particle&);*/

  size_t Size() const;

  double ViewPosition(size_t);

  double ViewBestPosition(size_t);

  double ViewVelocity(size_t);

  double ViewCost();

  double ViewBestCost();

  void SetPosition(size_t, double);

  void SetBestPosition();

  void SetVelocity(size_t, double);

  void SetCost(double);

  void UpdateModel(TF1*);

  friend std::ostream& operator<<(std::ostream& os, Particle& rhs) {
    for (size_t i = 0; i < rhs.Size(); ++i) {
      os << std::setw(10) << std::right << rhs.ViewBestPosition(i);
      if (i < rhs.Size()-1) os << ", ";
    }
    os << " --> " << rhs.m_cost_best << "\n";
    return os;
  };

  friend bool operator<(const Particle& l, const Particle& r) {
    return l.m_cost_best < r.m_cost_best;
  }

private:
  std::vector<double> m_position;
  std::vector<double> m_position_best;
  std::vector<double> m_velocity;
  double m_cost;
  double m_cost_best;
};

#endif
