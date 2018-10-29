#ifndef h2muAnalyser_H
#define h2muAnalyser_H
#include "nanoBase.h"

class h2muAnalyser : public nanoBase {
private: 
  //histogram
  TH1D* h_Event_Tot;
  TH1D* h_genweights;
  TH1D* h_weight;
  TH1D* h_Posweight;
  TH1D* h_XL;
  TH1D* h_nFH4;
  TH1D* h_Out;
  TH1D* h_Non;
  //Variables
  TLorentzVector b_Dilep, b_Mu1, b_Mu2;
  TLorentzVector b_lep;
  TLorentzVector b_nonbJet1, b_nonbJet2 ,b_nonbJet3 ,b_nonbJet4;
  
  //Top Reco variables 
  //version 1
  TLorentzVector m_Jet1, m_Jet2, m_Jet3 ,m_Jet4;
  TLorentzVector b_DiJetM1, b_DiJetM2, b_DiJetM3, b_DiJetM4, b_DiJetM5, b_DiJetM6;
  TLorentzVector b_top1, b_top2, b_top3, b_top4, b_top5, b_top6, b_top7, b_top8, b_top9, b_top10, b_top11, b_top12;
  std::vector<TLorentzVector> TopVector_hold;
  Double_t hold_pT3, hold_pT4, hold_pT5, hold_pT6;
  //version 2 
  TLorentzVector m2_Jet1, m2_Jet2, m2_Jet3, m2_Jet4, m2_Jet5, m2_Jet6;
  TLorentzVector m2_DiJetM1, m2_DiJetM2, m2_DiJetM3, m2_DiJetM4, m2_DiJetM5, m2_DiJetM6;
  TLorentzVector m2_top1, m2_top2, m2_top3, m2_top4, m2_top5, m2_top6, m2_top7, m2_top8, m2_top9, m2_top10, m2_top11, m2_top12;
  Float_t hold_Csv1, hold_Csv2;

  // Version 3
  TLorentzVector m2_b_top1, m2_b_top2, b_b_top1, b_b_top2;
  Float_t m_topM_hold1, m_topM_hold2, stupid_hold;
  Float_t TopM = 172.44; 
  Float_t b_topDR, b_bjetDR;

  Float_t b_DilepPt, b_DilepEta, b_DiJetM1M, b_DiJetM1Eta, b_DiJetM1Pt, b_JetEtaDiff;
  std::vector<TLorentzVector> b_Mu_tlv, b_El_tlv, b_Jet_tlv, b_bJet_tlv, b_nonbJet_tlv;
  std::vector<TLorentzVector> *b_bJet = 0;
  std::vector<TLorentzVector> *b_nonbJet = 0;
  std::vector<TLorentzVector> *b_Jet = 0;
  std::vector<Float_t> b_CSVv2;
  std::vector<Float_t> b_csvweights;
  std::vector<Int_t> b_Jet_pu;
  
  Float_t dphi;
  Float_t b_genweight, b_weight;
  Float_t b_puweight, b_puweight_up, b_puweight_dn; 
  Float_t b_mueffweight, b_mueffweight_up, b_mueffweight_dn;
  Float_t b_btagweight, b_btagweight_up, b_btagweight_dn;
  Float_t b_btagweightB, btagweightC, btagweightL;
  Float_t b_jes_up, b_jes_dn, b_lf_up, b_lf_dn, b_hfstats1_up, b_hfstats1_dn, b_hfstats2_up, b_hfstats2_dn; 
  Float_t b_cferr1_up, b_cferr1_dn, b_cferr2_up, b_cferr2_dn, b_lfstats1_up, b_lfstats1_dn, b_lfstats2_up, b_lfstats2_dn, b_hf_up, b_hf_dn;
  
  std::map<std::string, Float_t*> sys_b;
  std::map<std::string, Float_t*> sys_c;
  std::map<std::string, Float_t*> sys_l;

  Float_t b_Jet_eta1, b_Jet_eta2, b_Jet_eta3, b_Jet_eta4; 
  Int_t b_Event_No, b_Event_Total;
  // BDT Variables
  Float_t b_Central_Jets, b_Forward_Jets; 
  // all
  Float_t b_Met;
  Float_t b_Met_ori;
  Float_t b_npvs;
  Float_t b_Met_phi;
  Float_t b_all_Dilep_Pt, b_all_Dilep_Eta ,b_all_Dilep_Phi;
  Float_t b_all_muEtaDiff, b_all_muPtDiff, b_all_muPhiDiff, b_all_muDR;
  Float_t b_DijetM1, b_DijetM2, b_DijetEta1, b_DijetEta2, DijetM_hold, DijetEta_hold;
  Float_t b_MVA_TTJXL, b_MVA_TTZXL, b_MVA_TTJFH, b_MVA_DYOut, b_MVA_TTJOut, b_MVA_DYnoB, b_MVA_TTJnoB;
  Float_t b_DiJetM12, b_DiJetM13, b_DiJetM14 ,b_DiJetM23 , b_DiJetM24, b_DiJetM34;
  Float_t b_MVA_BDTXL, b_MVA_BDTFH, b_MVA_BDTnoB, b_MVA_BDTOut;
  Float_t b_minDR1, b_minDR2, b_minDR, b_XlepPt, b_mT2, b_mT;
  Float_t DR_Hold, DR_Hold2, MuPT_Hold ,ElPT_Hold, mT_Hold;
  Float_t b_etaJ1, b_etaJ2;
  Float_t b_CSV;
  Float_t mTmu1, mTmu2;
  Int_t b_sigCount;
  //Step and Cutflow
  TH1D* h_cutFlow;
  Int_t b_Step;

