#include <iostream>
#include <algorithm>

#include "Evaluate.h"
#include "UpBest.h"
#include "UpVel.h"
#include "Move.h"
#include "Evaluate.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"

#define NumRun 50 //nmero run del programma
#define NumIte 1000 //numero iterazione per run
#define NumBestChi 1000 //numero delle iterazioni del chi che scelgo di mostrare nel grafico chi_trend

struct iteration_char { //riassume i risultati dell'i-esima iterazioni per tutte le run
std::vector <double> chi; //il primo elemento del vettore rappresenta il chi del migliore cromosoma della prima run
double average; //media di tutti i chi
double variance; //varianza della popolazione di chi
};

int main(int argc, char *argv[]) {
  std::cout << ">>> Particle swarm optimization" << std::endl;
  std::vector<struct iteration_char> r (NumIte);

  Config conf;
  conf.num_particles = 20; //numero particelle
  conf.cognitive_par = 4.0; //numero fattore cognitivo --> mi definiscono come sono influenzate le singole particelle dai propri migliori risultati
  conf.social_par = 4.0; //numero fattore sociale --> mi definiscono come si influenzano reciprocamente le partcelle
  conf.Vmax = 0.1; //velocità massima per ridurre oscillazioni

  TFile *f = new TFile("data_J_10000.root","READ");
  TH1F * data = (TH1F *) f->Get("data"); //acquisisce i dati
  TH1F *best_chi = new TH1F("best_chi","PS Fit",10000, 0, 50); //grafico che rappresenta la frequenza dei vari R2
  TH1F *best_R2 = new TH1F("best_R2","PS Fit",10000, -0.2, 1.0); //grafico che rappresenta la frequenza dei vari R2
  TGraphAsymmErrors *chi_trend = new TGraphAsymmErrors(); //creo il grafico andamento chi medio con relativa banda di errore standard


  TF1* model = new TF1("model","[12]*([0]*([1]*ROOT::Math::crystalball_function(x, [6], [5], [7]*[3], [8]+[4]) + (1.-[1])*ROOT::Math::crystalball_function(x, [6], [5], [7], [8])) + (1.-[0])*([2]*exp([11]*x) + (1.-[2])*(1.-TMath::Erf((x-[10])/[9]))*0.5))", 1.50, 8.70);
  ParametersDomain domain(model->GetNumberFreeParameters()); //imposto dominio in cui possono variare i parametri
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
  domain.SetParDomain(12, "p12", 1.10, 1.80); //non è normalizzato il la funzione J iniziale
  //domain.SetParDomain(0, "p0", 4.3588e-01, 4.3588e-01);// valori esatti
  //domain.SetParDomain(1, "p1", 1.3231e-02, 1.3231e-02);//
  //domain.SetParDomain(2, "p2", 3.5251e-01, 3.5251e-01);//
  //domain.SetParDomain(3, "p3", 1.00, 1.00);//
  //domain.SetParDomain(4, "p4", 0.580, 0.580);//
  //domain.SetParDomain(5, "p5", 20, 20);//H
  //domain.SetParDomain(6, "p6", 1.0464, 1.0464);//
  //domain.SetParDomain(7, "p7", 6.9119e-02, 6.9119e-02);//
  //domain.SetParDomain(8, "p8", 3.098, 3.098);//H
  //domain.SetParDomain(9, "p9", 6.8136e-01, 6.8136e-01);//H
  //domain.SetParDomain(10, "p10", 2.5249, 2.5249);//
  //domain.SetParDomain(11, "p11", -4.9824e-01, -4.9824e-01);//
  //domain.SetParDomain(12, "p12", 1.00, 2.00);  //1.57033 chi ->1.2521 (lo stesso senza binwidth)
  conf.ParDomain = domain; //assegno il dominio alla popolazione di particelle

  double Ndof = (data->GetNbinsX()-model->GetNumberFreeParameters()); //numero di gradi di libertà

  for (int v = 0; v < NumRun; v++){ //per eseguire diverse run di seguito

  std::cout << "Run" << v << std::endl;

  Population pop(conf); //assegno la configurazione alla popolazione
  pop.Init(); //inizializzo la popolazione di particelle

  Evaluate::ComputeCost_Fit(pop, data, model,Ndof); //calcola il costo nelle posizioni iniziali
  UpBest::First_Update(pop); //imposta tale costo come migliore trovato dalla singola particella
  pop.Sort(); //ordina le particelle in base al costo migliore trovato dalla particella, la prima nel vettore sarà col costo minore

  std::cout << "--- Original population ---" << std::endl;
  std::cout << pop << std::endl;

  for (auto i = 0; i < NumIte; ++i) {
    UpVel::Update_Vel(pop); //calcola la velocità per ogni particella
    Move::Change(pop); //la particella si sposta da quella posiione con quella velocià
    Evaluate::ComputeCost_Fit(pop, data, model,Ndof); //calcolo il chi nelle nuove posizioni
    UpBest::Update(pop); //aggiorno la migliore posizione della singola particella
    pop.Sort(); //riordino le particelle
    r[i].chi.push_back(pop.AccessParticle(0).ViewBestCost()); //salvo il migliore costo di questa iterazione
    std::cout << "--- Iteration " << i+1 << std::endl;
    std::cout << pop << std::endl; //riporta le coordinate del punto migliore trovato fino a quell'iterazione
  };
  double SST=Evaluate::ComputeSST(data);
  double SSEn=pop.AccessParticle(0).ViewBestCost(); //è gia il SSE/NDOF
  double R2 = 1.0 - (SSEn/SST * (data->GetNbinsX()-1));
  best_R2->Fill(R2); //salvo il migliore R2 nel grafico best_R2
  best_chi->Fill(pop.AccessParticle(0).ViewBestCost());
};


  for (int i=0; i<NumIte;i++){
    r[i].average=(std::accumulate(r[i].chi.begin(), r[i].chi.end(), 0.0))/r[i].chi.size(); //media campionaria
    r[i].variance=(std::inner_product(r[i].chi.begin(),r[i].chi.end(),r[i].chi.begin(),0.0) - r[i].chi.size()*TMath::Power(r[i].average, 2)) /(r[i].chi.size()-1); //varianza della popolazione
  };

  for(int m=1; m<=NumBestChi;m++){ //definzione del grqfico chi_trend
    chi_trend ->SetPoint (m,m, r[m-1].average);
    double err = TMath::Power(r[m-1].variance/r[m-1].chi.size(), 0.5); //errore standard sul valore medio di chi, srqt(varianza popolazione/n)
    chi_trend ->SetPointError(m,0,0, err, err);
  };

  TFile *file = TFile::Open("PS_20_1000_4_4_0.1.root", "RECREATE"); //salvataggio dei risulatati
  file->cd();
  chi_trend->Write("chi_trend");
  best_R2->Write("best_R2");
  best_chi->Write("best_chi");
  file -> Close();

  delete data;
  delete model;
  return EXIT_SUCCESS;
}
