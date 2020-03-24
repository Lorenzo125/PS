#ifndef Evaluate_h
#define Evaluate_h

#include "Population.h"
#include "TH1F.h"
#include <random>

class Evaluate {
public:
  static void ComputeCost_Fit(Particle& par, TH1F* data, TF1* model, double Ndof) {
    double chi2 = 0., x = 0., y = 0., c = 0., e = 0.;
    double dx = data->GetEntries()*data->GetBinWidth(1);
    TAxis* xAxis = data->GetXaxis();
    par.UpdateModel(model);
    chi2 = 0.;
    for (size_t m = 1; m <= data->GetNbinsX(); m++) {
      x = xAxis->GetBinCenter(m);
      c = data->GetBinContent(m)/dx; // c*BinWidth=Contenent/Entries --> ho normalizzato c
      e = data->GetBinError(m)/dx;
      if (e == 0) continue;
      chi2 += TMath::Power((c-model->Eval(x))/e, 2); //SSE
    };
    par.SetCost(chi2/Ndof); //SSE/NDOF
  };

  static void ComputeCost_Fit(Population& pop, TH1F* data, TF1* model, double Ndof) {
    for (size_t i = 0; i < pop.Size(); ++i) {
      ComputeCost_Fit(pop[i], data, model, Ndof);
    };
  };

  static double ComputeSST(TH1F* data){
    double SST = 0., x = 0., y = 0., c = 0., e = 0.;
    double dx = data->GetEntries()*data->GetBinWidth(1);
    double n = data->GetNbinsX();
    TAxis* xAxis = data->GetXaxis();
    double average=0.;

    for (size_t m = 1; m <= n; m++){ //calcolo media
      average+=data->GetBinContent(m)/(dx*n);
    };

    for (size_t m = 1; m <= n; m++) {
      c = data->GetBinContent(m)/dx; // c*BinWidth=Contenent/Entries --> ho normalizzato c
      e = data->GetBinError(m)/dx;
      if (e == 0) continue;
      SST += TMath::Power((c-average)/e, 2);
    };
    return SST;
  };

};


#endif
