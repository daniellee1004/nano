#include "nano/analysis/interface/h2muAnalyser.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <cstdlib>

using namespace std;
/*
To compile:
g++ `root-config --cflags --glibs` -lEG h2muAnalyser.cc -o h2muAnalyser
*/

void h2muAnalyser::SetOutput(string outputName)
{
  m_output = TFile::Open(outputName.c_str(), "recreate");
  // TMVA Booking //
  
  weightXL = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/all/XL/weights/TMVAClassification_BDTG.weights.xml";
  weightFH = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/all/nFH/weights/TMVAClassification_BDTG.weights.xml";
  weightOut = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/all/Out/weights/TMVAClassification_BDTG.weights.xml";
  weightnoB = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/all/nonB/weights/TMVAClassification_BDTG.weights.xml";

  bdt_XL = new TMVA::Reader();
  bdt_XL->AddVariable( "Met", &b_Met );
  bdt_XL->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_XL->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_XL->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_XL->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_XL->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_XL->AddVariable( "nelec", &b_nelec );
  bdt_XL->AddVariable( "nmuon", &b_nmuon );
  bdt_XL->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_XL->AddVariable( "nbjet", &b_nbjet );
  bdt_XL->AddVariable( "minDR", &b_minDR );
  bdt_XL->AddVariable( "XlepPt", &b_XlepPt );
  bdt_XL->AddVariable( "mT", &b_mT );
  bdt_XL->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  bdt_XL->BookMVA("BDTG", weightXL); 
  
  bdt_FH = new TMVA::Reader();
  bdt_FH->AddVariable( "Met", &b_Met );
  bdt_FH->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_FH->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_FH->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_FH->AddVariable( "Dilep.Pt()", &b_DilepPt );
  //bdt_FH->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_FH->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_FH->AddVariable( "nbjet", &b_nbjet );
  bdt_FH->AddVariable( "minDR1", &b_minDR1 );
  bdt_FH->AddVariable( "minDR2", &b_minDR2 );
  bdt_FH->AddVariable( "mT", &b_mT );
 // bdt_FH->AddVariable( "DiJetM1.M()", &b_DiJetM12 );
 // bdt_FH->AddVariable( "DiJetM2.M()", &b_DiJetM13 );
 // bdt_FH->AddVariable( "DiJetM3.M()", &b_DiJetM14 );
 // bdt_FH->AddVariable( "DiJetM4.M()", &b_DiJetM23 );
 // bdt_FH->AddVariable( "DiJetM5.M()", &b_DiJetM24 );
 // bdt_FH->AddVariable( "DiJetM6.M()", &b_DiJetM34 );
  bdt_FH->BookMVA("BDTG", weightFH); 
  
  bdt_Out = new TMVA::Reader();
  bdt_Out->AddVariable( "Met", &b_Met );
  bdt_Out->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_Out->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_Out->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_Out->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_Out->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_Out->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_Out->AddVariable( "nbjet", &b_nbjet );
  bdt_Out->AddVariable( "mT", &b_mT );
  bdt_Out->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  bdt_Out->AddVariable( "DiJetM1.Pt()", &b_DiJetM1Pt );
  bdt_Out->AddVariable( "DiJetM1.Eta()", &b_DiJetM1Eta );
  bdt_Out->BookMVA("BDTG", weightOut);

  bdt_noB = new TMVA::Reader();
  bdt_noB->AddVariable( "Met", &b_Met );
  bdt_noB->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_noB->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_noB->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_noB->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_noB->AddVariable( "Dilep.Eta()", &b_DilepEta );
  //bdt_noB->AddVariable( "nelec", &b_nelec );
  bdt_noB->AddVariable( "nexLep", &b_nexLep );
  //bdt_noB->AddVariable( "nmuon", &b_nmuon );
  //bdt_noB->AddVariable( "njet", &b_njet );
  bdt_noB->AddVariable( "etaJ1", &b_etaJ1 );
  bdt_noB->AddVariable( "etaJ2", &b_etaJ2 );
  bdt_noB->AddVariable( "DijetM1", &b_DijetM1 );
  bdt_noB->AddVariable( "DijetM2", &b_DijetM2 );
  bdt_noB->AddVariable( "DijetEta1", &b_DijetEta1 );
  bdt_noB->AddVariable( "DijetEta2", &b_DijetEta2 );
  bdt_noB->BookMVA("BDTG", weightnoB);
  

  TTJXL = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/TTBar/XL/weights/TMVAClassification_BDTG.weights.xml";
  TTZXL = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/TTZ/XL/weights/TMVAClassification_BDTG.weights.xml";

  TTJFH = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/TTBar/nFH/weights/TMVAClassification_BDTG.weights.xml";
  //TTZFH = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/all/nFH_No/weights/TMVAClassification_BDTG.weights.xml";

  DYOut = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/DYJets/Out/weights/TMVAClassification_BDTG.weights.xml";
  TTJOut = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/TTBar/Out/weights/TMVAClassification_BDTG.weights.xml";
  //TTZOut = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/all/Seperate/weights/TMVAClassification_BDTG.weights.xml";

  DYnoB = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/DYJets/nonB/weights/TMVAClassification_BDTG.weights.xml";
  TTJnoB = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate/TTBar/nonB/weights/TMVAClassification_BDTG.weights.xml";
  //TTZnoB = std::string(std::getenv("CMSSW_BASE"))+"/src/nano/analysis/test/h2mu/TMVA/Seperate//nonB/weights/TMVAClassification_BDTG.weights.xml";

  bdt_TTJXL = new TMVA::Reader();
  bdt_TTJXL->AddVariable( "Met", &b_Met );
  bdt_TTJXL->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTJXL->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTJXL->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTJXL->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTJXL->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTJXL->AddVariable( "nelec", &b_nelec );
  bdt_TTJXL->AddVariable( "nmuon", &b_nmuon );
  bdt_TTJXL->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_TTJXL->AddVariable( "nbjet", &b_nbjet );
  //bdt_TTJXL->AddVariable( "njet", &b_nbjet );
  bdt_TTJXL->AddVariable( "minDR", &b_minDR );
  bdt_TTJXL->AddVariable( "XlepPt", &b_XlepPt );
  bdt_TTJXL->AddVariable( "mT", &b_mT );
  bdt_TTJXL->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  bdt_TTJXL->BookMVA("BDTG", TTJXL); 
  
  bdt_TTZXL = new TMVA::Reader();
  //bdt_TTZXL->AddVariable( "Met", &b_Met );
  bdt_TTZXL->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  //bdt_TTZXL->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTZXL->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTZXL->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTZXL->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTZXL->AddVariable( "nelec", &b_nelec );
  bdt_TTZXL->AddVariable( "nmuon", &b_nmuon );
  //bdt_TTZXL->AddVariable( "nnonbjet", &b_nnonbjet );
  //bdt_TTZXL->AddVariable( "nbjet", &b_nbjet );
  bdt_TTZXL->AddVariable( "minDR", &b_minDR );
  bdt_TTZXL->AddVariable( "XlepPt", &b_XlepPt );
  bdt_TTZXL->AddVariable( "mT", &b_mT );
  //bdt_TTZXL->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  bdt_TTZXL->BookMVA("BDTG", TTZXL); 
  
  bdt_TTJFH = new TMVA::Reader();
  bdt_TTJFH->AddVariable( "Met", &b_Met );
  bdt_TTJFH->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTJFH->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTJFH->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTJFH->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTJFH->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTJFH->AddVariable( "nnonbjet", &b_nnonbjet );
  //bdt_TTJFH->AddVariable( "nbjet", &b_nbjet );
  bdt_TTJFH->AddVariable( "minDR1", &b_minDR1 );
  bdt_TTJFH->AddVariable( "minDR2", &b_minDR2 );
  bdt_TTJFH->AddVariable( "mT", &b_mT );
  bdt_TTJFH->AddVariable( "DiJetM1.M()", &b_DiJetM12 );
  bdt_TTJFH->AddVariable( "DiJetM2.M()", &b_DiJetM13 );
  bdt_TTJFH->AddVariable( "DiJetM3.M()", &b_DiJetM14 );
  bdt_TTJFH->AddVariable( "DiJetM4.M()", &b_DiJetM23 );
  bdt_TTJFH->AddVariable( "DiJetM5.M()", &b_DiJetM24 );
  bdt_TTJFH->AddVariable( "DiJetM6.M()", &b_DiJetM34 );
  bdt_TTJFH->BookMVA("BDTG", TTJFH); 
 /* 
  bdt_TTZFH = new TMVA::Reader();
  bdt_TTZFH->AddVariable( "Met", &b_Met );
  bdt_TTZFH->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTZFH->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTZFH->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTZFH->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTZFH->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTZFH->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_TTZFH->AddVariable( "nbjet", &b_nbjet );
  bdt_TTZFH->AddVariable( "minDR1", &b_minDR1 );
  bdt_TTZFH->AddVariable( "minDR2", &b_minDR2 );
  bdt_TTZFH->AddVariable( "mT", &b_mT );
  bdt_TTZFH->AddVariable( "DiJetM1.M()", &b_DiJetM12 );
  bdt_TTZFH->AddVariable( "DiJetM2.M()", &b_DiJetM13 );
  bdt_TTZFH->AddVariable( "DiJetM3.M()", &b_DiJetM14 );
  bdt_TTZFH->AddVariable( "DiJetM4.M()", &b_DiJetM23 );
  bdt_TTZFH->AddVariable( "DiJetM5.M()", &b_DiJetM24 );
  bdt_TTZFH->AddVariable( "DiJetM6.M()", &b_DiJetM34 );
  bdt_TTZFH->BookMVA("BDT", TTZFH); 
 */
  bdt_DYOut = new TMVA::Reader();
  bdt_DYOut->AddVariable( "Met", &b_Met );
  bdt_DYOut->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_DYOut->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_DYOut->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_DYOut->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_DYOut->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_DYOut->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_DYOut->AddVariable( "nbjet", &b_nbjet );
  bdt_DYOut->AddVariable( "mT", &b_mT );
  bdt_DYOut->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  bdt_DYOut->AddVariable( "DiJetM1.Pt()", &b_DiJetM1Pt );
  bdt_DYOut->AddVariable( "DiJetM1.Eta()", &b_DiJetM1Eta );
  bdt_DYOut->BookMVA("BDTG", DYOut);

  bdt_TTJOut = new TMVA::Reader();
  bdt_TTJOut->AddVariable( "Met", &b_Met );
  bdt_TTJOut->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTJOut->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTJOut->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTJOut->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTJOut->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTJOut->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_TTJOut->AddVariable( "nbjet", &b_nbjet );
  bdt_TTJOut->AddVariable( "mT", &b_mT );
  //bdt_TTJOut->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  //bdt_TTJOut->AddVariable( "DiJetM1.Pt()", &b_DiJetM1Pt );
  bdt_TTJOut->BookMVA("BDTG", TTJOut);
/*
  bdt_TTZOut = new TMVA::Reader();
  bdt_TTZOut->AddVariable( "Met", &b_Met );
  bdt_TTZOut->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTZOut->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTZOut->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTZOut->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTZOut->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTZOut->AddVariable( "nnonbjet", &b_nnonbjet );
  bdt_TTZOut->AddVariable( "nbjet", &b_nbjet );
  bdt_TTZOut->AddVariable( "mT", &b_mT );
  bdt_TTZOut->AddVariable( "DiJetM1.M()", &b_DiJetM1M );
  bdt_TTZOut->AddVariable( "DiJetM1.Eta()", &b_DiJetM1Eta );
  bdt_TTZOut->AddVariable( "DiJetM1.Pt()", &b_DiJetM1Pt );
  bdt_TTZOut->BookMVA("BDT", TTZOut);
*/
  bdt_DYnoB = new TMVA::Reader();
  bdt_DYnoB->AddVariable( "Met", &b_Met );
  bdt_DYnoB->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_DYnoB->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_DYnoB->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_DYnoB->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_DYnoB->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_DYnoB->AddVariable( "nelec", &b_nelec );
  bdt_DYnoB->AddVariable( "nexLep", &b_nexLep );
  bdt_DYnoB->AddVariable( "nmuon", &b_nmuon );
  bdt_DYnoB->AddVariable( "njet", &b_njet );
  bdt_DYnoB->AddVariable( "etaJ1", &b_etaJ1 );
  bdt_DYnoB->AddVariable( "etaJ2", &b_etaJ2 );
  bdt_DYnoB->AddVariable( "DijetM1", &b_DijetM1 );
  bdt_DYnoB->AddVariable( "DijetM2", &b_DijetM2 );
  bdt_DYnoB->AddVariable( "DijetEta1", &b_DijetEta1 );
  bdt_DYnoB->AddVariable( "DijetEta2", &b_DijetEta2 );
  bdt_DYnoB->BookMVA("BDTG", DYnoB);

  bdt_TTJnoB = new TMVA::Reader();
  bdt_TTJnoB->AddVariable( "Met", &b_Met );
  bdt_TTJnoB->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTJnoB->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTJnoB->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTJnoB->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTJnoB->AddVariable( "Dilep.Eta()", &b_DilepEta );
  //bdt_TTJnoB->AddVariable( "nelec", &b_nelec );
  //bdt_TTJnoB->AddVariable( "nexLep", &b_nexLep );
  //bdt_TTJnoB->AddVariable( "nmuon", &b_nmuon );
  bdt_TTJnoB->AddVariable( "njet", &b_njet );
  bdt_TTJnoB->AddVariable( "etaJ1", &b_etaJ1 );
  bdt_TTJnoB->AddVariable( "etaJ2", &b_etaJ2 );
  bdt_TTJnoB->AddVariable( "DijetM1", &b_DijetM1 );
  bdt_TTJnoB->AddVariable( "DijetM2", &b_DijetM2 );
  bdt_TTJnoB->AddVariable( "DijetEta1", &b_DijetEta1 );
  bdt_TTJnoB->AddVariable( "DijetEta2", &b_DijetEta2 );
  bdt_TTJnoB->BookMVA("BDTG", TTJnoB);
/*
  bdt_TTZnoB = new TMVA::Reader();
  bdt_TTZnoB->AddVariable( "Met", &b_Met );
  bdt_TTZnoB->AddVariable( "all_muEtaDiff", &b_all_muEtaDiff );
  bdt_TTZnoB->AddVariable( "all_muPtDiff", &b_all_muPhiDiff );
  bdt_TTZnoB->AddVariable( "all_muPhiDiff", &b_all_muPhiDiff );
  bdt_TTZnoB->AddVariable( "Dilep.Pt()", &b_DilepPt );
  bdt_TTZnoB->AddVariable( "Dilep.Eta()", &b_DilepEta );
  bdt_TTZnoB->AddVariable( "nelec", &b_nelec );
  bdt_TTZnoB->AddVariable( "nexLep", &b_nexLep );
  bdt_TTZnoB->AddVariable( "nmuon", &b_nmuon );
  bdt_TTZnoB->AddVariable( "njet", &b_njet );
  bdt_TTZnoB->AddVariable( "etaJ1", &b_etaJ1 );
  bdt_TTZnoB->AddVariable( "etaJ2", &b_etaJ2 );
  bdt_TTZnoB->AddVariable( "DijetM1", &b_DijetM1 );
  bdt_TTZnoB->AddVariable( "DijetM2", &b_DijetM2 );
  bdt_TTZnoB->AddVariable( "DijetEta1", &b_DijetEta1 );
  bdt_TTZnoB->AddVariable( "DijetEta2", &b_DijetEta2 );
  bdt_TTZnoB->BookMVA("BDT", TTZnoB);
*/
  m_tree = new TTree("events", "events");
  MakeBranch(m_tree);
  
  h_Event_Tot = new TH1D("Event_total", "Event_total" ,1,0,1);
  h_genweights = new TH1D("genweight", "genweight" , 1,0,1);
  h_weight = new TH1D("weight", "weight", 1,0,1);
  h_Posweight = new TH1D("Posweight", "Posweight", 1,0,1);
  h_cutFlow = new TH1D("cutflow", "cutflow", 11, -0.5, 10.5);
  h_XL = new TH1D("ExtraLep", "ExtraLep", 1, 0, 1);
  h_nFH4 = new TH1D("FullyHad4", "FullyHad4", 1, 0, 1);
  h_Out = new TH1D("Out", "Out", 1, 0, 1);
  h_Non = new TH1D("Non", "Non", 1, 0, 1);
}