  //Channel
  Int_t b_channel;
  Float_t b_nlep, b_nmuon, b_nelec, b_njet, b_nbjet, b_charge, b_nnonbjet, b_nexLep;
  Bool_t keep;
  //triggers
  Bool_t b_trig_m, b_trig_m2,  b_trig_e, b_trig_mm, b_trig_em, b_trig_ee;
  Int_t b_FL, b_FH2, b_FH3, b_FH4, b_SL;
  Int_t b_XL, b_nFH4, b_Out, b_nonB;
  //weight files //
  std::string weightXL, weightFH, weightnoB, weightOut;
  std::string TTJXL, TTZXL, TTJFH, TTZFH, DYnoB, TTJnoB, TTZnoB, DYOut, TTJOut, TTZOut;
  
  //Tools
  std::vector<UInt_t> idxs;

  TMVA::Reader* bdt_XL;
  TMVA::Reader* bdt_TTJXL;
  TMVA::Reader* bdt_TTZXL;

  TMVA::Reader* bdt_FH;
  TMVA::Reader* bdt_TTJFH;
  //TMVA::Reader* bdt_TTZFH;
  
  TMVA::Reader* bdt_noB;
  TMVA::Reader* bdt_DYnoB;
  TMVA::Reader* bdt_TTJnoB;
  //TMVA::Reader* bdt_TTZnoB;

  TMVA::Reader* bdt_Out;
  TMVA::Reader* bdt_DYOut;
  TMVA::Reader* bdt_TTJOut;
  //TMVA::Reader* bdt_TTZOut;

  //Making output branch
  void MakeBranch(TTree* t);
  void ResetBranch();

  bool Analysis();
  //For Selection
  enum TTLLChannel { CH_NOLL = 0, CH_MUEL, CH_ELEL, CH_MUMU };

  bool hasOverLap(TLorentzVector cand, std::vector<TParticle> objects, Float_t rad);
  
  std::vector<TParticle> MuonSelection();
  std::vector<TParticle> ElectronSelection(std::vector<TParticle>);
  std::vector<TParticle> JetSelection(std::vector<TParticle>, std::vector<TParticle>);
  std::vector<TParticle> BJetSelection(std::vector<TParticle>, std::vector<TParticle>);
  std::vector<TParticle> nonbJetSelection(std::vector<TParticle>, std::vector<TParticle>);
  
  Double_t roccoR(TLorentzVector m, Int_t &q, Int_t &nGen, Int_t &nTrackerLayers);
  Double_t DeltaP(Double_t m1, Float_t m2);
public:
  //set output file
  h2muAnalyser(TTree *tree=0, Bool_t isMc = false);
  ~h2muAnalyser();
  void SetOutput(std::string outputName);
  virtual void Loop();
};

h2muAnalyser::h2muAnalyser(TTree *tree, Bool_t isMC) : nanoBase(tree, isMC)
{
  std::string env = getenv("CMSSW_BASE");
  m_rocCor = new RoccoR(env+"/src/nano/analysis/data/rcdata.2016.v3/");
  
  sys_b["up_jes"] = &b_jes_up; 
  sys_b["down_jes"] = &b_jes_dn; 
  sys_b["up_lf"] = &b_lf_up;
  sys_b["down_lf"] = &b_lf_dn;
  sys_b["up_hfstats1"] = &b_hfstats1_up;
  sys_b["down_hfstats1"] = &b_hfstats1_dn;
  sys_b["up_hfstats2"] = &b_hfstats2_up;
  sys_b["down_hfstats2"] = &b_hfstats2_dn;
  
  sys_l["up_jes"] = &b_jes_up; 
  sys_l["down_jes"] = &b_jes_dn; 
  sys_l["up_lfstats1"] = &b_lfstats1_up;
  sys_l["down_lfstats1"] = &b_lfstats1_dn;
  sys_l["up_lfstats2"] = &b_lfstats2_up;
  sys_l["down_lfstats2"] = &b_lfstats2_dn;
  sys_l["up_hf"] = &b_hf_up;
  sys_l["down_hf"] = &b_hf_dn;
  
  sys_c["up_cferr1"] = &b_cferr1_up;
  sys_c["down_cferr1"] = &b_cferr1_dn;
  sys_c["up_cferr2"] = &b_cferr2_up;
  sys_c["down_cferr2"] = &b_cferr2_dn;
}

h2muAnalyser::~h2muAnalyser()
{
}

#endif
