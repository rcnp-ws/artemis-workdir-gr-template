{
   // style
   gStyle->SetOptStat(1111111);
   gStyle->SetOptFit(1111);
   
   TString dypath = gSystem->GetDynamicPath();
   TString incpath = gSystem->GetIncludePath();
   
   // dypath.Append(":./src/"); // when use original source in src
   // dypath.Append(":{share-path}"); // artemis-cat-src directory

   incpath.Append(gSystem->GetFromPipe("artemis-config --cflags"));
   //incpath.Append(" -Isrc");  // when use original source in src
   //incpath.Append("-I{share-path}"); // artemis-cat-src directory

   gSystem->SetDynamicPath(dypath);
   gSystem->SetIncludePath(incpath);

   // load libraries
   gSystem->Load("libartshare");
   gSystem->Load("libCAT");
   //gSystem->Load("{liborig}"); // when use original library

   TCatCmdFactory *cf = TCatCmdFactory::Instance();
   cf->SetOptExactName(kFALSE);
   cf->Register(TCatCmdHelp::Instance());
   cf->Register(TCatCmdHt::Instance());
   cf->Register(TCatCmdHtp::Instance());
   cf->Register(TCatCmdHb::Instance());
   cf->Register(TCatCmdHn::Instance());
   cf->Register(TCatCmdZone::Instance());
   cf->Register(TCatCmdLs::Instance());
   cf->Register(TCatCmdCd::Instance());
   cf->Register(TCatCmdPrx::Instance());
   cf->Register(TCatCmdPry::Instance());
   cf->Register(TCatCmdAvx::Instance());
   cf->Register(TCatCmdAvy::Instance());
   cf->Register(TCatCmdBnx::Instance());
   cf->Register(TCatCmdBny::Instance());
   cf->Register(new TCatCmdLg(TCatCmdLg::kX,0));
   cf->Register(new TCatCmdLg(TCatCmdLg::kX,1));
   cf->Register(new TCatCmdLg(TCatCmdLg::kY,0));
   cf->Register(new TCatCmdLg(TCatCmdLg::kY,1));
   cf->Register(new TCatCmdLg(TCatCmdLg::kZ,0));
   cf->Register(new TCatCmdLg(TCatCmdLg::kZ,1));
   cf->Register(TCatCmdSly::Instance());
   cf->Register(TCatCmdLoopAdd::Instance());
   cf->Register(TCatCmdLoopResume::Instance());
   cf->Register(TCatCmdLoopSuspend::Instance());
   cf->Register(TCatCmdLoopTerminate::Instance());
   cf->Register(new TCatCmdHstore);
   cf->Register(TCatCmdXval::Instance());
   cf->Register(art::TCatCmdListg::Instance());
//   cf->Register(art::TCmdMWDCCalib::Instance());
//   cf->Register(art::TCmdMWDCConfig::Instance());
//   cf->Register(new art::TCmdFiga);
//   cf->Register(TCmdXsta::Instance());
   cf->Register(new art::TCmdBranchInfo);
   cf->Register(new art::TCmdClassInfo);
   cf->Register(new art::TCmdHdel);
   cf->Register(new art::TCmdFileCd);
   cf->Register(new art::TCmdFileLs);
   cf->Register(art::TCmdPn::Instance());
   cf->Register(art::TCmdPb::Instance());
   cf->Register(art::TCmdPcd::Instance());
   cf->Register(new art::TCmdRg(art::TCmdRg::kX));
   cf->Register(new art::TCmdRg(art::TCmdRg::kY));
   cf->Register(new art::TCmdRg(art::TCmdRg::kZ));
   cf->Register(new art::TCmdSlope);
   cf->Register(art::TCmdPn::Instance());
   cf->Register(art::TCmdPb::Instance());
   cf->Register(art::TCmdPcd::Instance());
   cf->Register(art::TCmdPadZoom::Instance());
   cf->Register(new art::TCmdProcessorDescription);
   cf->Register(new art::TCmdUnZoom);
   cf->Register(new art::TCmdComment);
   cf->Register(new art::TCmdGlobalComment);
   art::TCmdSave * cmdsave = art::TCmdSave::Instance();
   cmdsave->SetDefaultDirectory("figs");
   cmdsave->SetAddDateDir(kTRUE);
   cmdsave->SetAutoName(kTRUE);
   cmdsave->AddFormat("png");
   cmdsave->AddFormat("root");
   cmdsave->AddFormat("pdf",1);
   cf->Register(cmdsave);
   art::TCmdPrint *pri = new art::TCmdPrint;
   pri->SetOption("-Prcc2570a -o fit-to-page");
   cf->Register(pri);

   {
//      TString path = gSystem->GetIncludePath();
//      path.Append("-I./processors");
//      gSystem->SetIncludePath(path);
   }
   {

//      art::TModuleDecoderFactory *df = art::TModuleDecoderFactory::Instance();

//      gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoderV1190_rcnp)");
//      gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoder3377)");
//      gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoderTS)");
//      gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoderFERA)");
//      gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoderFERET)");
//      gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoderMXDC32_rcnp)");

//      
//      art::TModuleDecoderFactory *df = art::TModuleDecoderFactory::Instance();
//      // mod ID 0 : Fixed16
//      const Int_t digits0 = 16;
//      df->Register(new art::TModuleDecoderFixed<unsigned short>(0,digits0) );
//      // mod ID 1 : Fixed24
//      const Int_t digits1 = 24;
//      df->Register(new art::TModuleDecoderFixed<unsigned int>(1,digits1) );
//      // mod ID 21 : V7XX
//      df->Register(new art::TModuleDecoderV7XX);
//      // mod ID 23 : V767
//      df->Register(new art::TModuleDecoderV767);
//
//      // mod ID 24 : V1190
//      // mod ID 25 : V1290
//      // mod ID 26 : V1190C
//      art::TModuleDecoder *v1190 = new art::TModuleDecoderV1190;
//      art::TModuleDecoder *v1290 = new art::TModuleDecoderV1290(25);
//      art::TModuleDecoder *v1190c = new art::TModuleDecoderV1190(26);
//      v1190->SetVerboseLevel(kError);
//      v1290->SetVerboseLevel(kError);
//      v1190c->SetVerboseLevel(kError);
//      df->Register(v1190);
//      df->Register(v1290);
//      df->Register(v1190c);
//
//      // mod ID 36 : SIS3820
//      df->Register(new art::TModuleDecoderSIS3820);
//      df->Register(new art::TModuleDecoderSIS3610);
//
//      df->Register(new art::TModuleDecoderSkip(42));
//      df->Register(new art::TModuleDecoderSkip(8));
//
      // original decoder 
      //gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoder{MoudleName});");

   }
}