void h2muAnalyser::MakeBranch(TTree* t)
{
  t->Branch("Event_No", &b_Event_No, "Event_No/I");
  t->Branch("Step", &b_Step, "Step/I");
  t->Branch("Dilep", "TLorentzVector", &b_Dilep);
  t->Branch("Mu1", "TLorentzVector", &b_Mu1);
  
  t->Branch("Mu2", "TLorentzVector", &b_Mu2);
  t->Branch("lep", "TLorentzVector", &b_lep);
  t->Bronch("bjet", "std::vector<TLorentzVector>", &b_bJet);
  
  t->Bronch("Jet", "std::vector<TLorentzVector>", &b_Jet);
  t->Bronch("nonbJet", "std::vector<TLorentzVector>", &b_nonbJet);
  
  t->Branch("DiJetM1", &b_DiJetM1);
  t->Branch("DiJetM2", &b_DiJetM2);
  t->Branch("DiJetM3", &b_DiJetM3);
  t->Branch("DiJetM4", &b_DiJetM4);
  t->Branch("DiJetM5", &b_DiJetM5);
  t->Branch("DiJetM6", &b_DiJetM6);

  t->Branch("Jet_eta1", &b_Jet_eta1, "Jet_eta1/F");
  t->Branch("Jet_eta2", &b_Jet_eta2, "Jet_eta2/F");
  t->Branch("Jet_eta3", &b_Jet_eta3, "Jet_eta3/F");
  t->Branch("Jet_eta4", &b_Jet_eta4, "Jet_eta4/F");
  
  t->Branch("genweight", &b_genweight, "genweight/F");
  t->Branch("puweight", &b_puweight, "puweight/F");
  
  t->Branch("puweight_up", &b_puweight_up, "puweight_up/F");
  t->Branch("puweight_dn", &b_puweight_dn, "puweight_dn/F");
  t->Branch("weight", &b_weight, "weight/F");
  t->Branch("npvs", &b_npvs, "npvs/F");
  
  t->Branch("channel", &b_channel, "channel/I");
  t->Branch("charge", &b_charge, "charge/I");
  t->Branch("nlep", &b_nlep, "nlep/F");
  t->Branch("nmuon", &b_nmuon, "nmuon/F");
  
  t->Branch("nelec", &b_nelec, "nelec/F");
  t->Branch("njet", &b_njet, "njet/F");
  t->Branch("nnonbjet", &b_nnonbjet, "nnonbjet/F");
  t->Branch("nbjet", &b_nbjet, "nbjet/F");
  
  t->Branch("trig_m", &b_trig_m, "trig_m/O");
  t->Branch("Met_ori", &b_Met_ori, "Met_ori/F");
  t->Branch("Met", &b_Met, "Met/F");
  t->Branch("Met_phi", &b_Met_phi, "Met_phi/F");
  t->Branch("CSVv2", &b_CSVv2);
  
  t->Branch("nFH4", &b_nFH4, "nFH4/I");
  t->Branch("XL", &b_XL, "XL/I");
  t->Branch("Out", &b_Out, "Out/I");
  t->Branch("nonB", &b_nonB, "nonB/I");
  
  t->Branch("csvweight", "std::vector<float>", &b_csvweights);
  t->Branch("btagweight", &b_btagweight, "btagweight/F");
  t->Branch("btagweightB", &b_btagweightB, "btagweightB/F");
  
  t->Branch("jes_up", &b_jes_up, "jes_up/F");
  t->Branch("jes_dn", &b_jes_dn, "jes_dn/F");
  t->Branch("cferr1_up", &b_cferr1_up, "cferr1_up/F");
  t->Branch("cferr1_dn", &b_cferr1_dn, "cferr1_dn/F");
  
  t->Branch("cferr2_up", &b_cferr2_up, "cferr2_up/F");
  t->Branch("cferr2_dn", &b_cferr2_dn, "cferr2_dn/F");
  t->Branch("hf_up", &b_hf_up, "hf_up/F");
  t->Branch("hf_dn", &b_hf_dn, "hf_dn/F");
  
  t->Branch("hfstats1_up", &b_hfstats1_up, "hfstats1_up/F");
  t->Branch("hfstats1_dn", &b_hfstats1_dn, "hfstats1_dn/F");
  t->Branch("hfstats2_up", &b_hfstats2_up, "hfstats2_up/F");
  t->Branch("hfstats2_dn", &b_hfstats2_dn, "hfstats2_dn/F");
  
  t->Branch("lf_up", &b_lf_up, "lf_up/F");
  t->Branch("lf_dn", &b_lf_dn, "lf_dn/F");
  t->Branch("lfstats1_up", &b_lfstats1_up, "lfstats1_up/F");
  t->Branch("lfstats1_dn", &b_lfstats1_dn, "lfstats1_dn/F");
  
  t->Branch("lfstats2_up", &b_lfstats2_up, "lfstats2_up/F");
  t->Branch("lfstats2_dn", &b_lfstats2_dn, "lfstats2_dn/F");
  t->Branch("mueffweight", &b_mueffweight, "mueffweight/F");
  t->Branch("mueffweight_up", &b_mueffweight_up, "mueffweight_up/F");
  t->Branch("mueffweight_dn", &b_mueffweight_dn, "mueffweight_dn/F");
 
  ////////////////////BDT////////////////////////////
  t->Branch("all_muEtaDiff", &b_all_muEtaDiff, "all_muEtaDiff/F");
  t->Branch("all_muPtDiff", &b_all_muPtDiff, "all_muPtDiff/F");
  t->Branch("all_muPhiDiff", &b_all_muPhiDiff, "all_muPhiDiff/F");
  
  t->Branch("DijetM1", &b_DijetM1, "DijetM1/F");
  t->Branch("DijetM2", &b_DijetM2, "DijetM2/F");
  t->Branch("DijetEta1",&b_DijetEta1, "DijetEta1/F");
  t->Branch("DijetEta2",&b_DijetEta2, "DijetEta2/F");
  
  t->Branch("minDR1", &b_minDR1, "minDR1/F");
  t->Branch("minDR2", &b_minDR2, "minDR2/F");
  
  t->Branch("minDR", &b_minDR, "minDR/F");
  t->Branch("XlepPt", &b_XlepPt, "XlepPt/F");
  t->Branch("mT", &b_mT, "mT/F");
  t->Branch("mT2", &b_mT2, "mT2/F");
  
  t->Branch("nexLep", &b_nexLep, "nexLep/F");
  t->Branch("etaJ1", &b_etaJ1, "etaJ1/F");
  t->Branch("etaJ2", &b_etaJ2, "etaJ2/F");
  t->Branch("JetEtaDiff", &b_JetEtaDiff, "b_JetEtaDiff/F");

  t->Branch("MVA_BDTXL", &b_MVA_BDTXL, "MVA_BDTXL/F");
  t->Branch("MVA_TTJXL", &b_MVA_TTJXL, "MVA_TTJXL/F");
  t->Branch("MVA_TTZXL", &b_MVA_TTZXL, "MVA_TTZXL/F");

  t->Branch("MVA_BDTFH", &b_MVA_BDTFH, "MVA_BDTFH/F");
  t->Branch("MVA_TTJFH", &b_MVA_TTJFH, "MVA_TTJFH/F");
  //t->Branch("MVA_TTZFH", &b_MVA_TTZFH, "MVA_TTZFH/F");

  t->Branch("MVA_BDTnoB", &b_MVA_BDTnoB, "MVA_BDTnoB/F");
  t->Branch("MVA_DYnoB", &b_MVA_DYnoB, "MVA_DYnoB/F");
  t->Branch("MVA_TTJnoB", &b_MVA_TTJnoB, "MVA_TTJnoB/F");
  //t->Branch("MVA_TTZnoB", &b_MVA_TTZnoB, "MVA_TTZnoB/F");

  t->Branch("MVA_BDTOut", &b_MVA_BDTOut, "MVA_BDTOut/F");
  t->Branch("MVA_DYOut", &b_MVA_DYOut, "MVA_DYOut/F");
  t->Branch("MVA_TTJOut", &b_MVA_TTJOut, "MVA_TTJOut/F");
  //t->Branch("MVA_TTZOut", &b_MVA_TTZOut, "MVA_TTZOut/F");
  t->Branch("sigCount", &b_sigCount, "sigCount/I");
  t->Branch("CSV", &b_CSV, "CSV/F");

  t->Branch("Top1", &b_top1);
  t->Branch("Top2", &b_top2);
  t->Branch("Top3", &b_top3);
  t->Branch("Top4", &b_top4);
  t->Branch("Top5", &b_top5);
  t->Branch("Top6", &b_top6);

  t->Branch("Top7", &b_top7);
  t->Branch("Top8", &b_top8);
  t->Branch("Top9", &b_top9);
  t->Branch("Top10", &b_top10);
  t->Branch("Top11", &b_top11);
  t->Branch("Top12", &b_top12);
  
  t->Branch("m2_Top1", &m2_top1);
  t->Branch("m2_Top2", &m2_top2);
  t->Branch("m2_Top3", &m2_top3);
  t->Branch("m2_Top4", &m2_top4);
  t->Branch("m2_Top5", &m2_top5);
  t->Branch("m2_Top6", &m2_top6);

  t->Branch("m2_Top7", &m2_top7);
  t->Branch("m2_Top8", &m2_top8);
  t->Branch("m2_Top9", &m2_top9);
  t->Branch("m2_Top10", &m2_top10);
  t->Branch("m2_Top11", &m2_top11);
  t->Branch("m2_Top12", &m2_top12);

  t->Branch("best_m2_top1", &m2_b_top1);
  t->Branch("best_m2_top2", &m2_b_top2);
  t->Branch("TopDR", &b_topDR);
  t->Branch("bjetDR", &b_bjetDR);
  t->Branch("best_Top1", &b_b_top1);
  t->Branch("best_Top2", &b_b_top2);
}
void h2muAnalyser::ResetBranch()
{ 
  b_Step = 0;
  b_Dilep.SetPtEtaPhiM(0,0,0,0);
  b_Mu1.SetPtEtaPhiM(0,0,0,0);
  b_Mu2.SetPtEtaPhiM(0,0,0,0);
  b_lep.SetPtEtaPhiM(0,0,0,0);
  b_nonbJet1.SetPtEtaPhiM(0,0,0,0);
  b_nonbJet2.SetPtEtaPhiM(0,0,0,0);
  b_nonbJet3.SetPtEtaPhiM(0,0,0,0);
  b_nonbJet4.SetPtEtaPhiM(0,0,0,0);

  //Top Reco method 1
  m_Jet1.SetPtEtaPhiM(0,0,0,0); m_Jet2.SetPtEtaPhiM(0,0,0,0); m_Jet3.SetPtEtaPhiM(0,0,0,0); m_Jet4.SetPtEtaPhiM(0,0,0,0);

  b_DiJetM1.SetPtEtaPhiM(0,0,0,0); b_DiJetM2.SetPtEtaPhiM(0,0,0,0); b_DiJetM3.SetPtEtaPhiM(0,0,0,0); 
  b_DiJetM4.SetPtEtaPhiM(0,0,0,0); b_DiJetM5.SetPtEtaPhiM(0,0,0,0); b_DiJetM6.SetPtEtaPhiM(0,0,0,0);

  b_top1.SetPtEtaPhiM(0,0,0,0); b_top2.SetPtEtaPhiM(0,0,0,0); b_top3.SetPtEtaPhiM(0,0,0,0); b_top4.SetPtEtaPhiM(0,0,0,0);
  b_top5.SetPtEtaPhiM(0,0,0,0); b_top6.SetPtEtaPhiM(0,0,0,0); b_top7.SetPtEtaPhiM(0,0,0,0); b_top8.SetPtEtaPhiM(0,0,0,0);
  b_top9.SetPtEtaPhiM(0,0,0,0); b_top10.SetPtEtaPhiM(0,0,0,0); b_top11.SetPtEtaPhiM(0,0,0,0); b_top12.SetPtEtaPhiM(0,0,0,0);
  
  //Top Reco method 2  
  m2_Jet1.SetPtEtaPhiM(0,0,0,0); m2_Jet2.SetPtEtaPhiM(0,0,0,0); m2_Jet3.SetPtEtaPhiM(0,0,0,0); 
  m2_Jet4.SetPtEtaPhiM(0,0,0,0); m2_Jet5.SetPtEtaPhiM(0,0,0,0); m2_Jet6.SetPtEtaPhiM(0,0,0,0);
 
  m2_DiJetM1.SetPtEtaPhiM(0,0,0,0); m2_DiJetM2.SetPtEtaPhiM(0,0,0,0); m2_DiJetM3.SetPtEtaPhiM(0,0,0,0); 
  m2_DiJetM4.SetPtEtaPhiM(0,0,0,0); m2_DiJetM5.SetPtEtaPhiM(0,0,0,0); m2_DiJetM6.SetPtEtaPhiM(0,0,0,0);
  
  m2_top1.SetPtEtaPhiM(0,0,0,0); m2_top2.SetPtEtaPhiM(0,0,0,0); m2_top3.SetPtEtaPhiM(0,0,0,0); m2_top4.SetPtEtaPhiM(0,0,0,0);
  m2_top5.SetPtEtaPhiM(0,0,0,0); m2_top6.SetPtEtaPhiM(0,0,0,0); m2_top7.SetPtEtaPhiM(0,0,0,0); m2_top8.SetPtEtaPhiM(0,0,0,0);
  m2_top9.SetPtEtaPhiM(0,0,0,0); m2_top10.SetPtEtaPhiM(0,0,0,0); m2_top11.SetPtEtaPhiM(0,0,0,0); m2_top12.SetPtEtaPhiM(0,0,0,0);
  hold_Csv1 = 0; hold_Csv2 = 0;
  hold_pT3 = 0; hold_pT4 = 0; hold_pT5 = 0; hold_pT6 = 0;
  //Top Reco Method 3
  m2_b_top1.SetPtEtaPhiM(0,0,0,0); m2_b_top2.SetPtEtaPhiM(0,0,0,0); b_b_top1.SetPtEtaPhiM(0,0,0,0), b_b_top2.SetPtEtaPhiM(0,0,0,0);
  m_topM_hold1 = 0; m_topM_hold2 = 0; 
  TopVector_hold.clear();
  b_topDR = 0;
  b_bjetDR = 0;
  b_JetEtaDiff = 0;

  b_DiJetM1M = 0.; b_DiJetM1Pt = 0.; b_DiJetM1Eta = 0. ;b_DilepPt = 0.; b_DilepEta = 0.;
  b_Mu_tlv.clear(); b_El_tlv.clear(); b_Jet_tlv.clear(); b_bJet_tlv.clear(); 
  b_bJet->clear(); b_Jet->clear(); b_nonbJet->clear(); 
  b_nonbJet_tlv.clear(); b_Jet_pu.clear();
  b_csvweights.clear(); b_CSVv2.clear();
  b_Event_Total = 1; b_channel = -1;
  b_nlep = 0; b_nmuon = 0; b_nelec = 0; b_nnonbjet = 0; b_njet = 0; b_nbjet = 0;
  b_XL = 0; b_nFH4 = 0; b_Out = 0; b_nonB = 0; 
  b_Jet_eta1 = -6.; b_Jet_eta2 = -6.; b_Jet_eta3 = -6.; b_Jet_eta4 = -6.;
  
  // BtagWeight //
  b_btagweightB = 1.;
  b_btagweight = 1.; b_jes_up = 1.; b_jes_dn = 1.; b_lf_up = 1.; b_lf_dn = 1.;
  b_hfstats1_up = 1.; b_hfstats1_dn = 1.; b_hfstats2_up = 1.; b_hfstats2_dn = 1.;
  b_lfstats1_up = 1.; b_lfstats1_dn = 1.; b_lfstats2_up = 1.; b_lfstats2_dn = 1.; 
  b_hf_up = 1.; b_hf_dn = 1.; b_cferr1_up = 1.; b_cferr1_dn = 1.; b_cferr2_up = 1.; b_cferr2_dn = 1.;
  b_Met_ori = 0.; b_Met = 0. ; b_Met_phi = 0.;

  // BDT //
  b_all_muEtaDiff = 0; b_all_muPtDiff = 0; b_all_muPhiDiff = 0; b_all_muDR = 0;
  b_Central_Jets = 0; b_Forward_Jets = 0;
  b_DiJetM12 = 0; b_DiJetM13 = 0; b_DiJetM14 = 0; b_DiJetM23 = 0; b_DiJetM24 = 0; b_DiJetM34 = 0;
  b_minDR1 = -2; b_minDR2 = -2;
  b_minDR = -2; b_XlepPt = 0; b_mT2 = -2; b_mT = -2; b_nexLep = 0; b_etaJ1 = -6; b_etaJ2 = -6;
  b_MVA_BDTXL = -999; b_MVA_BDTFH = -999; b_MVA_BDTnoB = -999; b_MVA_BDTOut = -999;
  b_MVA_TTJXL = -999; b_MVA_TTZXL = -999; b_MVA_TTJFH = -999; b_MVA_DYOut = -999; b_MVA_TTJOut = -999; b_MVA_DYnoB = -999; b_MVA_TTJnoB = -999;
  DR_Hold = 0, DR_Hold2 = 0 ,mT_Hold = 0, MuPT_Hold = 0, ElPT_Hold = 0;
  b_DijetEta1 = -10, b_DijetEta2 = -10, DijetEta_hold = 0, DijetM_hold = 0, b_DijetM1 = -10, b_DijetM2 = -10;
  b_CSV = 0;
  b_npvs = 0;
  b_sigCount = 0;
}

