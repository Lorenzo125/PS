#ifndef Evaluate_h
#define Evaluate_h

#include "Population.h"
#include "TH1F.h"
#include <random>

class Evaluate {
public:
  static void ComputeCost_Fit(Particle& par, TH1F* data, TF1* model, double Ndof) {
    double chi2 = 0., x = 0., y = 0., c = 0., e = 0.;
    TAxis* xAxis = data->GetXaxis();
    par.UpdateModel(model);
    chi2 = 0.;
      for (size_t m = 1; m <= data->GetNbinsX(); m++) {
        x = xAxis->GetBinCenter(m);
        c = data->GetBinContent(m)/(data->GetEntries()*data->GetBinWidth(1));
        e = data->GetBinError(m)/(data->GetEntries()*data->GetBinWidth(1));
         if (e == 0) continue;
         chi2 += TMath::Power((c-model->Eval(x))/e, 2);
       };
    par.SetCost(chi2/Ndof);
    };

    static void ComputeCost_Fit(Population& pop, TH1F* data, TF1* model, double Ndof) {
      for (size_t i = 0; i < pop.Size(); ++i) {
        ComputeCost_Fit(pop[i], data, model, Ndof);
      }
    };

    static void ComputeCost (Particle& part, TF1* model){
      part.UpdateModel(model);
      part.SetCost(model->Eval(0,0,0,0));
    };

    static void ComputeCost (Population& pop, TF1* model) {
      for (size_t i = 0; i < pop.Size(); ++i) {
        ComputeCost(pop[i], model);
      };
    };

  };


#endif
