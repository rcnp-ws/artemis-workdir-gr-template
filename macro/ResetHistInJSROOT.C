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