bool h2muAnalyser::Analysis()
{
  h_Event_Tot->Fill(0.5, b_Event_Total);
  h_cutFlow->Fill(0);
  b_Step = 0;
  //Run for MC
  if(m_isMC){
    Int_t nvtx = Pileup_nTrueInt;
    b_puweight = m_pileUp->getWeight(nvtx);
    b_puweight_up = m_pileUp->getWeight(nvtx, 1);
    b_puweight_dn = m_pileUp->getWeight(nvtx, -1);
    b_genweight = genWeight;
    h_genweights->Fill(0.5, b_genweight);
    b_weight = b_genweight * b_puweight;
    h_weight->Fill(0.5, b_weight);
    h_Posweight->Fill(0.5, 1);
  } else {
    b_puweight = 1;
    b_genweight = 0;
    if (!(m_lumi->LumiCheck(run, luminosityBlock))) return false;
  }
  b_Step = 1;
  h_cutFlow->Fill(1);

  if (fabs(PV_z) >= 24.) return false;
  if (PV_npvs == 0) return false;
  if (PV_ndof < 4) return false;
  b_Step = 2;
  h_cutFlow->Fill(2);
  
  b_trig_m = HLT_IsoTkMu24 || HLT_IsoMu24;
  Bool_t IsoMu24 = false;
 // Bool_t IsoTkMu24 = false;

  for (UInt_t i = 0; i < nTrigObj; ++i) {
    if (TrigObj_id[i] != 13) continue; 
    if (TrigObj_pt[i] < 24) continue;
    Int_t bits = TrigObj_filterBits[i];
    if (bits & 0x2) IsoMu24 = true;
   // if (bits & 0x8) IsoTkMu24 = true;  
  }
  //if (!(IsoMu24 || IsoTkMu24)) return true; 
  if (!IsoMu24) return true; 
  
  b_Step = 3;
  h_cutFlow->Fill(3);

  auto Muons = MuonSelection();
  auto Elecs = ElectronSelection(Muons);
 
  if (Muons.size() < 2) return true;
  
  TParticle mu1;
  TParticle mu2; 
  b_Met_ori = MET_pt;
  b_Met = PuppiMET_pt;
  b_Met_phi = PuppiMET_phi;
  b_Step = 4;
  h_cutFlow->Fill(4);
  
  for (UInt_t i = 1; i < Muons.size(); i++) { 
    if ((b_Mu_tlv[0].Pt() > 26) || (b_Mu_tlv[i].Pt() > 26)) { 
      if ((Muons[0].GetPdgCode() * Muons[i].GetPdgCode()) < 0 ) { 
        b_Mu1 = b_Mu_tlv[0];
        b_Mu2 = b_Mu_tlv[i];

        b_charge = 1;
        mu1 = Muons[0];
        mu2 = Muons[i]; 
        b_Mu_tlv.erase(b_Mu_tlv.begin()+(i-1));
        b_Mu_tlv.erase(b_Mu_tlv.begin());

        break;
      }
    }
  }
  if (b_charge == 0) return true; 

  b_nlep = Muons.size() + Elecs.size();
  b_nmuon = Muons.size();
  b_nelec = Elecs.size();
  b_Step = 5;
  h_cutFlow->Fill(5);

  auto Jets = JetSelection(Muons, Elecs);
  auto BJets = BJetSelection(Muons, Elecs);
  auto nonbJets = nonbJetSelection(Muons, Elecs);

  b_njet = Jets.size();
  b_nnonbjet = nonbJets.size();
  b_nbjet = BJets.size();
  b_npvs = PV_npvs;
  for (UInt_t i = 0; i < Jets.size(); i++) {
     if (i == 0) {
        b_Jet_eta1 = b_Jet_tlv[i].Eta();
        }
     if (i == 1) {
        b_Jet_eta2 = b_Jet_tlv[i].Eta();
        }
     if (i == 2) {
        b_Jet_eta3 = b_Jet_tlv[i].Eta();
        }
     if (i == 3) {
        b_Jet_eta4 = b_Jet_tlv[i].Eta();
        }
  }

  b_Dilep = b_Mu1 + b_Mu2;

  if (b_Dilep.M() >= 120.0 && b_Dilep.M() <= 130.0) {
    b_sigCount = 1;
  }
  /// BDT Varialbe Set ALL ///
  b_all_muEtaDiff = fabs(b_Mu1.Eta() - b_Mu2.Eta());
  b_all_muPtDiff = fabs(b_Mu1.Pt() - b_Mu2.Pt());
  b_all_muPhiDiff = b_Mu1.DeltaPhi(b_Mu2);
  b_DilepPt = b_Dilep.Pt();
  b_DilepEta = b_Dilep.Eta();
  
  // Extra lep //
  if (Muons.size() + Elecs.size() >= 3 && BJets.size() >= 1) {
     b_XL = 1;

     b_CSV = b_CSVv2[0];
     if (b_Mu_tlv.size() > 0) {
       MuPT_Hold = b_Mu_tlv[0].Pt();
       for (UInt_t k=0; k < b_Mu_tlv.size(); k++) {
         mT_Hold = sqrt(2.0*b_Mu_tlv[k].Pt()*b_Met*(1-cos(DeltaP(b_Mu_tlv[k].Phi(), b_Met_phi))));
         if (mT_Hold > b_mT2) {
            b_mT2 = mT_Hold; 
         }
       } 
     }
     if (Elecs.size() > 0) {
       ElPT_Hold = b_El_tlv[0].Pt();
       for (UInt_t k=0; k < Elecs.size(); k++) {
         mT_Hold = sqrt(2.0*b_El_tlv[k].Pt()*b_Met*(1-cos(DeltaP(b_El_tlv[k].Phi(), b_Met_phi))));
         if (mT_Hold > b_mT2) {
           b_mT2 = mT_Hold; 
         }
       }
     }
     if (ElPT_Hold > MuPT_Hold) {
       b_XlepPt = ElPT_Hold;
     } else {
       b_XlepPt = MuPT_Hold; 
     }
     if (nonbJets.size() >= 2) {
       b_DiJetM1 = b_nonbJet_tlv[0] + b_nonbJet_tlv[1];
       b_DiJetM1M = b_DiJetM1.M();
     }

     for (UInt_t i = 0; i < BJets.size(); i++) {
       if (Elecs.size() > 0) {
         for (UInt_t m = 0; m < Elecs.size(); m++) { 
           DR_Hold = b_bJet_tlv[i].DeltaR(b_El_tlv[m]);
           if (DR_Hold < b_minDR || b_minDR < 0) {
             b_minDR = DR_Hold;
           }
         }
       }
       if (b_Mu_tlv.size() > 0) {
         for (UInt_t n = 0; n < Muons.size(); n++) {
           DR_Hold =b_bJet_tlv[i].DeltaR(b_Mu_tlv[n]);
           if (DR_Hold < b_minDR || b_minDR < 0) {
             b_minDR = DR_Hold;
           }
         }
       }
     }
     mTmu2 = sqrt(2.0*b_Mu2.Pt()*b_Met*(1-cos(DeltaP(b_Mu2.Phi(), b_Met_phi))));
     mTmu1 = sqrt(2.0*b_Mu1.Pt()*b_Met*(1-cos(DeltaP(b_Mu1.Phi(), b_Met_phi))));
     mT_Hold = max(mTmu1, mTmu2);
     b_mT = max(mT_Hold, b_mT2);
     h_XL->Fill(0.5, b_XL); 

     // BDT Evaluation //
     b_MVA_BDTXL = bdt_XL->EvaluateMVA("BDTG");
     b_MVA_TTJXL = bdt_TTJXL->EvaluateMVA("BDTG");
     b_MVA_TTZXL = bdt_TTZXL->EvaluateMVA("BDTG");
  }
  // Hadronic //
  if ((Elecs.size() == 0 && Muons.size() == 2 && BJets.size() >= 1 && nonbJets.size() >= 4)) {
     b_nFH4 = 1;
     b_CSV = b_CSVv2[0];
     
     // Method 1
     b_DiJetM1 = b_nonbJet_tlv[0] + b_nonbJet_tlv[1];
     b_DiJetM2 = b_nonbJet_tlv[0] + b_nonbJet_tlv[2]; 
     b_DiJetM3 = b_nonbJet_tlv[0] + b_nonbJet_tlv[3];
     b_DiJetM4 = b_nonbJet_tlv[1] + b_nonbJet_tlv[2];
     b_DiJetM5 = b_nonbJet_tlv[1] + b_nonbJet_tlv[3];
     b_DiJetM6 = b_nonbJet_tlv[2] + b_nonbJet_tlv[3];
     
     b_DiJetM12 = b_DiJetM1.M(); 
     b_DiJetM13 = b_DiJetM2.M();
     b_DiJetM14 = b_DiJetM3.M();
     b_DiJetM23 = b_DiJetM4.M();
     b_DiJetM24 = b_DiJetM5.M();
     b_DiJetM34 = b_DiJetM6.M();
    
     if (BJets.size() == 1) { 
        b_top1 = b_DiJetM1 + b_bJet_tlv[0]; 
        b_top2 = b_DiJetM2 + b_bJet_tlv[0]; 
        b_top3 = b_DiJetM3 + b_bJet_tlv[0]; 
        b_top4 = b_DiJetM4 + b_bJet_tlv[0]; 
        b_top5 = b_DiJetM5 + b_bJet_tlv[0]; 
        b_top6 = b_DiJetM6 + b_bJet_tlv[0]; 
        TopVector_hold.push_back(b_top1);
        TopVector_hold.push_back(b_top2);
        TopVector_hold.push_back(b_top3);
        TopVector_hold.push_back(b_top4);
        TopVector_hold.push_back(b_top5);
        TopVector_hold.push_back(b_top6);

        for (UInt_t i = 0; i < TopVector_hold.size(); i++) {
           if (m_topM_hold1 == 0 || (fabs(m_topM_hold1 - TopM) > fabs(TopVector_hold[i].M() - TopM))) {
              m_topM_hold1 = TopVector_hold[i].M();
              b_b_top1 = TopVector_hold[i];
           }       
        }
    }
     if (BJets.size() == 2) { 
        b_top1 = b_DiJetM1 + b_bJet_tlv[0]; 
        b_top2 = b_DiJetM2 + b_bJet_tlv[0]; 
        b_top3 = b_DiJetM3 + b_bJet_tlv[0]; 
        b_top4 = b_DiJetM4 + b_bJet_tlv[0]; 
        b_top5 = b_DiJetM5 + b_bJet_tlv[0]; 
        b_top6 = b_DiJetM6 + b_bJet_tlv[0]; 
        b_top7 = b_DiJetM1 + b_bJet_tlv[1]; 
        b_top8 = b_DiJetM2 + b_bJet_tlv[1]; 
        b_top9 = b_DiJetM3 + b_bJet_tlv[1]; 
        b_top10 = b_DiJetM4 + b_bJet_tlv[1]; 
        b_top11 = b_DiJetM5 + b_bJet_tlv[1]; 
        b_top12 = b_DiJetM6 + b_bJet_tlv[1]; 
        TopVector_hold.push_back(b_top1);
        TopVector_hold.push_back(b_top2);
        TopVector_hold.push_back(b_top3);
        TopVector_hold.push_back(b_top4);
        TopVector_hold.push_back(b_top5);
        TopVector_hold.push_back(b_top6);
        TopVector_hold.push_back(b_top7);
        TopVector_hold.push_back(b_top8);
        TopVector_hold.push_back(b_top9);
        TopVector_hold.push_back(b_top10);
        TopVector_hold.push_back(b_top11);
        TopVector_hold.push_back(b_top12);

        for (UInt_t i = 0; i < 6; i++) {
           if (m_topM_hold1 == 0 || (fabs(m_topM_hold1 - TopM) > fabs(TopVector_hold[i].M() - TopM))) {
              m_topM_hold1 = TopVector_hold[i].M();
              b_b_top1 = TopVector_hold[i];
           }       
        }
        for (UInt_t i = 6; i < 12; i++) {
           if (m_topM_hold2 == 0 || (fabs(m_topM_hold2 - TopM) > fabs(TopVector_hold[i].M() - TopM))) {
              m_topM_hold2 = TopVector_hold[i].M();
              b_b_top2 = TopVector_hold[i];
           }       
        }
     
     m_topM_hold2 = 0; m_topM_hold1 = 0; 
     TopVector_hold.clear();

     }
     // Method 2 
     if (Jets.size() >= 6) { 
        for (UInt_t i = 0; i < Jets.size(); i++) {
           if (hold_Csv1 < b_CSVv2[i]){
              hold_Csv1 = b_CSVv2[i];
              m2_Jet1 = b_Jet_tlv[i];
           }
        }
        for (UInt_t i = 0; i < Jets.size(); i++) {
           if (hold_Csv2 < b_CSVv2[i] && b_CSVv2[i] != hold_Csv1) { 
              hold_Csv2 = b_CSVv2[i];
              m2_Jet2 = b_Jet_tlv[i];
           }
        }

        for (UInt_t i = 0; i < Jets.size(); i++) {
           if (hold_pT3 < b_Jet_tlv[i].Pt() && (b_Jet_tlv[i].Pt() != m2_Jet2.Pt() && b_Jet_tlv[i].Pt() != m2_Jet1.Pt())){
              hold_pT3 = b_Jet_tlv[i].Pt();
              m2_Jet3 = b_Jet_tlv[i];
           }
        }
        for (UInt_t i = 0; i < Jets.size(); i++) {
           if (hold_pT4 < b_Jet_tlv[i].Pt() && (b_Jet_tlv[i].Pt() != hold_pT3)  && (b_Jet_tlv[i].Pt() != m2_Jet2.Pt() && b_Jet_tlv[i].Pt() != m2_Jet1.Pt())){
              hold_pT4 = b_Jet_tlv[i].Pt();
              m2_Jet4 = b_Jet_tlv[i];
           }
        }
        for (UInt_t i = 0; i < Jets.size(); i++) {
           if (hold_pT5 < b_Jet_tlv[i].Pt() && (b_Jet_tlv[i].Pt() != hold_pT4 && b_Jet_tlv[i].Pt() != hold_pT3) && (b_Jet_tlv[i].Pt() != m2_Jet2.Pt() && b_Jet_tlv[i].Pt() != m2_Jet1.Pt())){
              hold_pT5 = b_Jet_tlv[i].Pt();
              m2_Jet5 = b_Jet_tlv[i];
           }
        }
        for (UInt_t i = 0; i < Jets.size(); i++) {
           if (hold_pT6 < b_Jet_tlv[i].Pt() && (b_Jet_tlv[i].Pt() != hold_pT5 && b_Jet_tlv[i].Pt() != hold_pT4 && b_Jet_tlv[i].Pt() != hold_pT3) && (b_Jet_tlv[i].Pt() != m2_Jet2.Pt() && b_Jet_tlv[i].Pt() != m2_Jet1.Pt())){
              hold_pT6 = b_Jet_tlv[i].Pt();
              m2_Jet6 = b_Jet_tlv[i];
           }
        }
        b_bjetDR = m2_Jet1.DeltaR(m2_Jet2);
        // Combination for W Jet 
        m2_DiJetM1 = m2_Jet3 + m2_Jet4; 
        m2_DiJetM2 = m2_Jet3 + m2_Jet5; 
        m2_DiJetM3 = m2_Jet3 + m2_Jet6; 
        m2_DiJetM4 = m2_Jet4 + m2_Jet5; 
        m2_DiJetM5 = m2_Jet4 + m2_Jet6; 
        m2_DiJetM6 = m2_Jet5 + m2_Jet6; 
        // Combination for Top 
        m2_top1 = m2_DiJetM1 + m2_Jet1; 
        m2_top2 = m2_DiJetM2 + m2_Jet1; 
        m2_top3 = m2_DiJetM3 + m2_Jet1; 
        m2_top4 = m2_DiJetM4 + m2_Jet1; 
        m2_top5 = m2_DiJetM5 + m2_Jet1; 
        m2_top6 = m2_DiJetM6 + m2_Jet1; 
        m2_top7 = m2_DiJetM1 + m2_Jet2; 
        m2_top8 = m2_DiJetM2 + m2_Jet2; 
        m2_top9 = m2_DiJetM3 + m2_Jet2; 
        m2_top10 = m2_DiJetM4 + m2_Jet2; 
        m2_top11 = m2_DiJetM5 + m2_Jet2; 
        m2_top12 = m2_DiJetM6 + m2_Jet2;
        
        TopVector_hold.push_back(m2_top1);
        TopVector_hold.push_back(m2_top2);
        TopVector_hold.push_back(m2_top3);
        TopVector_hold.push_back(m2_top4);
        TopVector_hold.push_back(m2_top5);
        TopVector_hold.push_back(m2_top6);
        TopVector_hold.push_back(m2_top7);
        TopVector_hold.push_back(m2_top8);
        TopVector_hold.push_back(m2_top9);
        TopVector_hold.push_back(m2_top10);
        TopVector_hold.push_back(m2_top11);
        TopVector_hold.push_back(m2_top12);

        for (UInt_t i = 0; i < 6; i++) {
           if (m_topM_hold1 == 0 ||(fabs(m_topM_hold1 - TopM) > fabs(TopVector_hold[i].M() - TopM))) {
              m_topM_hold1 = TopVector_hold[i].M();
              m2_b_top1 = TopVector_hold[i];
           }       
        }
        for (UInt_t i = 6; i < 12; i++) {
           if (m_topM_hold2 ==0 || (fabs(m_topM_hold2 - TopM) > fabs(TopVector_hold[i].M() - TopM))) {
              m_topM_hold2 = TopVector_hold[i].M();
              m2_b_top2 = TopVector_hold[i];
           }       
        }
     }
     b_topDR = m2_b_top1.DeltaR(m2_b_top2);
     for (UInt_t i = 0; i < BJets.size(); i++) {
       DR_Hold = b_bJet_tlv[i].DeltaR(b_Mu1);
       DR_Hold2 =b_bJet_tlv[i].DeltaR(b_Mu2);
       if (DR_Hold < b_minDR1 || b_minDR1 < 0) {
         b_minDR1 = DR_Hold;
       }
       if (DR_Hold2 > b_minDR2 || b_minDR2 < 0) {
         b_minDR2 = DR_Hold2;
       }
     }
     
     mTmu1 = sqrt(2.0*b_Mu1.Pt()*b_Met*(1-cos(DeltaP(b_Mu1.Phi(), b_Met_phi))));
     mTmu2 = sqrt(2.0*b_Mu2.Pt()*b_Met*(1-cos(DeltaP(b_Mu2.Phi(), b_Met_phi))));
     b_mT = max(mTmu1, mTmu2);
     h_nFH4->Fill(0.5, b_nFH4); 
     // BDT Evaluation //
     b_MVA_BDTFH = bdt_FH->EvaluateMVA("BDTG");
     b_MVA_TTJFH = bdt_TTJFH->EvaluateMVA("BDTG");
  }
  //Outsider //
  if (BJets.size() >= 1 && b_nFH4 == 0 && b_XL == 0) {
     b_Out = 1;
     b_CSV = b_CSVv2[0];
     if (nonbJets.size() >= 2) {
        b_JetEtaDiff = fabs(b_nonbJet_tlv[0].Eta() - b_nonbJet_tlv[1].Eta());  
        b_DiJetM1 = b_nonbJet_tlv[0] + b_nonbJet_tlv[1];
        b_DiJetM1M = b_DiJetM1.M();
        b_DiJetM1Eta = b_DiJetM1.Eta();
        b_DiJetM1Pt = b_DiJetM1.Pt();
     }     

     mTmu1 = sqrt(2.0*b_Mu1.Pt()*b_Met*(1-cos(DeltaP(b_Mu1.Phi(), b_Met_phi))));
     mTmu2 = sqrt(2.0*b_Mu2.Pt()*b_Met*(1-cos(DeltaP(b_Mu2.Phi(), b_Met_phi))));
     b_mT = max(mTmu1, mTmu2);
     
     h_Out->Fill(0.5,b_Out);
     // BDT Evaluation //
     b_MVA_BDTOut = bdt_Out->EvaluateMVA("BDTG");
     b_MVA_DYOut = bdt_DYOut->EvaluateMVA("BDTG");
     b_MVA_TTJOut = bdt_TTJOut->EvaluateMVA("BDTG");
  }

  // nob // 
  if (BJets.size() == 0) {
     b_nonB = 1;
     b_nexLep = Muons.size() + Elecs.size() - 2;
     if (Jets.size() >= 2) {
       TLorentzVector j1; 
       TLorentzVector j2; 
       b_etaJ1 = b_Jet_tlv[0].Eta();
       b_etaJ2 = b_Jet_tlv[1].Eta();

       for (auto& J1 : b_Jet_tlv) {
         for (auto& J2 : b_Jet_tlv) {
           if (J1.M() != J2.M()) { 
             TLorentzVector Dijet_hold = J1 + J2;
             if (Dijet_hold.M() > b_DijetM2) {
               b_DijetM2 = Dijet_hold.M();
               b_DijetEta2 = Dijet_hold.Eta();
             }    
             if (b_DijetM1 == b_DijetM2) {
               b_DijetM2 = 0; 
             }    
             if (b_DijetM2 > b_DijetM1) {
               DijetM_hold = b_DijetM1;
               DijetEta_hold = b_DijetEta1;

        
               b_DijetM1 = b_DijetM2;
               b_DijetEta1 = b_DijetEta2;

               b_DijetM2 = DijetM_hold;
               b_DijetEta2 = DijetEta_hold; 
            }    
          }    
        }    
      }    
    }
    h_Non->Fill(0.5, b_nonB);
    // BDT Evaluation //
    b_MVA_BDTnoB = bdt_noB->EvaluateMVA("BDTG");
    b_MVA_DYnoB = bdt_DYnoB->EvaluateMVA("BDTG");
    b_MVA_TTJnoB = bdt_TTJnoB->EvaluateMVA("BDTG");
  }

  ////////// BDT //////////////////////////////
  b_mueffweight = m_muonSF.getScaleFactor(mu1, 13, 0)*m_muonSF.getScaleFactor(mu2, 13, 0);
  b_mueffweight_up = m_muonSF.getScaleFactor(mu1, 13, +1)*m_muonSF.getScaleFactor(mu2, 13, +1);
  b_mueffweight_dn = m_muonSF.getScaleFactor(mu1, 13, -1)*m_muonSF.getScaleFactor(mu2, 13, -1);

  //b_weight = b_weight*b_mueffweight*b_btagweight;
  b_Event_No = 1;
  /*
  b_MVA_BDTXL = bdt_XL->EvaluateMVA("BDTG");
  b_MVA_BDTFH = bdt_FH->EvaluateMVA("BDTG");
  b_MVA_BDTnoB = bdt_noB->EvaluateMVA("BDTG");
  b_MVA_BDTOut = bdt_Out->EvaluateMVA("BDTG");
  */

  return true;
}


