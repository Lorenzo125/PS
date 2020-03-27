#include <iostream>
#include <algorithm>

#include "Evaluate.h"
#include "UpBest.h"
#include "UpVel.h"
#include "Move.h"
#include "Evaluate.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TH2.h"

struct iteration_char { //riassume i risultati dell'i-esima iterazioni per tutte le run
std::vector <double> chi; //il primo elemento del vettore rappresenta il chi del migliore cromosoma della prima run
double average; //media di tutti i chi
};

int main(int argc, char *argv[]) {
  std::cout << ">>> Particle swarm optimization" << std::endl;
  TApplication *app = new TApplication("app",0,0);
  Config conf;

  int NumRun = 10; //numero run
  conf.num_particles = 5000; //numero particelle
  conf.cognitive_par = 2.0; //numero fattore cognitivo --> mi definiscono come sono influenzate le singole particelle dai propri migliori risultati
  conf.social_par = 2.0; //numero fattore sociale --> mi definiscono come si influenzano reciprocamente le partcelle
  conf.Vmax = 0.01; //velocità massima per ridurre oscillazioni

  std::vector<struct iteration_char> r (2000); //definisco numero iterazioni, inizializzo vettore che raccoglie i dati

  TFile *f = new TFile("data_J_10000.root","READ");
  TH1F * data = (TH1F *) f->Get("data"); //acquisisce i dati
  //TFile *file = TFile::Open("PS_Vel_0.01.root", "RECREATE");
  //TH2F *best_chi = new TH2F("best_chi","PS Fit",1000, 0, 6000,1000, 0, 2000); //raccoglie i dati sul chi2, X->num part, Y->num iter, salvato su file root esterno
  TFile *file = new TFile("PS_Vel_0.01a.root","READ");
  TH2F * best_chi = (TH2F *) file->Get("best_chi"); //acquisisce i dati

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
  conf.ParDomain = domain; //assegno il dominio alla popolazione di particelle

  double Ndof = (data->GetNbinsX()-model->GetNumberFreeParameters()); //numero di gradi di libertà

  for (int v = 1; v <= NumRun; v++){ //per eseguire diverse run di seguito

    std::cout << "Run" << v << std::endl;

    Population pop(conf); //assegno la configurazione alla popolazione
    pop.Init(); //inizializzo la popolazione di particelle

    Evaluate::ComputeCost_Fit(pop, data, model,Ndof); //calcola il costo nelle posizioni iniziali
    UpBest::First_Update(pop); //imposta tale costo come migliore trovato dalla singola particella
    pop.Sort(); //ordina le particelle in base al costo migliore trovato dalla particella, la prima nel vettore sarà col costo minore

    std::cout << "--- Original population ---" << std::endl;
    std::cout << pop << std::endl;

    for (auto i = 0; i < r.size(); i++) {
      UpVel::Update_Vel(pop); //calcola la velocità per ogni particella
      Move::Change(pop); //la particella si sposta da quella posiione con quella velocià
      Evaluate::ComputeCost_Fit(pop, data, model,Ndof); //calcolo il chi nelle nuove posizioni
      UpBest::Update(pop); //aggiorno la migliore posizione della singola particella
      pop.Sort(); //riordino le particelle
      r[i].chi.push_back(pop.AccessParticle(0).ViewBestCost()); //salvo il migliore costo di questa iterazione
      std::cout << "--- Iteration " << i+1 << std::endl;
      std::cout << pop << std::endl; //riporta le coordinate del punto migliore trovato fino a quell'iterazione
    };
  };

  ////ATTENZIONE! I NUMERI SONO PRESI NON IN MODO AUTOMATICO DALL'ISTOGRAMMA

  int binx = conf.ShowNumParticles()*1000/6000+1;

  for (int i=0; i < r.size();i=i+2){ //risoluzione istrogramma 2000/1000
    r[i].average=(std::accumulate(r[i].chi.begin(), r[i].chi.end(), 0.0))/r[i].chi.size(); //media campionaria
    int biny = i*1000/2000+1;
    //std::cout << i << "_" << binx << "_" << biny << "_" << r[i].average << std::endl;
    best_chi->SetBinContent(binx,biny,r[i].average);
  };

  /*TCanvas *c1 = new TCanvas ("c1","",1500,500);
  best_chi->Draw("LEGO");
  app -> Run();*/


  TFile *file2 = TFile::Open("PS_Vel_0.01b.root", "RECREATE"); //salvo i nuovi dati, poi rinomino a versione a
  file2->cd();
  best_chi->Write("best_chi");
  file2->Save();
  file2->Close();

  delete data;
  delete model;
  return EXIT_SUCCESS;
}
