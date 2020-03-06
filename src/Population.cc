#include "Population.h"
#include "TH1F.h"
#include <random>

Population::Population(const Config& conf) :
m_particle(conf.num_particles, conf.NumberOfParameters()), m_conf(conf) {};

void Population::Init() {

  std::random_device rd;
  std::mt19937 rng(rd());

  for (size_t i = 0; i < m_particle.size(); ++i) {
    size_t psize = m_particle[i].Size();
    for (size_t j = 0; j < psize; ++j) {
      std::uniform_real_distribution<double> uni(m_conf.ParDomain.ViewParMin(j), m_conf.ParDomain.ViewParMax(j));
      m_particle[i].SetPosition(j, uni(rng)),
      m_particle[i].SetVelocity(j, 0.);
    };
  };
};

size_t Population::Size() const {
  return m_particle.size();
};

Config Population::Configuration() {
  return m_conf;
};

void Population::Sort() {
  std::sort(m_particle.begin(), m_particle.end());
};