void h2muAnalyser::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  
  // Events loop
  for (Long64_t iev=0; iev<nentries; iev++) {
    ResetBranch();
    fChain->GetEntry(iev);
    bool keep = Analysis();
    if (keep) { m_tree->Fill(); }
  }

}

int main(Int_t argc, Char_t** argv)
{
  string env = getenv("CMSSW_BASE");
  string username = getenv("USER");

  if (argc != 1) {
    string dirName = "root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/"+username+"/nanoAOD/"+std::string(argv[1])+"/"+std::string(argv[2]);
    string temp = argv[2];
    Bool_t isMC = false;
    Size_t found = temp.find("Run");
    if(found == string::npos) isMC = true;
    for (Int_t i = 3; i < argc; i++) {
      cerr << argv[i] << endl;
      TFile *f = TFile::Open(argv[i], "read");

      TTree *tree;
      f->GetObject("Events", tree);

      temp = argv[i];
      found = temp.find_last_of('/');
      string outPutName = dirName+temp.substr(found);
      h2muAnalyser t(tree, isMC);
      t.SetOutput(outPutName);
      t.Loop();
    }
  } else {
    //TFile *f = TFile::Open("/xrootd/store/group/nanoAOD/run2_2016v5/TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/180611_081410/0000/nanoAOD_122.root", "read");

  //  TFile *f = TFile::Open("/xrootd/store/group/nanoAOD/run2_2016v3/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/180125_131129/0000/nanoAOD_100.root", "read");
    //TFile *f = TFile::Open("/xrootd/store/group/nanoAOD/run2_2016v5/ttHToMuMu_M125_13TeV-powheg-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6/180611_131219/0000/nanoAOD_100.root", "read");
    TFile *f = TFile::Open("/xrootd/store/group/nanoAOD/run2_2016v5/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/180607_115426/0000/nanoAOD_440.root", "read");

    //TFile *f = TFile::Open("/xrootd/store/group/nanoAOD/run2_2016v4/SingleMuon/Run2016C-07Aug17-v1/180504_150105/0000/nanoAOD_140.root", "read");
    TTree *tree;
    Bool_t isMC = false;
    string temp = "Run";
    Size_t found = temp.find("Run123123");
    if(found == string::npos) isMC = true;
    f->GetObject("Events", tree);

      h2muAnalyser t(tree, isMC);    
    t.SetOutput("test.root");
    t.Loop();
  }

  return 0;
}

