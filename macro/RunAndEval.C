// analysis
// definition of min and max in horizontal axis


//const double xmin = 200;
//const double xmax = 300; //2024/3/24 RTsuji
//const double xmin = 0;
// const double xmax = 100;
//const double xmax = 150; // 2024/3/24 HJKT
//const double xmin = 140; // 2024/4/14
//const double xmax = 240; // 2024/4/14
//const double xmin = 150; // 2024/4/15
//const double xmax = 250; // 2024/4/15
//const double xmin = -50;   // 2024/6/10 for E545-2
//const double xmax = 150; // 2024/6/10 for E545-2
//const double xmin = -50;   // 2024/6/16 for E545-2
//const double xmax = 150; // 2024/6/16 for E545-2
const double xmin = 20;   // 2024/6/16 for E545-2
const double xmax = 120; // 2024/6/16 for E545-2 p 65 MeV



// definition of min and max for scattering angle to be projected
//const double amin = 2.0;
//const double amax = 3.2;
//const double amax = 3.0; // 2024/3/30 HJKT
//const double amin = 1.0; // 2024/4/14
//const double amax = 3.0; // 2024/4/14
//const double amin = 1.0; // 2024/4/15
//const double amax = 2.0; // 2024/4/15
//const double amin = -1.0; // 2024/6/14 for E545-2
//const double amax = 1.0;  // 2024/6/14 for E545-2
//const double amin = -2.0; // 2024/6/16 for E545-2
//const double amax = 3.0;  // 2024/6/16 for E545-2
//const double amin = -1.0; // 2024/6/16 for E545-2
//const double amax = 3.0;  // 2024/6/16 for E545-2
const double amin = 0.0; // 2024/6/16 for E545-2
const double amax = 2.0;  // 2024/6/16 for E545-2

// run name (run545 for e545??)
const char* name="run";
// conversion 
//const  double mm2keV = 30;
// We found the resolution is actually 39 keV/mm (2024.03.30)
//const  double mm2keV = 31;
//const  double mm2keV = 20.7;
//const  double mm2keV = 27.8; // 2024/6/10 for E545-2
//const  double mm2keV = 28.7; // 2024/6/14 for E545-2
//const  double mm2keV = 26.2; // 2024/6/16 for E545-2
//const  double mm2keV = 3352.62/120.0; // 2024/6/16 for E545-2
const  double mm2keV = 5.7; // 2024/6/16 for E545-2


TF1* Fit(TH1 *h1)
{
   int ibin = h1->GetMaximumBin();
   double maxx = h1->GetXaxis()->GetBinCenter(ibin);
   //h1->GetXaxis()->SetRangeUser(maxx-30.,maxx+30);
   //h1->Fit("gaus","L");
   //h1->Fit("gaus","L","",maxx-10,maxx+10);
	 //h1->GetXaxis()->SetRangeUser(maxx-40.,maxx+40); 2024.06.14
	 //h1->GetXaxis()->SetRangeUser(maxx-50.,maxx+50); 2024.06.16
	 //h1->GetXaxis()->SetRangeUser(maxx-30.,maxx+30); //2024.06.16
	 h1->GetXaxis()->SetRangeUser(maxx-20.,maxx+20); //2024.06.16
	 //h1->Fit("gaus","L");
	 //h1->Fit("gaus","L","",maxx-30,maxx+30);
	 //h1->Fit("gaus","L","",maxx-20,maxx+20);
	 h1->Fit("gaus","L","",maxx-5,maxx+5);

	 return h1->GetFunction("gaus");
}


