#include "./ResetHistInJSROOT.C"

TF1* Fit(TH1 *h1)
{
   int ibin = h1->GetMaximumBin();
   double maxx = h1->GetXaxis()->GetBinCenter(ibin);
   h1->GetXaxis()->SetRangeUser(maxx-30.,maxx+30); 
   h1->Fit("gaus","L","",maxx-30,maxx+30);
   return h1->GetFunction("gaus");
}


void startDaq () {
   gSystem->Exec("cd /home/ws-devel/exp/d202407a/art_analysis/user/ota/scripts/ && sh start.sh");
   gSystem->Exec("ssh quser@ata03 /home/quser/repos/exp-config/rcnp_d202407a/run_ata03/post_start.sh");
}

void stopDaq () {
   gSystem->Exec("ssh quser@ata03 /home/quser/repos/exp-config/rcnp_d202407a/run_ata03/pre_stop.sh");
   gSystem->Exec("cd /home/ws-devel/exp/d202407a/art_analysis/user/ota/scripts/ && sh stop.sh");
   gSystem->Exec("cd /home/ws-devel/exp/d202407a/art_analysis/user/ota/scripts/ && sh incrnum.sh");
}

void autoRun() {
   resetAllHistogram();
   startDaq();
   int i = 0;
   TH1 *h2 = (TH1*) gDirectory->FindObject("vdc")->FindObject("hX_cA_cY");
   while (h2->Integral() < 300 && i < 150) {
      gSystem->ProcessEvents();
      gSystem->Sleep(1000);
      i++;
   }
   int run = TString(gSystem->GetFromPipe("redis-cli -h vmeserver1 get run_info:run_number")).Atoi();
   stopDaq();

   TString pdffile(Form("/home/ws-devel/exp/d202407a/art_analysis/user/ota/eres/run%04d.pdf",run));
   TString txtfile(Form("/home/ws-devel/exp/d202407a/art_analysis/user/ota/eres/run%04d.txt",run));
   double mm2keV = 9.;
   double sigma = Fit(h2)->GetParameter(2);
   gApplication->ProcessLine("ht vdc/hX_cA_cY");
   gApplication->ProcessLine(Form("gcom run%04d FWHM %10.5f keV",run,sigma * mm2keV * 2.35));
   gApplication->ProcessLine(Form(".! echo \"%s run%04d  sigma_x = %10.5f mm FWHM %10.5f keV assuming %.3f keV/mm (a 100 MeV) \"> %s",
                                  TDatime().AsString(),run,sigma,sigma * mm2keV* 2.35, mm2keV, txtfile.Data()));
   
   gApplication->ProcessLine(Form("artcanvas->SaveAs(\"%s\")",pdffile.Data()));

//   TH2 *h2 = (TH2*) gDirectory->cd("vdc")->Get("hXA");
}
void online () {

   THttpServer *server = new THttpServer("http:5955");
   server->RegisterCommand("/expert/autoRun","autoRun()");
   server->RegisterCommand("/resetAllHistogram", "resetAllHistogram()");
   server->RegisterCommand("/expert/startDaq", "startDaq()");
   server->RegisterCommand("/expert/stopDaq", "stopDaq()");

   gApplication->ProcessLine("add steering/online.tmpl.yaml");
   gApplication->ProcessLine("res");
}