//Object Selections
vector<TParticle> h2muAnalyser::MuonSelection()
{
  vector<TParticle> muons;
  for (UInt_t i = 0; i < nMuon; i++) {
    if (!Muon_trackerMu[i]) continue;
    if (!Muon_globalMu[i]) continue;
    if (!Muon_tightId[i]) continue;
   // if (!Muon_mediumId[i]) continue;
    if (Muon_pfRelIso04_all[i] > 0.25) continue;
    
    TLorentzVector mom;
    mom.SetPtEtaPhiM(Muon_pt[i], Muon_eta[i], Muon_phi[i], Muon_mass[i]);
    mom = mom * roccoR(mom, Muon_charge[i], Muon_genPartIdx[i], Muon_nTrackerLayers[i]);
    
    if (mom.Pt() < 20) continue;
    if (fabs(mom.Eta() > 2.4)) continue;
   
    auto muon = TParticle();
    muon.SetPdgCode(13*Muon_charge[i]*-1);
    muon.SetMomentum(mom);

    b_Mu_tlv.push_back(mom);
    muons.push_back(muon);
  }
  return muons;
}

vector<TParticle> h2muAnalyser::ElectronSelection(vector<TParticle> leptons)
{
  vector<TParticle> electrons;
  for(UInt_t i = 0; i < nElectron; i++) {
    if ( Electron_pt[i] < 10) continue;
    if (fabs(Electron_eta[i]) > 2.5 ) continue; //<~~~~~~~~~~~~~~ Higgs Electron pt == 10; Higgs Electron eta > 2.5  
    if( Electron_pfRelIso03_all[i] > 0.15) continue;
    if (Electron_cutBased[i] < 3) continue;
    float el_scEta = Electron_deltaEtaSC[i] + Electron_eta[i];
    if ( std::fabs(el_scEta) > 1.4442 &&  std::fabs(el_scEta) < 1.566 ) continue;

    TLorentzVector mom;
    mom.SetPtEtaPhiM(Electron_pt[i], Electron_eta[i], Electron_phi[i], Electron_mass[i]);

    if (hasOverLap(mom, leptons, 0.4)) continue;
    
    auto elec = TParticle();
    elec.SetPdgCode(11*Electron_charge[i]*-1);
    elec.SetMomentum(mom);
    
    b_El_tlv.push_back(mom);
    electrons.push_back(elec);
  }
  return electrons;
}
vector<TParticle> h2muAnalyser::JetSelection(vector<TParticle> Muons, vector<TParticle> Elecs)
{
  vector<TParticle> jets;

  b_btagweightB = 1., btagweightC = 1., btagweightL = 1.;

  for (UInt_t i = 0; i < nJet; i++) {
    if (Jet_pt[i] < 30) continue;
    if (fabs(Jet_eta[i]) > 2.4) continue; 
    if (Jet_jetId[i] < 1) continue;
    if (Jet_puId[i] != 7) continue; 
    TLorentzVector mom;
    mom.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);
    
    if (hasOverLap(mom, Muons, 0.4)) continue;
    if (hasOverLap(mom, Elecs, 0.4)) continue;
    
    auto jet = TParticle();
    b_CSVv2.push_back(Jet_btagCSVV2[i]);
    jet.SetMomentum(mom);
    b_Jet_tlv.push_back(mom);
    b_Jet->push_back(mom);
    jets.push_back(jet);


    // Btag Weight - test //
    if(m_isMC){
       if (Jet_hadronFlavour[i] == 0) {
          btagweightL = reader.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(Jet_eta[i]), Jet_pt[i], Jet_btagCSVV2[i]);
          if (btagweightL != 0) btagweightL *= btagweightL;
          for (auto key : sysl){ 
             if (!*sys_l[key]) continue;  
             *sys_l[key] = reader.eval_auto_bounds(key, BTagEntry::FLAV_UDSG, fabs(Jet_eta[i]), Jet_pt[i], Jet_btagCSVV2[i]);
             if (*sys_l[key] != 0) *sys_l[key] *= *sys_l[key];  
          }
       }
       if (Jet_hadronFlavour[i] == 4) {
          btagweightC = reader.eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(Jet_eta[i]), Jet_pt[i], Jet_btagCSVV2[i]);
          if (btagweightC != 0) btagweightC *= btagweightC;
          for (auto key : sysc){ 
             if (!*sys_c[key]) continue;
             *sys_c[key] = reader.eval_auto_bounds(key, BTagEntry::FLAV_C, fabs(Jet_eta[i]), Jet_pt[i], Jet_btagCSVV2[i]);
             if (*sys_c[key] != 0) *sys_c[key] *= *sys_c[key];  
          }
       }
       // Iterative Fit // 
       if (Jet_hadronFlavour[i] == 5) {
          b_btagweightB = reader.eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(Jet_eta[i]), Jet_pt[i], Jet_btagCSVV2[i]);
          if (b_btagweightB != 0) b_btagweightB *= b_btagweightB;
          for (auto key : sysb){ 
             if (!*sys_b[key]) continue; 
             *sys_b[key] = reader.eval_auto_bounds(key, BTagEntry::FLAV_B, fabs(Jet_eta[i]), Jet_pt[i], Jet_btagCSVV2[i]);
             if (*sys_b[key] != 0) *sys_b[key] *= *sys_b[key];  
          }
       }
    }
    b_btagweight = b_btagweightB * btagweightC * btagweightL; 
  }
  return jets;
}

