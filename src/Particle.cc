#include "Particle.h"
#include  "TRandom.h"

Particle::Particle(size_t ndim) :
m_position(ndim, 0), m_position_best(ndim, 0), m_velocity(ndim, 0), m_cost(0.), m_cost_best(0.) {};

/*Particle::Particle(const std::vector<double>& v) :
m_genes(v), m_cost(0.) {};

Particle::Particle(const Particle& c) :
m_genes(c.m_genes), m_cost(c.m_cost) {};*/


size_t Particle::Size() const {
  return m_position.size();
};

double Particle::ViewPosition(size_t i) {
  return m_position[i];
};

double Particle::ViewBestPosition(size_t i) {
  return m_position_best[i];
};

double Particle::ViewVelocity(size_t i) {
  return m_velocity[i];
};

double Particle::ViewCost(){
  return m_cost;
};

double Particle::ViewBestCost(){
  return m_cost_best;
};

void Particle::SetPosition(size_t i, double x) {
  m_position[i]=x;
};

void Particle::SetBestPosition() {
  for (int i=0; i < m_position.size(); i++)
  m_position_best[i]=m_position[i];
  m_cost_best=m_cost;
};

void Particle::SetCost(double x){
  m_cost=x;
};

void Particle::SetVelocity(size_t i, double x){
  m_velocity[i]=x;
};

void Particle::UpdateModel(TF1* f) {
  for (size_t i = 0; i < m_position.size(); ++i) {
    f->SetParameter(i, m_position[i]);
  }
};
