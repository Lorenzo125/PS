#include "ParametersDomain.h"

ParametersDomain::ParametersDomain() : m_par(0){};

ParametersDomain::ParametersDomain(size_t n) : m_par(n){};

void ParametersDomain::setParameterDomain(size_t t, std::string t_name, double t_min, double t_max)
{
   m_par[t].m_name    = t_name;
   m_par[t].m_min_val = t_min;
   m_par[t].m_max_val = t_max;
};

double ParametersDomain::getParameterMin(size_t t)
{
   return m_par[t].m_min_val;
};

double ParametersDomain::getParameterMax(size_t t)
{
   return m_par[t].m_max_val;
};

size_t ParametersDomain::getNumberOfParameters() const
{
   return m_par.size();
};