vector<TParticle> h2muAnalyser::BJetSelection(vector<TParticle> Muons, vector<TParticle> Elecs)
{
  vector<TParticle> bJets;
  for (UInt_t i = 0; i < nJet; i++) {
    if (Jet_btagCSVV2[i] <= 0.8484) continue;
    if (Jet_pt[i] < 30) continue;
    if (fabs(Jet_eta[i]) > 2.4) continue;
    if (Jet_puId[i] != 7) continue; 
    
    TLorentzVector mom;
    mom.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);
    
    if (hasOverLap(mom, Muons, 0.4)) continue;
    if (hasOverLap(mom, Elecs, 0.4)) continue;
    
    auto bjet = TParticle();
    bjet.SetMomentum(mom);
    b_bJet_tlv.push_back(mom);
    b_bJet->push_back(mom);
    bJets.push_back(bjet);
  }
  return bJets;
}

vector<TParticle> h2muAnalyser::nonbJetSelection(vector<TParticle> Muons, vector<TParticle> Elecs)
{
  vector<TParticle> nonbjets;
  for (UInt_t i = 0; i < nJet; i++) {
    if (Jet_pt[i] < 30) continue; 
    if (fabs(Jet_eta[i]) > 2.4) continue; 
    if (Jet_jetId[i] < 1) continue;
    if (Jet_puId[i] != 7) continue; 

    if (Jet_btagCSVV2[i] > 0.8484) continue;

    TLorentzVector mom;
    mom.SetPtEtaPhiM(Jet_pt[i], Jet_eta[i], Jet_phi[i], Jet_mass[i]);
    
    if (hasOverLap(mom, Muons, 0.4)) continue;
    if (hasOverLap(mom, Elecs, 0.4)) continue;
    
    auto jet = TParticle();
    jet.SetMomentum(mom);
    b_nonbJet_tlv.push_back(mom);  
    b_nonbJet->push_back(mom);
    nonbjets.push_back(jet);
  }
  return nonbjets;
}
bool h2muAnalyser::hasOverLap(TLorentzVector cand, vector<TParticle> objects, Float_t rad)
{
  for (auto obj: objects) {
    TLorentzVector mom;
    obj.Momentum(mom);
    if (cand.DeltaR(mom) < rad) {
      return true;
    }
  }
  return false;
}

Double_t h2muAnalyser::roccoR(TLorentzVector m, int &q, int &nGen, int &nTrackerLayers)
{
  Float_t u1 = gRandom->Rndm();
  Float_t u2 = gRandom->Rndm();
  if (!m_isMC) {
    return m_rocCor->kScaleDT(q, m.Pt(), m.Eta(), m.Phi(), 0, 0);
  } else {
    if (nGen > -1) {
      return m_rocCor->kScaleFromGenMC(q, m.Pt(), m.Eta(), m.Phi(),
				       nTrackerLayers, GenPart_pt[nGen],
				       u1, 0, 0);
    } else return m_rocCor->kScaleAndSmearMC(q, m.Pt(), m.Eta(), m.Phi(),
	        			     nTrackerLayers, u1, u2, 0, 0);
  }
}
Double_t h2muAnalyser::DeltaP(double m1, float m2)
{  
   dphi = m1 - m2;
   if (dphi > M_PI) {
      dphi -= 2.0*M_PI;
   } else {
      dphi += 2.0*M_PI; 
   }
   return dphi;
}


