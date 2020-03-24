#ifndef Particle_h
#define Particle_h

#include "TF1.h"
#include <vector>
#include <iostream>
#include <iomanip>

class Particle {
public:
  Particle(size_t);

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

  friend std::ostream& operator<<(std::ostream& os, Particle& rhs) { //per stampare a video una particella con relative coordinate e chi
    std::cout << "la particella con chi best migliore attualmente si trova in:" << std::endl;
    for (size_t i = 0; i < rhs.Size(); ++i) {
      os << std::setw(10) << std::right << rhs.ViewPosition(i);
      if (i < rhs.Size()-1) os << ", ";
    }
    os << " --> fitness attuale " << rhs.m_cost << std::endl;
    std::cout << "la particella con chi best migliore ha trovato il chi best in: " << std::endl;
    for (size_t i = 0; i < rhs.Size(); ++i) {
      os << std::setw(10) << std::right << rhs.ViewBestPosition(i);
      if (i < rhs.Size()-1) os << ", ";
    }
    os << " --> fitness migliore " << rhs.m_cost_best << std::endl;
    return os;
  };

  friend bool operator<(const Particle& l, const Particle& r) { //utilizzato solo per riordinare le particelle
  return l.m_cost_best < r.m_cost_best;
};

private:
  std::vector<double> m_position;
  std::vector<double> m_position_best;
  std::vector<double> m_velocity;
  double m_cost;
  double m_cost_best;
};

#endif
