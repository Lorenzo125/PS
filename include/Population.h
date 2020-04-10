#ifndef Population_h
#define Population_h

#include <iostream>
#include <numeric>
#include <random>
#include "Config.h"
#include "Particle.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TH1F.h"

class Population {
public:
   /// Population default constructor, starting from an assignment of Config
   Population(const Config &t_config);

   /// Initialization of the population with random starting points for the particles and null velocity
   void init();

   /// Return the number of particles in the population <br> <br>
   /// Referenced by Evaluate::computeCostFit()
   size_t size() const;

   /// Sort the particles according to their best solution
   void sort();

   /// Set the velocity for each particle in the population
   void setVelocity();

   /// Move all the particle in a new position with the calculated velocity
   void moveParticles();

   /// Update the best cost for each particle if the new position is a better solution
   void setBestCost();

   /// Show on display the model with the best solution found and the normalized data in the background
   void draw(TH1F *t_data, TF1 *t_model);

   /// Return the _t_ - particle
   Particle &accessParticle(size_t t) { return m_particle[t]; };

   /// Return the _t_ - particle
   Particle &operator[](size_t t) { return m_particle[t]; };

   /// Show on video the current position, the best position and the best cost for the _0_ - particle (the one that has
   /// found the best global solution)
   friend std::ostream &operator<<(std::ostream &t_os, Population &t_rhs)
   {
      /*os << "--- Population ---\n";
      for (size_t i = 0; i < rhs.size(); ++i) { //stampa tutta la popolazione
      os << t_rhs[i];
    };*/
      t_os << t_rhs[0];

      t_os << "------------------\n";
      return t_os;
   };

private:
   std::vector<Particle> m_particle; /**<Vector of particles that compose the population*/
   Config                m_config;   /**<Configuration used by the population*/
   std::mt19937          m_mt;       /**<Random numbers generator used for calculations*/
};

#endif
