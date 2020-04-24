#ifndef Config_h
#define Config_h

#include "ParametersDomain.h"
#include "TMath.h"

class Config {
public:
   /// Config default constructor

   Config() {}

   /// Config constructor with direct assignment of working conditions

   Config(int t_nparticles /**<number of particles */, double t_cognitive /**<cognitive learning factor*/,
          double t_social /**<social learning factor*/, double t_dumping /**<dumping factor */,
          double                  t_vmax /**< maximum distance of movement-per-iteration allowed */,
          const ParametersDomain &t_par_domain /**<research domain*/)
      : m_nparticles(t_nparticles), m_cognitive(t_cognitive), m_social(t_social), m_vmax(t_vmax), m_dumping(t_dumping),
        m_par_domain(t_par_domain)
   {
   }

   /// Set the number of particles in the population
   void setNumberOfParticles(int t) { m_nparticles = t; };

   /// Set the cognitive learning factor, by deafult = 2.0 <br> <br>
   /// This learning factor set the weight that the particle's own best postion has in the next-step computation
   void setCognitiveParameter(double t) { m_cognitive = t; };

   /// Set the social learning factor, by deafult = 2.0 <br> <br>
   /// This learning factor set the weight that the global best postion has in the next-step computation
   void setSocialParameter(double t) { m_social = t; };

   /// Set dumping factor calculated as default <br> <br>
   /// The dumping factor prevents the swing of the position around the best solution
   void setDumpingFactor()
   {
      double phi = m_social + m_cognitive;
      m_dumping  = 2.0 / TMath::Abs(2.0 - phi - TMath::Power(TMath::Power(phi, 2) - 4.0 * phi, 0.5));
   };

   /// Set the maximum distance of movement-per-iteration allowed <br> <br>
   /// The velocity should be set according to the parameters domain width; a smaller velocity implies a more careful
   /// research, but it requires a greater number of iterations
   void setVMaxParameter(double t) { m_vmax = t; };

   /// Set the fitting parameters domain as research domain <br> <br>
   void setParametersDomain(const ParametersDomain &t) { m_par_domain = t; }

   /// Return the number of particles in the population <br> <br>
   int getNumberOfParticles() const { return m_nparticles; };

   /// Return the cognitive learning factor <br> <br>
   /// Referenced by Population::setVelocity()
   double getCognitiveParameter() const { return m_cognitive; };

   /// Return the social learning factor <br> <br>
   /// Referenced by Population::setVelocity()
   double getSocialParameter() const { return m_social; };

   /// Return the dumping factor <br> <br>
   /// Referenced by Population::setVelocity()
   double getDumpingFactor() const { return m_dumping; };

   /// Return the maximum distance of movement-per-iteration allowed <br> <br>
   /// Referenced by Population::setVelocity()
   double getVMaxParameter() const { return m_vmax; };

   /// Return the number of parameters in the model
   int getNumberOfParameters() const { return m_par_domain.getNumberOfParameters(); };

   /// Return the minimum value allowed for the _t_ - parameter of fitting <br> <br>
   /// Referenced by Population::init(), Population::moveParticles()
   double getParameterMin(size_t t) { return m_par_domain.getParameterMin(t); };

   /// Return the maximum value allowed for the _t_ - parameter of fitting <br> <br>
   /// Referenced by Population::init(), Population::moveParticles()
   double getParameterMax(size_t t) { return m_par_domain.getParameterMax(t); };

private:
   int              m_nparticles; /**< Number of particles */
   double           m_cognitive;  /**< Cognitive learning factor */
   double           m_social;     /**< Social learning factor */
   double           m_dumping;    /**<Dumping factor*/
   double           m_vmax;       /**< Maximum distance of movement-per-iteration */
   ParametersDomain m_par_domain; /**< Research domain */
};
#endif
