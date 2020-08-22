n #ifndef Evaluate_h
#define Evaluate_h

#include <random>
#include "TH1F.h"
#include "Population.h"

   class Evaluate {
public:
   /// Compute the chi2/Ndof using the coordinates of the current position of the particle as parameters in the model
   /// <br> <br> The chi2/Ndof is assigned to the particle as cost to be minimized
   static void computeCostFit(Particle &t_par, TH1F *t_data, TF1 *t_model, double t_Ndof)
   {
      double chi2 = 0., x = 0., y = 0., c = 0., e = 0.;
      TAxis *xAxis = t_data->GetXaxis();
      t_par.setModel(t_model);
      chi2 = 0.;
      for (size_t i = 1; i <= t_data->GetNbinsX(); i++) {
         x = xAxis->GetBinCenter(i);
         c = t_data->GetBinContent(i);
         e = t_data->GetBinError(i);
         if (e == 0) continue;
         chi2 += TMath::Power((c - t_model->Eval(x)) / e, 2);
      };
      t_par.setCost(chi2 / t_Ndof);
   };

   /// Compute the chi2/Ndof for each particle in the population <br> <br>
   static void computeCostFit(Population &t_pop, TH1F *t_data, TF1 *t_model, double t_Ndof)
   {
      for (size_t i = 0; i < t_pop.size(); ++i) {
         computeCostFit(t_pop[i], t_data, t_model, t_Ndof);
      };
   };
};

#endif
