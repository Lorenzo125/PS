#include <iostream>
#include <algorithm>

#include "TFile.h"
#include "Evaluate.h"

int main(int argc, char *argv[])
{
   std::cout << ">>> Particle swarm optimization" << std::endl;
   Config conf;

   conf.setNumberOfParticles(500);
   conf.setCognitiveParameter(2.0);
   conf.setSocialParameter(2.0);
   conf.setVMaxParameter(0.01);
   conf.setDumpingFactor();
   size_t iter = 5000;

   TFile *f   = new TFile("data_J_10000.root", "READ");
   TH1F * aux = (TH1F *)f->Get("data");

   // clone the initial data in order to normalize and use it without work on the original source

   TH1F *data = (TH1F *)aux->Clone();
   data->Scale(1 / (data->GetEntries() * data->GetBinWidth(1)));

   TF1 *model = new TF1("model",
                        "[12]*([0]*([1]*ROOT::Math::crystalball_function(x, [6], [5], [7]*[3], [8]+[4]) + "
                        "(1.-[1])*ROOT::Math::crystalball_function(x, [6], [5], [7], [8])) + (1.-[0])*([2]*exp([11]*x) "
                        "+ (1.-[2])*(1.-TMath::Erf((x-[10])/[9]))*0.5))",
                        1.50, 8.70);

   ParametersDomain domain(model->GetNumberFreeParameters());

   // domain of parameters

   /*domain.setParameterDomain(0, "p0", 1e-1, 9e-1);
   domain.setParameterDomain(1, "p1", 0.001, 0.10);
   domain.setParameterDomain(2, "p2", 5e-2, 8e-1);
   domain.setParameterDomain(3, "p3", 1.00, 1.10);
   domain.setParameterDomain(4, "p4", 0.580, 0.600);
   domain.setParameterDomain(5, "p5", 5, 20);
   domain.setParameterDomain(6, "p6", 0.5, 2.0);
   domain.setParameterDomain(7, "p7", 0.03, 0.14);
   domain.setParameterDomain(8, "p8", 3.0, 3.15);
   domain.setParameterDomain(9, "p9", 0.3, 1.4);
   domain.setParameterDomain(10, "p10", 1.2, 3.6);
   domain.setParameterDomain(11, "p11", -1, 0);
   domain.setParameterDomain(12, "p12", 1.10, 1.80);*/

   domain.setParameterDomain(0, "p0", 0.218, 0.654);
   domain.setParameterDomain(1, "p1", 0.007, 0.02);
   domain.setParameterDomain(2, "p2", 0.176, 0.529);
   domain.setParameterDomain(3, "p3", 0.50, 1.50);
   domain.setParameterDomain(4, "p4", 0.290, 0.870);
   domain.setParameterDomain(5, "p5", 10, 30);
   domain.setParameterDomain(6, "p6", 0.523, 1.57);
   domain.setParameterDomain(7, "p7", 0.035, 0.104);
   domain.setParameterDomain(8, "p8", 1.549, 4.647);
   domain.setParameterDomain(9, "p9", 0.341, 1.022);
   domain.setParameterDomain(10, "p10", 1.262, 3.787);
   domain.setParameterDomain(11, "p11", -0.747, -0.249);
   domain.setParameterDomain(12, "p12", 0.762, 2.286);
   conf.setParametersDomain(domain);

   double Ndof = (data->GetNbinsX() - model->GetNumberFreeParameters());

   Population pop(conf);
   pop.init();
   Evaluate::computeCostFit(pop, data, model, Ndof);

   for (auto i = 0; i < pop.size(); i++) { // start with a initial best position
      pop[i].setBestPosition();
   };

   pop.sort();

   std::cout << "--- Original population ---" << std::endl;
   std::cout << pop << std::endl;

   for (auto i = 0; i < iter; i++) {
      pop.setVelocity();
      pop.moveParticles();
      Evaluate::computeCostFit(pop, data, model, Ndof);
      pop.setBestCost();
      pop.sort();
      std::cout << "--- Iteration " << i + 1 << std::endl;
      std::cout << pop << std::endl;
   };

   pop.draw(data, model);

   delete data;
   delete model;
   return EXIT_SUCCESS;
};
