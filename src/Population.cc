#include <random>
#include "Population.h"

Population::Population(const Config &t_config)
   : m_particle(t_config.getNumberOfParticles(), t_config.getNumberOfParameters()), m_config(t_config),
     m_mt(std::random_device()()){};

void Population::init()
{
   size_t psize = m_particle[0].getDimension();
   for (size_t i = 0; i < m_particle.size(); ++i) {
      for (size_t j = 0; j < psize; ++j) {
         std::uniform_real_distribution<double> uni1(m_config.getParameterMin(j), m_config.getParameterMax(j));
         std::uniform_real_distribution<double> uni2(-m_config.getVMaxParameter(), m_config.getVMaxParameter());
         m_particle[i].setPosition(j, uni1(m_mt)), m_particle[i].setVelocity(j, uni2(m_mt));
      };
   };
};

size_t Population::size() const
{
   return m_particle.size();
};

void Population::sort()
{
   std::sort(m_particle.begin(), m_particle.end());
};

void Population::setVelocity()
{
   std::uniform_real_distribution<double> uni(0, 1);
   for (size_t i = 0; i < m_particle.size(); ++i) {
      for (size_t j = 0; j < m_particle[i].getDimension(); ++j) {
         double cognitive = m_config.getCognitiveParameter() * uni(m_mt) *
                            (m_particle[i].getBestPosition(j) - m_particle[i].getPosition(j));
         double social = m_config.getSocialParameter() * uni(m_mt) *
                         (m_particle[0].getBestPosition(j) - m_particle[i].getPosition(j));
         double vel = (m_particle[i].getVelocity(j) * m_config.getInertia() + cognitive + social);
         if (abs(vel) < m_config.getVMaxParameter()) {
            m_particle[i].setVelocity(j, vel);
         } else {
            if (vel > m_config.getVMaxParameter()) {
               m_particle[i].setVelocity(j, m_config.getVMaxParameter());
            } else {
               m_particle[i].setVelocity(j, -m_config.getVMaxParameter());
            }
         };
      };
   };
};

void Population::moveParticles()
{
   for (size_t i = 0; i < m_particle.size(); ++i) {
      for (size_t j = 0; j < m_particle[i].getDimension(); ++j) {
         if (m_particle[i].getPosition(j) + m_particle[i].getVelocity(j) >= m_config.getParameterMax(j)) {
            m_particle[i].setPosition(j, m_config.getParameterMax(j));
         } else if (m_particle[i].getPosition(j) + m_particle[i].getVelocity(j) <= m_config.getParameterMin(j)) {
            m_particle[i].setPosition(j, m_config.getParameterMin(j));
         } else
            m_particle[i].setPosition(j, m_particle[i].getPosition(j) + m_particle[i].getVelocity(j));
      }
   }
};

void Population::setBestCost()
{
   for (size_t i = 0; i < m_particle.size(); i++) {
      if (m_particle[i].getCost() < m_particle[i].getBestCost()) {
         m_particle[i].setBestPosition();
      };
   };
};

void Population::draw(TH1F *t_data, TF1 *t_model)
{
   TApplication *app = new TApplication("app", 0, 0);
   TCanvas *     c1  = new TCanvas("c1", "", 1500, 500);
   m_particle[0].setModelBest(t_model);
   t_model->Draw("C");
   t_model->SetTitle("Normalized function and histogram");
   t_data->Draw("SAME");
   app->Run();
};
