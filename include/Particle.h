#ifndef Particle_h
#define Particle_h

#include <vector>
#include <iostream>
#include <iomanip>
#include "TF1.h"

class Particle {
public:
   /// Particle default constructor for an _n_ - dimensional search space (- _n_ fitting parameters)
   Particle(int n);

   /// Set the particle's _t_ - coordinate <br> <br>
   /// Referenced by Population::init(), Population::moveParticles()
   void setPosition(size_t t, double);

   /// Set the best position recorded by the particle if the current one is better <br> <br>
   /// Referenced by Population::setBestCost()
   void setBestPosition();

   /// Set the velocity <br> <br>
   /// Referenced by Population::setVelocity(), Population::init()
   void setVelocity(size_t, double);

   /// Set the cost of the current position <br> <br>
   /// Referenced by Evaluate::computeCostFit()
   void setCost(double);

   /// Set the parameters of the model using the coordinates of the current position <br> <br>
   /// Referenced by Evaluate::computeCostFit()
   void setModel(TF1 *);

   /// Set the parameters of the model with the coordinates of the best position ever found by the particle <br> <br>
   /// Referenced by Population::draw();
   void setModelBest(TF1 *t_f);

   /// Return the the number of dimensions of the search space  <br> <br>
   /// Referenced by Population::init(), Population::setVelocity(), Population::moveParticles()
   size_t getDimension() const;

   /// Return the _t_ - coordinate of the particle in the current position <br> <br>
   /// Referenced by Population::setVelocity(), Population::moveParticles()
   double getPosition(size_t t);

   /// Return the _t_ - coordinate of the best position found by the particle <br> <br>
   /// Referenced by Population::setVelocity()
   double getBestPosition(size_t t);

   /// Return the _t_ - component of the velocity <br> <br>
   /// Referenced by Population::setVelocity(), Population::moveParticles()
   double getVelocity(size_t t);

   /// Return the cost computed using the current position of the particle <br> <br>
   /// Referenced by Population::setBestCost()
   double getCost();

   /// Return the cost computed using the best position found by the particle <br> <br>
   /// Referenced by Population::setBestCost()
   double getBestCost();

   /// Show on video the characteristics of a particle
   friend std::ostream &operator<<(std::ostream &t_os, Particle &t_rhs)
   {
      std::cout << "la particella con chi best migliore ha trovato il chi best in: " << std::endl;
      for (size_t i = 0; i < t_rhs.getDimension(); ++i) {
         t_os << std::setw(10) << std::right << t_rhs.getBestPosition(i);
         if (i < t_rhs.getDimension() - 1) t_os << ", ";
      };
      t_os << " --> fitness migliore " << t_rhs.m_cost_best << std::endl;
      return t_os;
   };

   /// Compare two particles' best cost found
   friend bool operator<(const Particle &l, const Particle &r) { return l.m_cost_best < r.m_cost_best; };

private:
   std::vector<double> m_position;      /**<Vector storing the coordinates of the current position*/
   std::vector<double> m_position_best; /**<Vector storing the coordinates of the best position found*/
   std::vector<double> m_velocity;      /**<Vector storing the velocity components*/
   double              m_cost;          /**<Particle's cost evaluated in the current position*/
   double              m_cost_best;     /**<Particle's best cost found*/
};

#endif
