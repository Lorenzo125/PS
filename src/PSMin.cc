#include <iostream>
#include <algorithm>

#include "Evaluate.h"
#include "UpBest.h"
#include "UpVel.h"
#include "Move.h"
#include "Evaluate.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"

struct iteration_char { //riassume i risultati dell'i-esima iterazioni per tutte le run
std::vector <double> chi; //il primo elemento del vettore rappresenta il chi del migliore cromosoma della prima run
double average; //media di tutti i chi
double variance;
};

int main(int argc, char *argv[]) {
  std::cout << ">>> Particle swarm optimization" << std::endl;
  std::vector<struct iteration_char> r (6000); //ad ogni elemento corrisponde l'iterazione

  Config conf;
  conf.num_particles = 20;
  conf.cognitive_par = 2.0;
  conf.social_par = 2.0;
  conf.Vmax = 0.05;

  TFile *f = new TFile("data_J_10000.root","READ");
  TH1F * data = (TH1F *) f->Get("data");
  TH1F *best_chi = new TH1F("best_chi","PS Fit", 500, 0, 10);


  TF1* model = new TF1("model","[12]*([0]*([1]*ROOT::Math::crystalball_function(x, [6], [5], [7]*[3], [8]+[4]) + (0.90-[1])*ROOT::Math::crystalball_function(x, [6], [5], [7], [8])) + (1-[0])*([2]*exp([11]*x) + (1.0-[2])*(1-TMath::Erf((x-[10])/[9]))*0.5))", 1.50, 8.70);
  ParametersDomain domain(model->GetNumberFreeParameters());
  domain.SetParDomain(0, "p0", 1e-1, 9e-1);
  domain.SetParDomain(1, "p1", 0.001, 0.10);
  domain.SetParDomain(2, "p2", 5e-2, 8e-1);
  domain.SetParDomain(3, "p3", 1.00, 1.10);
  domain.SetParDomain(4, "p4", 0.580, 0.600);
  domain.SetParDomain(5, "p5", 5, 20);
  domain.SetParDomain(6, "p6", 0.5, 2.0);
  domain.SetParDomain(7, "p7", 0.03, 0.14);
  domain.SetParDomain(8, "p8", 3.0, 3.15);
  domain.SetParDomain(9, "p9", 0.3, 1.4);
  domain.SetParDomain(10, "p10", 1.2, 3.6);
  domain.SetParDomain(11, "p11", -1,  0);
  domain.SetParDomain(12, "p12", 1.10, 1.80);
  //domain.SetParDomain(0, "p0", 4.3588e-01, 4.3588e-01);//
  //domain.SetParDomain(1, "p1", 1.3231e-02, 1.3231e-02);//
  //domain.SetParDomain(2, "p2", 3.5251e-01, 3.5251e-01);//
  //domain.SetParDomain(3, "p3", 1.00, 1.00);//
  //domain.SetParDomain(4, "p4", 0.580, 0.580);//
  //domain.SetParDomain(5, "p5", 20, 20);//
  //domain.SetParDomain(6, "p6", 1.0464, 1.0464);//
  //domain.SetParDomain(7, "p7", 6.9119e-02, 6.9119e-02);//
  //domain.SetParDomain(8, "p8", 3.098, 3.098);//
  //domain.SetParDomain(9, "p9", 6.8136e-01, 6.8136e-01);//
  //domain.SetParDomain(10, "p10", 2.5249, 2.5249);//
  //domain.SetParDomain(11, "p11", -4.9824e-01, -4.9824e-01);//
  //domain.SetParDomain(12, "p12", 1.00, 2.00);  //1.57033 
  conf.ParDomain = domain;

  double Ndof = (data->GetNbinsX()-model->GetNumberFreeParameters());

  for (int v = 0; v < 50; v++){

  std::cout << "Run" << v << std::endl;

  Population pop(conf);
  pop.Init();

  Evaluate::ComputeCost_Fit(pop, data, model,Ndof);
  UpBest::First_Update(pop);
  pop.Sort();

  std::cout << "--- Original population ---" << std::endl;
  std::cout << pop << std::endl;

  for (auto i = 0; i < 1000; ++i) {
    UpVel::Update_Vel(pop);
    Move::Change(pop);
    Evaluate::ComputeCost_Fit(pop, data, model,Ndof);
    UpBest::Update(pop);
    pop.Sort();
    std::cout << "--- Iteration " << i+1 << std::endl;
    std::cout << pop << std::endl;
    r[i].chi.push_back(pop.AccessParticle(0).ViewBestCost());
  };

  best_chi->Fill(pop.AccessParticle(0).ViewBestCost());

};


  for (int i=0; i<1000;i++){ //oridno e trovo la media e varianza per ogni iterazione
    std::sort(r[i].chi.begin(), r[i].chi.end());
    double sum=0.;
    for(int l=0; l < r[i].chi.size(); l++){
      sum+=r[i].chi[l];
    };
    r[i].average=sum/r[i].chi.size();
    r[i].variance=0.;
    for(int l=0; l < r[i].chi.size(); l++){
      r[i].variance+=TMath::Power(r[i].chi[l]-r[i].average, 2)/(r[i].chi.size()-1);
    };
  };
  TFile *file = TFile::Open("PS_20_5000_2_2_0.05.root", "RECREATE");
  TGraphAsymmErrors *chi_trend = new TGraphAsymmErrors();
  for(int m=1; m<=500;m++){
    chi_trend ->SetPoint (m,m, r[m-1].average);
    chi_trend ->SetPointError(m,0,0, TMath::Power(r[m-1].variance/r[m-1].chi.size(), 0.5), TMath::Power(r[m-1].variance/r[m-1].chi.size(), 0.5));
  };
  file->cd();
  chi_trend->Write("chi_trend");
  best_chi->Write("best_chi");
  file -> Close();

  delete data;
  delete model;
  return EXIT_SUCCESS;
}
