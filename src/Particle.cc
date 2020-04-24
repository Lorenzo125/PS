#include "Particle.h"
#include "TRandom.h"

Particle::Particle(int n) : m_position(n, 0), m_position_best(n, 0), m_velocity(n, 0), m_cost(0.), m_cost_best(0.){};

void Particle::setPosition(size_t t, double t_x)
{
   m_position[t] = t_x;
};

void Particle::setBestPosition()
{
   for (int i = 0; i < m_position.size(); i++) {
      m_position_best[i] = m_position[i];
   };
   m_cost_best = m_cost;
};

void Particle::setCost(double t)
{
   m_cost = t;
};

void Particle::setVelocity(size_t t, double t_x)
{
   m_velocity[t] = t_x;
};

void Particle::setModel(TF1 *t_f)
{
   for (size_t i = 0; i < m_position.size(); ++i) {
      t_f->SetParameter(i, m_position[i]);
   };
};

size_t Particle::getDimension() const
{
   return m_position.size();
};

double Particle::getPosition(size_t t)
{
   return m_position[t];
};

double Particle::getBestPosition(size_t t)
{
   return m_position_best[t];
};

double Particle::getVelocity(size_t t)
{
   return m_velocity[t];
};

double Particle::getCost()
{
   return m_cost;
};

double Particle::getBestCost()
{
   return m_cost_best;
};
