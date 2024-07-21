#include "THttpServer.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TKey.h"
#include <vector>
#include <iostream>

void resetHistogram(TDirectory* dir) {
    TList* lists = (TList *)dir->GetList();
    for(int i=0;i<(int)lists->GetSize();i++){
        if ( lists->At(i)->InheritsFrom(TH1::Class())) {((TH1*) lists->At(i))->Reset();} 
        else if ( lists->At(i)->InheritsFrom(TH2::Class())) {((TH2*)lists->At(i))->Reset();}
    }
}

bool isTDirectory(TObject* obj) { return obj->InheritsFrom("TDirectory");}

void listObjectsInDirectory(TDirectory* dir) {
    TIter next(dir->GetListOfKeys());
    TKey* key;
    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();
        if (obj->InheritsFrom("TDirectory")) {
            listObjectsInDirectory((TDirectory*)obj);
        }
    }
}

void resetAllHistogram() {
    TIter nextFile(gROOT->GetListOfFiles());
    TObject* objFile;
    while ((objFile = nextFile())) {
        TFile* file = (TFile*)objFile;
        listObjectsInDirectory(file);
    }

    TIter nextObj(gROOT->GetList());
    TObject* obj;
    while ((obj = nextObj())) {
        if(obj->InheritsFrom("TDirectory")){
            resetHistogram((TDirectory*)obj);
        }
    }
}

void Shift(const std::string &runnum)
{

   std::string cmd = "add steering/offline.tmpl.yaml NUM=" + runnum;
   gROOT->ProcessLine(cmd.c_str());
   std::cout << "Starting the loop... " << std::endl;

   THttpServer *server = new THttpServer("http:5908");
   server->RegisterCommand("/resetAllHistogram", "resetAllHistogram()");
   
   gROOT->ProcessLine("res");
   gROOT->ProcessLine("sus");

   sleep(5);
   art::TAnalysisInfo * ainfo = (art::TAnalysisInfo*)gROOT->FindObject("analysisInfo");
   TString str_yamlname  = ainfo->GetSteeringFileName();
   TString str_runname   = ainfo->GetRunName();
   TString str_runnumber = ainfo->GetRunNumber();
   TString str_pagetitle = str_runname + str_runnumber +  "(" + str_yamlname + ")";
   server->SetItemField("/", "_title",str_pagetitle.Data());
   server->SetTopName("artemis");
   gROOT->ProcessLine("res");
}
