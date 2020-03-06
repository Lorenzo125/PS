#include "ParametersDomain.h"

ParametersDomain::ParametersDomain() :
m_par(0) {};

ParametersDomain::ParametersDomain(size_t s) :
m_par(s) {};

void ParametersDomain::SetParDomain(size_t i, std::string vname, double vmin, double vmax) {
  m_par[i].name = vname;
  m_par[i].min_val = vmin;
  m_par[i].max_val = vmax;
};

double ParametersDomain::ViewParMin(size_t i) {
  return m_par[i].min_val;
};

double ParametersDomain::ViewParMax(size_t i) {
  return m_par[i].max_val;
};

size_t ParametersDomain::NumberOfParameters() const {
  return m_par.size();
};