void RunAndEval(int run) {

//   gApplication->ProcessLine(Form("add steering/chk_spadi.yaml %d",run));
//   gApplication->ProcessLine(Form("add steering/chk_e583.yaml %d",run));
   // E559(2024 Apr)
   //TString pdffile(Form("$HOME/HTMLpub/eres/2024Mar/run%04d.pdf",run));
   //TString txtfile(Form("$HOME/HTMLpub/eres/2024Mar/run%04d.txt",run));
   // E545-2(2024 Jun.)
   TString pdffile(Form("$HOME/HTMLpub/eres/e545-2/run%04d.pdf",run));
   TString txtfile(Form("$HOME/HTMLpub/eres/e545-2/run%04d.txt",run));
   
   gApplication->ProcessLine(Form("add steering/chkres.tmpl.yaml NAME=%s NUM=%04d",name,run));
   art::TLoopManager::Instance()->GetLoop(0)->Resume();
   
   gApplication->ProcessLine("fcd 0");
   TTree *tree = (TTree*) gDirectory->Get("tree");
   //TH2* h2 = new TH2F("hGRAX","GR A vs X",100,xmin,xmax,100,-3.,4.);
   TH2* h2 = new TH2F("hGRAX","GR A vs X",200,xmin,xmax,100,-3.,4.);
   //   tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX>>hGRAX");
   //   tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+vdc_gr_m.fA*300.>>hGRAX");
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+vdc_gr_m.fA*TMath::RadToDeg()*10.>>hGRAX"); // 2024.3.30
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+vdc_gr_m.fA*TMath::RadToDeg()*6.8>>hGRAX"); // 2024.3.30 14:48
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+vdc_gr_m.fA*TMath::RadToDeg()*12.422>>hGRAX"); // 2024.6.14
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+vdc_gr_m.fA*756.232+4010.5*pow(vdc_gr_m.fA,2)-3.79115*vdc_gr_m.fA*TMath::RadToDeg()>>hGRAX"); // 2024.6.14
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX>>hGRAX"); // 2024.6.15
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+0.00422349*pow(vdc_gr_m.fA*1e3,2)+85.4602*vdc_gr_m.fA-3.37311*TMath::RadToDeg()*vdc_gr_m.fA>>hGRAX"); // 2024.6.16
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+0.00371026*pow(vdc_gr_m.fA*1e3,2)+7.13772*vdc_gr_m.fA>>hGRAX"); // 2024.6.16
   //tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+1.44775*pow(vdc_gr_m.fA*TMath::RadToDeg(),2)-0.389743*vdc_gr_m.fA*TMath::RadToDeg()>>hGRAX"); // 2024.6.17
   tree->Draw("vdc_gr_m.fA*TMath::RadToDeg():vdc_gr_m.fX+113.685*vdc_gr_m.fA>>hGRAX"); // 2024.6.21
   h2->Draw("colz");
   // e583
   // double amin = 2.;
   // double amax = 2.5;
   gApplication->ProcessLine(Form("bnx 2 %f %f",amin,amax));
   gApplication->ProcessLine("hGRAX_bnx->Draw()");

   TH1 *h2d_bnx = (TH1*)gDirectory->Get("hGRAX_bnx");
   h2d_bnx->SetTitle(Form("GR X(mm) (%.2f < A < %.2f)",amin,amax));
   h2d_bnx->SetName("hGRXcA");
   gApplication->ProcessLine("zon 1 2");
   gApplication->ProcessLine("ht 2 colz");
   gApplication->ProcessLine("ht 3");
   double sigma = -1;
   if (h2d_bnx->GetEntries() >0) {
      TF1* gaus = Fit(h2d_bnx);
      sigma = gaus->GetParameter(2);
      gApplication->ProcessLine(Form("gcom run%04d #sigma = %.3f (mm) FWHM %.3f keV",run,gaus->GetParameter(2),gaus->GetParameter(2) * mm2keV * 2.35));
   } else {
      gApplication->ProcessLine(Form("gcom run%04d",run));
   }
//   const char* filename = Form("/home/e583/work/e583/analysis/figs/run%04d.pdf",run);
///*
   gApplication->ProcessLine(Form("artcanvas->SaveAs(\"%s\")",pdffile.Data()));
   //gApplication->ProcessLine(Form(".! echo %s run%04d  sigma_x = %10.5f mm FWHM %10.5f keV assuming %.3f keV/mm >> %s",
   gApplication->ProcessLine(Form(".! echo %s run%04d  sigma_x = %10.5f mm FWHM %10.5f keV assuming %.3f keV/mm (p 65 MeV) >> %s",
                                  TDatime().AsString(),run,sigma,sigma * mm2keV* 2.35, mm2keV, txtfile.Data()));
//*/
                                  
//   gApplication->ProcessLine(Form(".! ssh saho-a lpr -P acc2570 %s",filename));
///   gApplication->ProcessLine(Form(".! ssh saho-a lpr -P rcc4000b %s",filename));
   //   gApplication->Terminate();
}



  

