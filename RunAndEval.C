TF1* Fit(TH1 *h1)
{
   int ibin = h1->GetMaximumBin();
   double maxx = h1->GetXaxis()->GetBinCenter(ibin);
   h1->GetXaxis()->SetRangeUser(maxx-20.,maxx+20);
   h1->Fit("gaus");
   return h1->GetFunction("gaus");
}

void RunAndEval(int run) {

   gApplication->ProcessLine(Form("add steering/chk_spadi.yaml %d",run));
   art::TLoopManager::Instance()->GetLoop(0)->Resume();
   
   
   gApplication->ProcessLine("fcd 0");
   TTree *tree = (TTree*) gDirectory->Get("tree");
   TH2* h2 = new TH2F("hGRAX","GR A vs X",1200,-0.,300.,100,-5.,5.);
   tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX>>hGRAX");
   h2->Draw("colz");
   double amin = 0;
   double amax = 0.5;
   gApplication->ProcessLine(Form("bnx 2 %f %f",amin,amax));
   gApplication->ProcessLine("hGRAX_bnx->Draw()");

   TH1 *h2d_bnx = (TH1*)gDirectory->Get("hGRAX_bnx");
   h2d_bnx->SetTitle(Form("GR X(mm) (%.2f < A < %.2f)",amin,amax));
   h2d_bnx->SetName("hGRXcA");
   art::TCmdSave::Instance()->SetDefaultDirectory("/home/spadi/d202304a/analysis/figs/");
   gApplication->ProcessLine("zon 1 2");
   gApplication->ProcessLine("ht 2 colz");
   gApplication->ProcessLine("ht 3");
   if (h2d_bnx->GetEntries() >0) {
      TF1* gaus = Fit(h2d_bnx);
      gApplication->ProcessLine(Form("gcom run%04d #sigma = %.3f (mm)",run,gaus->GetParameter(2)));
   } else {
      gApplication->ProcessLine(Form("gcom run%04d",run));
   }
   const char* filename = Form("/home/spadi/d202304a/analysis/figs/run%04d.pdf",run);
   gApplication->ProcessLine(Form("artcanvas->SaveAs(\"%s\")",filename));
   gApplication->ProcessLine(Form(".! ssh saho-a lpr -P acc2570 %s",filename));
///   gApplication->ProcessLine(Form(".! ssh saho-a lpr -P rcc4000b %s",filename));

   gApplication->Terminate();
}


