
TF1* Fit(TH1 *h1)
{
   int ibin = h1->GetMaximumBin();
   double maxx = h1->GetXaxis()->GetBinCenter(ibin);
   h1->GetXaxis()->SetRangeUser(maxx-20.,maxx+20);
   h1->Fit("gaus");
   return h1->GetFunction("gaus");
}


void autoRun() {

   TH2F *h2 = gROOT->cd("vdc")->FindObject("hXA");
   TH1F *h1 = gROOT->cd("vdc")->FindObject("hX_cA");
   
   art::TCmdSave::Instance()->SetDefaultDirectory("/home/ws-devel/exp/d202407a/figs/");

   gApplication->ProcessLine("zon 1 2");
   gApplication->ProcessLine("ht hXA");
   gApplication->ProcessLine("ht hX_cA");

   if (h1->GetEntries() > 0) {
      TF1 *gaus = Fit(h1);
      gApplication->ProcessLine(Form("gcom run%04d #sigma = %.3f (mm)",run,gaus->GetParameter(2)));
   } else {
      gApplication->ProcessLine(Form("gcom run%04d",run));
   }      
   
}
