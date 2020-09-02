#include <iostream>
#include <algorithm>

#include "TFile.h"
#include "Evaluate.h"

int main(int argc, char *argv[])
{
   Config conf;

   conf.setNumberOfParticles(500);
   conf.setCognitiveParameter(2.0);
   conf.setSocialParameter(2.0);
   conf.setVMaxParameter(0.05);
   conf.setInertia(0.4);

   // max number of iterations allowed
   double iter_max = 10000;
   // max number of iterations with the same best cost (with a tollerance toll)
   size_t stuck_max = 200;
   double toll      = 1e-3;

   TApplication *app = new TApplication("app", 0, 0);

   // import the dataset from a .root  file
   TFile *f   = new TFile("XXX.root", "READ");
   TH1F * aux = (TH1F *)f->Get("data");
   //

   // clone the initial data and normalize the histogram
   TH1F *data = (TH1F *)aux->Clone();
   if (data->GetSumw2N() == 0) data->Sumw2(kTRUE);
   data->Scale(1 / (data->GetEntries() * data->GetBinWidth(1)));
   //

   // define the model as a parametric function
   TF1 *model = new TF1("model", "XXX", XX, XX);
   //

   ParametersDomain domain(model->GetNumberFreeParameters());

   // for every parameter in the model
  domain.setParameterDomain(a, "",XX, XX));
  domain.setParameterDomain(b, "",XX, XX));
  //

  conf.setParametersDomain(domain);

  double Ndof = (data->GetNbinsX() - model->GetNumberFreeParameters());

  std::vector<double> chi_run; 

  Population pop(conf);

  pop.init();
  Evaluate::computeCostFit(pop, data, model, Ndof);

  for (auto i = 0; i < pop.size(); i++) {
     pop[i].setBestPosition();
  };

  pop.sort();
  chi_run.push_back(pop[0].getBestCost());

  double iter  = 0;
  size_t stuck = 0;

  do {
     iter++;
     pop.setVelocity();
     pop.moveParticles();
     Evaluate::computeCostFit(pop, data, model, Ndof);
     pop.setBestCost();
     pop.sort();
     chi_run.push_back(pop[0].getBestCost());
     if (abs(chi_run[iter - 1] - chi_run[iter]) < toll) {
        stuck++;
     } else
        stuck = 0;
  } while (stuck < stuck_max & iter < iter_max);

  std::cout << pop << std::endl;

  pop.draw();

  delete data;
  delete model;
  return EXIT_SUCCESS;
};
