#ifndef Config_h
#define Config_h

#include "ParametersDomain.h"
#include "TMath.h"

class Config {
public:
   /// Config default constructor

   Config() {}

   /// Config constructor assigning working conditions

   Config(int t_nparticles /**<number of particles */, double t_cognitive /**<cognitive learning factor*/,
          double t_social /**<social learning factor*/, double t_inertia /**inertia factor*/,
          double                  t_vmax /**< maximum distance of movement-per-iteration allowed */,
          const ParametersDomain &t_par_domain /**<search domain*/)
      : m_nparticles(t_nparticles), m_cognitive(t_cognitive), m_social(t_social), m_vmax(t_vmax), m_inertia(t_inertia),
        m_par_domain(t_par_domain)
   {
   }

   /// Set the number of particles in the population
   void setNumberOfParticles(int t) { m_nparticles = t; };

   /// Set the cognitive learning factor, by deafult = 2.0 <br> <br>
   void setCognitiveParameter(double t) { m_cognitive = t; };

   /// Set the social learning factor, by deafult = 2.0 <br> <br>
   void setSocialParameter(double t) { m_social = t; };

   /// Set the inertia factor <br> <br>
   void setInertia(double t) { m_inertia = t; };

   /// Set the maximum distance of movement-per-iteration allowed <br> <br>
   void setVMaxParameter(double t) { m_vmax = t; };

   /// Set the search domain <br> <br>
   void setParametersDomain(const ParametersDomain &t) { m_par_domain = t; }

   /// Return the number of particles in the population <br> <br>
   int getNumberOfParticles() const { return m_nparticles; };

   /// Return the cognitive learning factor <br> <br>
   /// Referenced by Population::setVelocity()
   double getCognitiveParameter() const { return m_cognitive; };

   /// Return the social learning factor <br> <br>
   /// Referenced by Population::setVelocity()
   double getSocialParameter() const { return m_social; };

   /// Return the intertia factor <br> <br>
   /// Referenced by Population::setVelocity()
   double getInertia() const { return m_inertia; };

   /// Return the maximum distance of movement-per-iteration allowed <br> <br>
   /// Referenced by Population::setVelocity()
   double getVMaxParameter() const { return m_vmax; };

   /// Return the number of parameters in the model
   int getNumberOfParameters() const { return m_par_domain.getNumberOfParameters(); };

   /// Return the minimum value allowed for the _t_ - parameter <br> <br>
   /// Referenced by Population::init(), Population::moveParticles()
   double getParameterMin(size_t t) { return m_par_domain.getParameterMin(t); };

   /// Return the maximum value allowed for the _t_ - parameter<br> <br>
   /// Referenced by Population::init(), Population::moveParticles()
   double getParameterMax(size_t t) { return m_par_domain.getParameterMax(t); };

private:
   int              m_nparticles; /**< Number of particles */
   double           m_cognitive;  /**< Cognitive learning factor */
   double           m_social;     /**< Social learning factor */
   double           m_inertia;    /**< Inertia factor*/
   double           m_vmax;       /**< Maximum distance of movement-per-iteration */
   ParametersDomain m_par_domain; /**< search domain */
};
#endif
