#ifndef Parameter_h
#define Parameter_h

#include <string>
#include <vector>

class Parameter {
public:
  Parameter() {
    name = "";
    min_val = 0.;
    max_val = 0.;
  };

  std::string name;
  double min_val;
  double max_val;
};

class ParametersDomain {
public:
  ParametersDomain();

  ParametersDomain(size_t);

  void SetParDomain(size_t, std::string, double, double);

  size_t NumberOfParameters() const;

  double ViewParMin(size_t i);

  double ViewParMax(size_t i);

  Parameter& operator[](size_t i) {
    return m_par[i];
  };

private:
  std::vector<Parameter> m_par;
};

#endif
