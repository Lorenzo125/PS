int main (){
  TCanvas *c1 = new TCanvas ("c1","",1500,500);
  c1->Divide(2,1);
  TFile *f = TFile::Open("PS_20_5000_2_2_0.05.root", "READ");
  //TFile *f = TFile::Open("test_J_64_02.root", "READ");
  TGraphAsymmErrors *g = new TGraphAsymmErrors();
  f->GetObject("chi_trend", g);
  g->GetXaxis()->SetTitle("# generation");
  g->GetYaxis()->SetTitle("#chi^{2}/NDOF");
  g->SetFillColor(4);
  g->SetFillStyle(3005);
  g->SetTitle("#chi^{2}/NDOF trend versus n. iterations");
  c1->cd(2);
  g->Draw("a3");
  //g->Draw("same");	
  c1->cd(1);
  TH1F * h1 = (TH1F *) f->Get("best_chi");
  //h1->SetTitle("#chi^{2} - best #chi^{2} frequency on 50 runs");
  h1->SetTitle("#chi^{2}/NDOF frequency on 50 runs");
  h1->GetYaxis()->SetTitle("frequency");
  //h1->GetXaxis()->SetTitle("#chi^{2} - best #chi^{2}");
  h1->GetXaxis()->SetTitle("#chi^{2}/NDOF");
  h1 -> Draw("HIST");
  /*c1->cd(2);
  TH1F * time = (TH1F *) f->Get("time");
  time->SetTitle("time required frequency on 50 runs");
  time->GetYaxis()->SetTitle("frequency");
  time->GetXaxis()->SetTitle("time required");
  time -> Draw("HIST");*/
}
