#ifndef Parameter_h
#define Parameter_h

#include <string>
#include <vector>

class Parameter {
public:
   /// Parameter default constructor <br> <br>
   /// The parameter stores the name and the minimum and maximum values allowed for a fitting parameter
   Parameter()
   {
      m_name    = "";
      m_min_val = 0.;
      m_max_val = 0.;
   };

   std::string m_name /**Name of the parameter*/;
   double      m_min_val /**Minimum value allowed for the parameter*/;
   double      m_max_val /**Maximum value allowed for the parameter*/;
};

class ParametersDomain {
public:
   /// ParametersDomain default constructor
   ParametersDomain();

   /// ParametersDomain constructor for a set of _n_ - parameters
   ParametersDomain(int n);

   /// Set the _t_ - parameter with the name and the domain extreme values
   void setParameterDomain(size_t t, std::string t_name, double t_min, double t_max);

   /// Return the number of parameters <br> <br>
   /// Referenced by Config::getNumberOfParameters()
   size_t getNumberOfParameters() const;

   /// Return the minimum value allowed for the _t_ - parameter <br> <br>
   /// Referenced by Config::getParameterMin()
   double getParameterMin(size_t t);

   /// Return the maximum value allowed for the _t_ - parameter <br> <br>
   /// Referenced by Config::getParameterMax()
   double getParameterMax(size_t t);

   /// Return the _t_ - parameter
   Parameter &operator[](size_t t) { return m_par[t]; };

private:
   std::vector<Parameter> m_par; /**< Vector of parameters */
};

#endif
