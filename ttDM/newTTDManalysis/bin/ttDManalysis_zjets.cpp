#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include <vector>
#include <assert.h>
#include <TMVA/Reader.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cassert>
#include <sstream>
#include <string>
#include "TFileCollection.h"
#include "THashList.h"
#include "ttDM/TopTagResolved/interface/KinematicFitter.hh"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "ttDM/newTTDManalysis/interface/Weights.h"
#include "ttDM/newTTDManalysis/interface/MT2Utility.h"
#include "ttDM/newTTDManalysis/interface/mt2w_bisect.h"
#include "ttDM/newTTDManalysis/interface/mt2bl_bisect.h"
#include "ttDM/newTTDManalysis/interface/Mt2Com_bisect.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "ttDM/localQGLikelihoodCalculator/localQGLikelihoodCalculator.h"
#include "ttDM/localQGLikelihoodCalculator/localQGLikelihoodCalculator.cc"

using namespace std;

typedef vector<double> vdouble;
typedef vector<float> vfloat;
typedef vector<int> vint;
typedef vector<bool> vbool;
typedef vector<string> vstring;

void callme(){
  std::cout<<" NaN value"<<std::endl;
}


float ciao(float eta1,float phi1,float eta2,float phi2)
{
  float DeltaPhi = TMath::Abs(phi1-phi2);
  float DeltaEta = eta1-eta2;
  if(DeltaPhi > TMath::Pi())
    DeltaPhi = TMath::TwoPi() - DeltaPhi;
  return TMath::Sqrt(DeltaEta*DeltaEta + DeltaPhi*DeltaPhi);
}


int main(int argc, char **argv) {

  std::cout<<"Let's start"<<endl;

  string sample(argv[1]) ;
  std::cout<<"sample: "<<sample<<endl;

  //TString path(argv[2]);                                                                                                   
  //std::cout<<"File to open: "<<path<<endl;

   string path(argv[2]);
  std::cout<<"File list to open: "<<path<<endl;

  string channel(argv[3]);
  std::cout<<"channel: "<<channel<<endl;

  string cat(argv[4]);
  std::cout<<"category:" <<cat<<endl;

  string sys(argv[5]);
  std::cout<<"systematics: "<<sys<<endl;

  string sync(argv[6]);
  std::cout<<"synchro: "<<sync<<endl;

  string isData(argv[7]);
  std::cout<<"isData: "<<isData<<endl;

  //  TString path_ = path + "/trees*.root";                                                                                 
  TString path_ = path ;
 std::cout<<"File to open: "<<path_<<endl;

  std::cout << "Loading file collection from " << path << std::endl;
  TFileCollection fc(sample.c_str(),sample.c_str(),path.c_str());
  std::cout << "Files found : " << fc.GetNFiles() << std::endl;                                               

  string reportName = "SelectedEvents_"+channel+"_"+cat+"_"+sample+".txt";
  ofstream fileout;
  fileout.open(reportName.c_str(),ios::in | ios::out | ios::trunc);
  fileout<<"RunNumber EvtNumber Lumi "<<std::endl;
  
  std::cout<<"File to open: "<<path_<<endl;
  TString treePath = "DMTreesDumper/ttDM__noSyst";
                                                                                                 
  TChain chain(treePath);
  chain.AddFileInfoList(fc.GetList());

  Int_t nEvents = (Int_t)chain.GetEntries();
  std::cout<<"Number of Events: "<<nEvents<< endl;
  //  nEvents=100000;
  //nEvents = std::min(nEvents, 1000000);                                                                                    
  int sizeMax=50;
  Int_t jetSize, genPartSize, muonSize;
  float passTrig(0.);

  float rho(0.), w(1.), runNumber(0.), lumiSec(0.);
  double evtNumber(0.);
  int n_jet(0.),n_test(0), n_trig(0), n_twomuons(0), n_isZ(0), n_isBackToBack(0), n_Leadjet(0);

  //  int genpartstatus[sizeMax], genpartid[sizeMax];
  float genpartpt[sizeMax], genparteta[sizeMax], genpartphi[sizeMax], genparte[sizeMax], genpartid[sizeMax], genpartstatus[sizeMax], genpartmomid[sizeMax], genpartmass[sizeMax];
  float jetflavour[sizeMax], jete[sizeMax], jetpt[sizeMax], jetphi[sizeMax], jeteta[sizeMax], jetcsv[sizeMax], jetIsLoose[sizeMax], pileupJetIdptD[sizeMax],pileupJetIdnParticles[sizeMax],pileupJetIdminW[sizeMax], jetqgl[sizeMax], jetmult[sizeMax], jetptd[sizeMax], jetaxis2[sizeMax], pileupJetIdRMS[sizeMax],pileupJetIdbeta[sizeMax], pileupJetIdbetaClassic[sizeMax], pileupJetIdbetaStar[sizeMax],pileupJetIdbetaStarClassic[sizeMax],pileupJetIddR2Mean[sizeMax],pileupJetIddRMean[sizeMax], pileupJetIddZ[sizeMax],pileupJetIdfrac01[sizeMax],pileupJetIdfrac02[sizeMax],pileupJetIdfrac03[sizeMax],pileupJetIdfrac04[sizeMax],pileupJetIdjetR[sizeMax],pileupJetIdjetRchg[sizeMax],pileupJetIdmajW[sizeMax],pileupJetIdnCharged[sizeMax],pileupJetIdnNeutrals[sizeMax],pileupJetIdpull[sizeMax] ;
   float muone[sizeMax], muonpt[sizeMax], muonphi[sizeMax], muoneta[sizeMax], muoncharge[sizeMax];
   
   float jetgenjetpt[sizeMax];
   
   chain.SetBranchAddress("genpart_Pt", genpartpt);
   chain.SetBranchAddress("genpart_Eta", genparteta);
   chain.SetBranchAddress("genpart_Phi", genpartphi);
   chain.SetBranchAddress("genpart_E", genparte);
   chain.SetBranchAddress("genpart_Mass", genpartmass);
   chain.SetBranchAddress("genpart_ID", genpartid);
   chain.SetBranchAddress("genpart_Status", genpartstatus);
   chain.SetBranchAddress("genpart_Mom0ID", genpartmomid);
   chain.SetBranchAddress("genpart_size", &genPartSize);
   
   //   chain.SetBranchAddress("jetsAK4Tight_PassesDR", jetpassesdr);
   //chain.SetBranchAddress("jetsAK4Tight_IsTight", jetpassesid);
   chain.SetBranchAddress("jetsAK4Tight_PartonFlavour", jetflavour);
   chain.SetBranchAddress("jetsAK4Tight_GenJetPt", jetgenjetpt);
   chain.SetBranchAddress("jetsAK4Tight_E", jete);
   chain.SetBranchAddress("jetsAK4Tight_Pt", jetpt);
   chain.SetBranchAddress("jetsAK4Tight_Phi", jetphi);
   chain.SetBranchAddress("jetsAK4Tight_Eta", jeteta);
   chain.SetBranchAddress("jetsAK4Tight_IsLoose", jetIsLoose);
   chain.SetBranchAddress("jetsAK4Tight_CSVv2", jetcsv);
   chain.SetBranchAddress("jetsAK4Tight_QGL", jetqgl);
   chain.SetBranchAddress("jetsAK4Tight_mult", jetmult);
   chain.SetBranchAddress("jetsAK4Tight_ptD", jetptd);
   chain.SetBranchAddress("jetsAK4Tight_axis2", jetaxis2);
   chain.SetBranchAddress("jetsAK4Tight_size", &jetSize);

   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdptD", pileupJetIdptD);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdnParticles",pileupJetIdnParticles);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdminW",pileupJetIdminW);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdRMS",pileupJetIdRMS);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdbeta", pileupJetIdbeta);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdbetaClassic", pileupJetIdbetaClassic);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdbetaStar", pileupJetIdbetaStar);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdbetaStarClassic",pileupJetIdbetaStarClassic);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIddR2Mean", pileupJetIddR2Mean);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIddRMean", pileupJetIddRMean);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIddZ", pileupJetIddZ);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdfrac01", pileupJetIdfrac01);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdfrac02",pileupJetIdfrac02);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdfrac03",pileupJetIdfrac03);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdfrac04",pileupJetIdfrac04);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdjetR",pileupJetIdjetR);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdjetRchg", pileupJetIdjetRchg);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdmajW", pileupJetIdmajW);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdnCharged", pileupJetIdnCharged);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdnNeutrals",pileupJetIdnNeutrals);
   chain.SetBranchAddress("jetsAK4Tight_pileupJetIdpull", pileupJetIdpull);

   chain.SetBranchAddress("muonsMedium_E", muone);
   chain.SetBranchAddress("muonsMedium_Pt", muonpt);
   chain.SetBranchAddress("muonsMedium_Phi", muonphi);
   chain.SetBranchAddress("muonsMedium_Eta", muoneta);
   chain.SetBranchAddress("muonsMedium_Charge", muoncharge);
   chain.SetBranchAddress("muonsMedium_size", &muonSize);
   //   chain.SetBranchAddress("muons_IsTight", &muonIsTight);
   
   //   chain.SetBranchAddress("Event_passesHLT_IsoMu20", &passTrig);
   chain.SetBranchAddress("Event_passesSingleMuTriggers",&passTrig);
   chain.SetBranchAddress("Event_Rho", &rho);
   chain.SetBranchAddress("Event_RunNumber", &runNumber);
   chain.SetBranchAddress("Event_LumiBlock", &lumiSec);
   chain.SetBranchAddress("Event_EventNumber", &evtNumber);

   int a,b;
   int N = 10, M=5;

   TH1F *h_qgl[N][M];
   TH1F *h_qgl2[N][M];
   TH1F *h_qgl3[N][M];
   TH1F *h_ptD[N][M] ;
   TH1F *h_minW[N][M] ;
   TH1F *h_nPart[N][M];
   TH1F *h_ptD_quark[N][M] ;
   TH1F *h_minW_quark[N][M] ;
   TH1F *h_nPart_quark[N][M];
   TH1F *h_ptD_gluon[N][M] ;
   TH1F *h_minW_gluon[N][M] ;
   TH1F *h_nPart_gluon[N][M];
   TH1F *h_ptD_undef[N][M] ;
   TH1F *h_minW_undef[N][M] ;
   TH1F *h_nPart_undef[N][M];
   TH1F *h_ptD_unmatched[N][M] ;
   TH1F *h_minW_unmatched[N][M] ;
   TH1F *h_nPart_unmatched[N][M];
   TH1F *h_qgl_quark[N][M];
   TH1F *h_qgl_gluon[N][M];
   TH1F *h_qgl_undef[N][M];
   TH1F *h_qgl_unmatched[N][M];
   TH1F *h_qgl2_quark[N][M];
   TH1F *h_qgl2_gluon[N][M];
   TH1F *h_qgl2_undef[N][M];
   TH1F *h_qgl2_unmatched[N][M];
   TH1F *h_qgl3_quark[N][M];
   TH1F *h_qgl3_gluon[N][M];
   TH1F *h_qgl3_undef[N][M];
   TH1F *h_qgl3_unmatched[N][M];
   TH1F *h_ptD2[N][M] ;
   TH1F *h_minW2[N][M] ;
   TH1F *h_nPart2[N][M];
   TH1F *h_ptD2_quark[N][M] ;
   TH1F *h_minW2_quark[N][M] ;
   TH1F *h_nPart2_quark[N][M];
   TH1F *h_ptD2_gluon[N][M] ;
   TH1F *h_minW2_gluon[N][M] ;
   TH1F *h_nPart2_gluon[N][M];
   TH1F *h_ptD2_undef[N][M] ;
   TH1F *h_minW2_undef[N][M] ;
   TH1F *h_nPart2_undef[N][M];

   TH1F *h_ptD2_unmatched[N][M] ;
   TH1F *h_minW2_unmatched[N][M] ;
   TH1F *h_nPart2_unmatched[N][M];
   
   TH1F *h_neu_quark[N][M];
   TH1F *h_neu_gluon[N][M];
   TH1F *h_neu_undef[N][M];
   TH1F *h_neu[N][M];

   TH1F *h_chg_quark[N][M];
   TH1F *h_chg_gluon[N][M];
   TH1F *h_chg_undef[N][M];
   TH1F *h_chg[N][M];

   char chg[100], chg_quark[100], chg_gluon[100], chg_undef[100];
   char neu[100], neu_quark[100], neu_gluon[100], neu_undef[100];

   char qgl[100], qgl_quark[100], qgl_gluon[100], qgl_undef[100], qgl_unmatched[100];
   char qgl2[100], qgl2_quark[100], qgl2_gluon[100], qgl2_undef[100], qgl2_unmatched[100];
   char qgl3[100], qgl3_quark[100], qgl3_gluon[100], qgl3_undef[100], qgl3_unmatched[100];
   char ptD[100], minW[100], nPart[100];
   char ptD_quark[100], minW_quark[100], nPart_quark[100];
   char ptD_gluon[100], minW_gluon[100], nPart_gluon[100];
   char ptD_undef[100], minW_undef[100], nPart_undef[100];
   char ptD_unmatched[100], minW_unmatched[100], nPart_unmatched[100];
   char ptD2[100], minW2[100], nPart2[100];
   char ptD2_quark[100], minW2_quark[100], nPart2_quark[100];
   char ptD2_gluon[100], minW2_gluon[100], nPart2_gluon[100];
   char ptD2_undef[100], minW2_undef[100], nPart2_undef[100];
   char ptD2_unmatched[100], minW2_unmatched[100], nPart2_unmatched[100];  
   for(a=0; a<N; a++){
     for(b=0; b<M; b++){
 
       sprintf(qgl, "h_qgl_%d_%d", a,b);
       h_qgl[a][b] = new TH1F(qgl, qgl, 25, 0, 1);
       sprintf(qgl_gluon, "h_qgl_gluon_%d_%d", a,b);
       h_qgl_gluon[a][b] = new TH1F(qgl_gluon, qgl_gluon,25, 0, 1);
       sprintf(qgl_quark, "h_qgl_quark_%d_%d", a,b);
       h_qgl_quark[a][b] = new TH1F(qgl_quark, qgl_quark,25, 0, 1);
       sprintf(qgl_undef, "h_qgl_undef_%d_%d", a,b);
       h_qgl_undef[a][b] = new TH1F(qgl_undef, qgl_undef,25, 0, 1);
       sprintf(qgl_unmatched, "h_qgl_unmatched_%d_%d", a,b);
       h_qgl_unmatched[a][b] = new TH1F(qgl_unmatched, qgl_unmatched,25, 0, 1);


       sprintf(chg, "h_chg_%d_%d", a,b);
       h_chg[a][b] = new TH1F(chg, chg, 40 , 0-.5,40-.5);
       sprintf(chg_gluon, "h_chg_gluon_%d_%d", a,b);
       h_chg_gluon[a][b] = new TH1F(chg_gluon, chg_gluon,40 , 0-.5,40-.5);
       sprintf(chg_quark, "h_chg_quark_%d_%d", a,b);
       h_chg_quark[a][b] = new TH1F(chg_quark, chg_quark,40 , 0-.5,40-.5);
       sprintf(chg_undef, "h_chg_undef_%d_%d", a,b);
       h_chg_undef[a][b] = new TH1F(chg_undef, chg_undef,40 , 0-.5,40-.5);
       //sprintf(chg_unmatched, "h_chg_unmatched_%d_%d", a,b);
       //h_chg_unmatched[a][b] = new TH1F(chg_unmatched, chg_unmatched,40 , 0-.5,40-.5);


       sprintf(neu, "h_neu_%d_%d", a,b);
       h_neu[a][b] = new TH1F(neu, neu, 40 , 0-.5,40-.5);
       sprintf(neu_gluon, "h_neu_gluon_%d_%d", a,b);
       h_neu_gluon[a][b] = new TH1F(neu_gluon, neu_gluon,40 , 0-.5,40-.5);
       sprintf(neu_quark, "h_neu_quark_%d_%d", a,b);
       h_neu_quark[a][b] = new TH1F(neu_quark, neu_quark,40 , 0-.5,40-.5);
       sprintf(neu_undef, "h_neu_undef_%d_%d", a,b);
       h_neu_undef[a][b] = new TH1F(neu_undef, neu_undef,40 , 0-.5,40-.5);
       //       sprintf(neu_unmatched, "h_neu_unmatched_%d_%d", a,b);
       //h_neu_unmatched[a][b] = new TH1F(neu_unmatched, neu_unmatched,40 , 0-.5,40-.5);


       sprintf(qgl2, "h_qgl2_%d_%d", a,b);
       h_qgl2[a][b] = new TH1F(qgl2, qgl2, 25, 0, 1);
       sprintf(qgl2_gluon, "h_qgl2_gluon_%d_%d", a,b);
       h_qgl2_gluon[a][b] = new TH1F(qgl2_gluon, qgl2_gluon,25, 0, 1);
       sprintf(qgl2_quark, "h_qgl2_quark_%d_%d", a,b);
       h_qgl2_quark[a][b] = new TH1F(qgl2_quark, qgl2_quark,25, 0, 1);
       sprintf(qgl2_undef, "h_qgl2_undef_%d_%d", a,b);
       h_qgl2_undef[a][b] = new TH1F(qgl2_undef, qgl2_undef,25, 0, 1);
       sprintf(qgl2_unmatched, "h_qgl2_unmatched_%d_%d", a,b);
       h_qgl2_unmatched[a][b] = new TH1F(qgl2_unmatched, qgl2_unmatched,25, 0, 1);

       sprintf(qgl3, "h_qgl3_%d_%d", a,b);
       h_qgl3[a][b] = new TH1F(qgl3, qgl3, 25, 0, 1);
       sprintf(qgl3_gluon, "h_qgl3_gluon_%d_%d", a,b);
       h_qgl3_gluon[a][b] = new TH1F(qgl3_gluon, qgl3_gluon,25, 0, 1);
       sprintf(qgl3_quark, "h_qgl3_quark_%d_%d", a,b);
       h_qgl3_quark[a][b] = new TH1F(qgl3_quark, qgl3_quark,25, 0, 1);
       sprintf(qgl3_undef, "h_qgl3_undef_%d_%d", a,b);
       h_qgl3_undef[a][b] = new TH1F(qgl3_undef, qgl3_undef,25, 0, 1);
       sprintf(qgl3_unmatched, "h_qgl3_unmatched_%d_%d", a,b);
       h_qgl3_unmatched[a][b] = new TH1F(qgl3_unmatched, qgl3_unmatched,25, 0, 1);
       
       sprintf(ptD, "h_ptD_%d_%d", a,b);
       h_ptD[a][b] = new TH1F(ptD, ptD,50,0,1);
       sprintf(minW, "h_minW_%d_%d", a,b);
       h_minW[a][b]  = new TH1F(minW, minW,50,0,7);
       sprintf(nPart, "h_nPart_%d_%d", a,b);
       h_nPart[a][b] = new TH1F(nPart, nPart,50 , 0-.5,50-.5);

       sprintf(ptD_quark, "h_ptD_quark_%d_%d", a,b);
       h_ptD_quark[a][b] = new TH1F(ptD_quark, ptD_quark,50,0,1);
       sprintf(minW_quark, "h_minW_quark_%d_%d", a,b);
       h_minW_quark[a][b]  = new TH1F(minW_quark, minW_quark,50,0,7);
       sprintf(nPart_quark, "h_nPart_quark_%d_%d", a,b);
       h_nPart_quark[a][b] = new TH1F(nPart_quark, nPart_quark,50 , 0-.5,50-.5);

       sprintf(ptD_gluon, "h_ptD_gluon_%d_%d", a,b);
       h_ptD_gluon[a][b] = new TH1F(ptD_gluon, ptD_gluon,50,0,1);
       sprintf(minW_gluon, "h_minW_gluon_%d_%d", a,b);
       h_minW_gluon[a][b]  = new TH1F(minW_gluon, minW_gluon,50,0,7);
       sprintf(nPart_gluon, "h_nPart_gluon_%d_%d", a,b);
       h_nPart_gluon[a][b] = new TH1F(nPart_gluon, nPart_gluon,50 , 0-.5,50-.5);

       sprintf(ptD_undef, "h_ptD_undef_%d_%d", a,b);
       h_ptD_undef[a][b] = new TH1F(ptD_undef, ptD_undef,50,0,1);
       sprintf(minW_undef, "h_minW_undef_%d_%d", a,b);
       h_minW_undef[a][b]  = new TH1F(minW_undef, minW_undef,50,0,7);
       sprintf(nPart_undef, "h_nPart_undef_%d_%d", a,b);
       h_nPart_undef[a][b] = new TH1F(nPart_undef, nPart_undef,50 , 0-.5,50-.5);

       sprintf(ptD_unmatched, "h_ptD_unmatched_%d_%d", a,b);
       h_ptD_unmatched[a][b] = new TH1F(ptD_unmatched, ptD_unmatched,50,0,1);
       sprintf(minW_unmatched, "h_minW_unmatched_%d_%d", a,b);
       h_minW_unmatched[a][b]  = new TH1F(minW_unmatched, minW_unmatched,50,0,7);
       sprintf(nPart_unmatched, "h_nPart_unmatched_%d_%d", a,b);
       h_nPart_unmatched[a][b] = new TH1F(nPart_unmatched, nPart_unmatched,50 , 0-.5,50-.5);

       sprintf(ptD2, "h_ptD2_%d_%d", a,b);
       h_ptD2[a][b] = new TH1F(ptD2, ptD2,50,0,1);
       sprintf(minW2, "h_minW2_%d_%d", a,b);
       h_minW2[a][b]  = new TH1F(minW2, minW2,50,0,7);
       sprintf(nPart2, "h_nPart2_%d_%d", a,b);
       h_nPart2[a][b] = new TH1F(nPart2, nPart2,50 , 0-.5,50-.5);

       sprintf(ptD2_quark, "h_ptD2_quark_%d_%d", a,b);
       h_ptD2_quark[a][b] = new TH1F(ptD2_quark, ptD2_quark,50,0,1);
       sprintf(minW2_quark, "h_minW2_quark_%d_%d", a,b);
       h_minW2_quark[a][b]  = new TH1F(minW2_quark, minW2_quark,50,0,7);
       sprintf(nPart2_quark, "h_nPart2_quark_%d_%d", a,b);
       h_nPart2_quark[a][b] = new TH1F(nPart2_quark, nPart2_quark,50 , 0-.5,50-.5);

       sprintf(ptD2_gluon, "h_ptD2_gluon_%d_%d", a,b);
       h_ptD2_gluon[a][b] = new TH1F(ptD2_gluon, ptD2_gluon,50,0,1);
       sprintf(minW2_gluon, "h_minW2_gluon_%d_%d", a,b);
       h_minW2_gluon[a][b]  = new TH1F(minW2_gluon, minW2_gluon,50,0,7);
       sprintf(nPart2_gluon, "h_nPart2_gluon_%d_%d", a,b);
       h_nPart2_gluon[a][b] = new TH1F(nPart2_gluon, nPart2_gluon,50 , 0-.5,50-.5);

       sprintf(ptD2_undef, "h_ptD2_undef_%d_%d", a,b);
       h_ptD2_undef[a][b] = new TH1F(ptD2_undef, ptD2_undef,50,0,1);
       sprintf(minW2_undef, "h_minW2_undef_%d_%d", a,b);
       h_minW2_undef[a][b]  = new TH1F(minW2_undef, minW2_undef,50,0,7);
       sprintf(nPart2_undef, "h_nPart2_undef_%d_%d", a,b);
       h_nPart2_undef[a][b] = new TH1F(nPart2_undef, nPart2_undef,50 , 0-.5,50-.5);
       
       sprintf(ptD2_unmatched, "h_ptD2_unmatched_%d_%d", a,b);
       h_ptD2_unmatched[a][b] = new TH1F(ptD2_unmatched, ptD2_unmatched,50,0,1);
       sprintf(minW2_unmatched, "h_minW2_unmatched_%d_%d", a,b);
       h_minW2_unmatched[a][b]  = new TH1F(minW2_unmatched, minW2_unmatched,50,0,7);
       sprintf(nPart2_unmatched, "h_nPart2_unmatched_%d_%d", a,b);
       h_nPart2_unmatched[a][b] = new TH1F(nPart2_unmatched, nPart2_unmatched,50 , 0-.5,50-.5);
     }
   }

   TH1F *h_rho = new TH1F("rho", "rho", 18, 0, 18);
   TH1F *h_qgl_all = new TH1F("qgl_all", "qgl_all", 25, 0, 1);
   TH1F *h_qgl_undef_all = new TH1F("qgl_undef_all", "qgl_undef_all", 25, 0, 1);
   TH1F *h_qgl_unmatched_all = new TH1F("qgl_unmatched_all", "qgl_unmatched_all", 25, 0, 1);
   TH1F *h_qgl_gluon_all = new TH1F("qgl_gluon_all", "qgl_gluon_all", 25, 0, 1);
   TH1F *h_qgl_quark_all = new TH1F("qgl_quark_all", "qgl_quark_all", 25, 0, 1);

   TH1F *h_qgl2_all = new TH1F("qgl2_all", "qgl2_all", 25, 0, 1);
   TH1F *h_qgl2_undef_all = new TH1F("qgl2_undef_all", "qgl2_undef_all", 25, 0, 1);
   TH1F *h_qgl2_unmatched_all = new TH1F("qgl2_unmatched_all", "qgl2_unmatched_all", 25, 0, 1);
   TH1F *h_qgl2_gluon_all = new TH1F("qgl2_gluon_all", "qgl2_gluon_all", 25, 0, 1);
   TH1F *h_qgl2_quark_all = new TH1F("qgl2_quark_all", "qgl2_quark_all", 25, 0, 1);

   TH1F *h_qgl3_all = new TH1F("qgl3_all", "qgl3_all", 25, 0, 1);
   TH1F *h_qgl3_undef_all = new TH1F("qgl3_undef_all", "qgl3_undef_all", 25, 0, 1);
   TH1F *h_qgl3_unmatched_all = new TH1F("qgl3_unmatched_all", "qgl3_unmatched_all", 25, 0, 1);
   TH1F *h_qgl3_gluon_all = new TH1F("qgl3_gluon_all", "qgl3_gluon_all", 25, 0, 1);
   TH1F *h_qgl3_quark_all = new TH1F("qgl3_quark_all", "qgl3_quark_all", 25, 0, 1);

   TH1F *h_nPart_all = new TH1F("nPart_all", "nPart_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart_undef_all = new TH1F("nPart_undef_all", "nPart_undef_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart_unmatched_all = new TH1F("nPart_unmatched_all", "nPart_unmatched_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart_gluon_all = new TH1F("nPart_gluon_all", "nPart_gluon_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart_quark_all = new TH1F("nPart_quark_all", "nPart_quark_all", 50 , 0-.5,50-.5);   

   TH1F *h_ptD_all = new TH1F("ptD_all", "ptD_all", 25, 0, 1);
   TH1F *h_ptD_undef_all = new TH1F("ptD_undef_all", "ptD_undef_all", 25, 0, 1);
   TH1F *h_ptD_unmatched_all = new TH1F("ptD_unmatched_all", "ptD_unmatched_all", 25, 0, 1);
   TH1F *h_ptD_gluon_all = new TH1F("ptD_gluon_all", "ptD_gluon_all", 25, 0, 1);
   TH1F *h_ptD_quark_all = new TH1F("ptD_quark_all", "ptD_quark_all", 25, 0, 1);

   TH1F *h_minW_all = new TH1F("minW_all", "minW_all", 50, 0, 7);
   TH1F *h_minW_unmatched_all = new TH1F("minW_unmatched_all", "minW_unmatched_all", 50, 0, 7);
   TH1F *h_minW_undef_all = new TH1F("minW_undef_all", "minW_undef_all", 50, 0, 7);
   TH1F *h_minW_gluon_all = new TH1F("minW_gluon_all", "minW_gluon_all", 50, 0, 7);
   TH1F *h_minW_quark_all = new TH1F("minW_quark_all", "minW_quark_all", 50, 0, 7);
   
   TH1F *h_nPart2_all = new TH1F("nPart2_all", "nPart2_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart2_undef_all = new TH1F("nPart2_undef_all", "nPart2_undef_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart2_unmatched_all = new TH1F("nPart2_unmatched_all", "nPart2_unmatched_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart2_gluon_all = new TH1F("nPart2_gluon_all", "nPart2_gluon_all", 50 , 0-.5,50-.5);
   TH1F *h_nPart2_quark_all = new TH1F("nPart2_quark_all", "nPart2_quark_all", 50 , 0-.5,50-.5);   

   TH1F *h_ptD2_all = new TH1F("ptD2_all", "ptD2_all", 25, 0, 1);
   TH1F *h_ptD2_undef_all = new TH1F("ptD2_undef_all", "ptD2_undef_all", 25, 0, 1);
   TH1F *h_ptD2_unmatched_all = new TH1F("ptD2_unmatched_all", "ptD2_unmatched_all", 25, 0, 1);
   TH1F *h_ptD2_gluon_all = new TH1F("ptD2_gluon_all", "ptD2_gluon_all", 25, 0, 1);
   TH1F *h_ptD2_quark_all = new TH1F("ptD2_quark_all", "ptD2_quark_all", 25, 0, 1);

   TH1F *h_minW2_all = new TH1F("minW2_all", "minW2_all", 50, 0, 7);
   TH1F *h_minW2_undef_all = new TH1F("minW2_undef_all", "minW2_undef_all", 50, 0, 7);
   TH1F *h_minW2_unmatched_all = new TH1F("minW2_unmatched_all", "minW2_unmatched_all", 50, 0, 7);
   TH1F *h_minW2_gluon_all = new TH1F("minW2_gluon_all", "minW2_gluon_all", 50, 0, 7);
   TH1F *h_minW2_quark_all = new TH1F("minW2_quark_all", "minW2_quark_all", 50, 0, 7);
   
   TH1F *h_cutFlow = new TH1F("h_cutFlow", "cutFlow", 7, -0.5, 6.5);
   TH1F *h_ptbalance = new TH1F("h_ptbalance", "ptbalance", 100, 0., 2.);
   TH1F *h_Zpt = new TH1F("h_Zpt", "Zpt", 100, 0., 500.);
   TH1F *h_Zmass = new TH1F("h_Zmass", "Zmass", 100, 0., 150.);
   TH1F *h_genZpt = new TH1F("h_genZpt", "genZpt", 100, 0., 500.);
   TH1F *h_genZmass = new TH1F("h_genZmass", "genZmass", 100, 0., 150.);
   TH1F *h_leadmuonPt = new TH1F("h_leadmuonPt", "leadmuonPt", 100, 0., 500.);
   TH1F *h_subleadmuonPt = new TH1F("h_subleadmuonPt", "subleadmuonPt", 100, 0., 500.);
   TH1F *h_leadmuonEta = new TH1F("h_leadmuonEta", "leadmuonEta", 100, -5.2, 5.2);
   TH1F *h_subleadmuonEta = new TH1F("h_subleadmuonEta", "subleadmuonEta", 100, -5.2, 5.2);
   TH1F *h_leadmuonPhi = new TH1F("h_leadmuonPhi", "leadmuonPhi", 100, -3.14, 3.14);
   TH1F *h_subleadmuonPhi = new TH1F("h_subleadmuonPhi", "subleadmuonPhi", 100, -3.14, 3.14);
   TH1F *h_leadjetPt = new TH1F("h_leadjetPt", "leadjetPt", 100, 0., 500.);
   TH1F *h_subleadjetPt = new TH1F("h_subleadjetPt", "subleadjetPt", 100, 0., 500.);
   TH1F *h_leadjetEta = new TH1F("h_leadjetEta", "leadjetEta", 100, -5.2, 5.2);
   TH1F *h_subleadjetEta = new TH1F("h_subleadjetEta", "subleadjetEta", 100, -5.2, 5.2);
   TH1F *h_leadjetPhi = new TH1F("h_leadjetPhi", "leadjetPhi", 100, -3.14, 3.14);
   TH1F *h_subleadjetPhi = new TH1F("h_subleadjetPhi", "subleadjetPhi", 100, -3.14, 3.14);
   TH1F *h_deltaPhi = new TH1F("h_deltaPhi", "deltaPhi", 100, 0, 6.28);

   QGLikelihoodCalculator localQG("/mnt/t3nfs01/data01/shome/grauco/JetMET_z/CMSSW_7_6_3/src/ttDM/newTTDManalysis/pdfQG_AK4chs_13TeV_v2_PU20bx25_QCD_AllPtBins.root");
   
   for(Int_t i=0; i<nEvents; i++ )
     {
       
	     
       if(i%100000==1 ){
	 cout<<"Running on event: "<<i<<endl;
       }
       chain.GetEntry(i);
       
       float ptRatiobins[10]={30,40,50,60,80,100,120,250,500,800};
       float etaRatiobins[5]={0.0,2.0,2.5,3.0,4.7};

       std::vector<TLorentzVector> jets;
       struct TightJets{
	 TLorentzVector vect;
	 float csv;
	 float deltaphi;
	 float qgl;
	 float qgl2;
	 float qgl3;
	 float ptD;
	 float nPart;
	 float minW;
	 float ptD2;
	 float nPart2;
	 float minW2;
	 float chg;
	 float neu;
	 int flavour;
       };
       std::vector<TightJets> SelectedJets;
       //cout << "2" << endl;
       if(passTrig>0.){
	 //if(1>0.){
	 n_trig+= w;
	 //cout << "3" << endl;
	 if(muonSize>1){                                                                                  
	   bool twoMuons = (muonSize>1 && muonpt[0]>20 && muonpt[1]>20 && (muoncharge[0]*muoncharge[1])<0); 
	   //cout << "4" << endl;
	   TLorentzVector muon_lead;
	   TLorentzVector muon_sublead;
	   muon_lead.SetPtEtaPhiE(muonpt[0], muoneta[0],  muonphi[0], muone[0]);
	   muon_sublead.SetPtEtaPhiE(muonpt[1], muoneta[1] , muonphi[1], muone[1]);
	   //cout << "5" << endl;
	   TLorentzVector Z;
	   Z = (muon_lead+muon_sublead);
	   //cout << "6" << endl;
	   bool isZ = fabs(Z.M()-91)<20;                               
	   bool areBackToBack = 0;
	   bool secondjet = 0;
	   //cout << "7" << endl;
	   if(isZ==1  && jetSize>=1){                                              
	     TLorentzVector jet;
	     jet.SetPtEtaPhiE(jetpt[0], jeteta[0], jetphi[0], jete[0]);
	     jets.push_back(jet);
	     //cout << "8" << endl;
	     float deltaPhi = Z.DeltaPhi(jet);
	     areBackToBack= deltaPhi>2.1;                                                         	     
	     secondjet = 0;
	     if(jetSize>=2 && jetpt[1]<(0.3*Z.Pt())) secondjet=1;
	     if(jetSize==1) secondjet=1;
	     if(secondjet==1  && areBackToBack==1){

	       TightJets b;
	       b.vect = jet;
	       b.csv = jetcsv[0];
	       b.deltaphi = Z.DeltaPhi(jet);
	       b.qgl=jetqgl[0];
	       b.qgl2=localQG.computeQGLikelihood(jet.Pt(), jet.Eta(), rho, {(float) pileupJetIdnParticles[0], pileupJetIdptD[0], -log(pileupJetIdminW[0])});
	       b.qgl3=localQG.computeQGLikelihood(jet.Pt(), jet.Eta(), rho, {(float) jetmult[0], jetptd[0], -log(jetaxis2[0])});
	       b.minW=pileupJetIdminW[0];
	       b.ptD=pileupJetIdptD[0];
	       b.nPart = pileupJetIdnParticles[0];
	       b.minW2=jetaxis2[0];
	       b.ptD2=jetptd[0];
	       b.nPart2 = jetmult[0];
	       b.chg=pileupJetIdnCharged[0];
	       b.neu=pileupJetIdnNeutrals[0];
	       b.flavour=jetflavour[0];
	       SelectedJets.push_back(b);
	     }
	   }
	     
	     if(twoMuons==1){
	       n_twomuons+=w;
	       if(isZ==1){
		 n_isZ+=w;
		 if(jetSize>0){
		   n_jet+=w;
		 if(areBackToBack>0){
		   n_isBackToBack+=w;
		   if(secondjet==1){
		   n_Leadjet+=w;

		   h_rho->Fill(rho);
		   h_Zpt->Fill(Z.Pt());
		   h_Zmass->Fill(Z.M());
		   h_leadmuonPt->Fill(muon_lead.Pt());
		   h_subleadmuonPt->Fill(muon_sublead.Pt());
		   h_leadmuonEta->Fill(muon_lead.Eta());
		   h_leadmuonPhi->Fill(muon_lead.Phi());
		   h_subleadmuonEta->Fill(muon_sublead.Eta());
		   h_subleadmuonPhi->Fill(muon_sublead.Phi());
		   h_deltaPhi->Fill((SelectedJets[0].deltaphi));		     
		   h_leadjetPt->Fill((SelectedJets[0].vect).Pt());
		   h_subleadjetPt->Fill((SelectedJets[1].vect).Pt());
		   h_leadjetEta->Fill((SelectedJets[0].vect).Eta());
		   h_leadjetPhi->Fill((SelectedJets[0].vect).Phi());
		   h_subleadjetEta->Fill((SelectedJets[1].vect).Eta());
		   h_subleadjetPhi->Fill((SelectedJets[0].vect).Phi());

		   h_qgl_all->Fill(SelectedJets[0].qgl);
		   h_qgl2_all->Fill(SelectedJets[0].qgl2);
		   h_qgl3_all->Fill(SelectedJets[0].qgl3);
		   h_nPart_all->Fill(SelectedJets[0].nPart);
		   h_ptD_all->Fill(SelectedJets[0].ptD);
		   h_minW_all->Fill(-log(SelectedJets[0].minW));
		   h_nPart2_all->Fill(SelectedJets[0].nPart2);
		   h_ptD2_all->Fill(SelectedJets[0].ptD2);
		   h_minW2_all->Fill(-log(SelectedJets[0].minW2));
		  
		   for(int i=0;i<9;i++){
		     for(int j=0;j<5;j++){
		       if(abs((SelectedJets[0].vect).Eta())>etaRatiobins[j] && abs((SelectedJets[0].vect).Eta())<etaRatiobins[j+1] && Z.Pt()>ptRatiobins[i] && Z.Pt()<ptRatiobins[i+1]){
		
			 h_chg[i][j]->Fill(SelectedJets[0].chg);
			 h_neu[i][j]->Fill(SelectedJets[0].neu);
			 h_ptD2[i][j]->Fill(SelectedJets[0].ptD2);
			 h_nPart2[i][j]->Fill(SelectedJets[0].nPart2);
			 h_minW2[i][j]->Fill(-log(SelectedJets[0].minW2));
			 h_ptD[i][j]->Fill(SelectedJets[0].ptD);
			 h_nPart[i][j]->Fill(SelectedJets[0].nPart);
			 h_minW[i][j]->Fill(-log(SelectedJets[0].minW));
			 h_qgl[i][j]->Fill(SelectedJets[0].qgl);
			 h_qgl2[i][j]->Fill(SelectedJets[0].qgl2);
			 h_qgl3[i][j]->Fill(SelectedJets[0].qgl3);
		       } 
		     } 
		   }
		   
		   /*float deltaR_jetallpartons=-999;
		   float mindeltaR_jetallpartons=999;
		   int genindex=999;
		   
		   for(int i=0; i<genPartSize; i++){
		     if(genpartpt[i]>0.1){
		       if(fabs(genpartid[i])==23){
			 h_genZpt->Fill(genpartpt[i]);
			 h_genZmass->Fill(genpartmass[i]);
		       }             		       
		       if(genpartstatus[i]<=23.1 && genpartstatus[i]>=22.9){
			 TLorentzVector genParticle;
			 genParticle.SetPtEtaPhiE(genpartpt[i], genparteta[i], genpartphi[i], genparte[i]);
			 deltaR_jetallpartons=deltaR((SelectedJets[0].vect).Eta(),(SelectedJets[0].vect).Phi(),genparteta[i],genpartphi[i]);
			 if(deltaR_jetallpartons < mindeltaR_jetallpartons){                 
			   genindex=genpartid[i];	
			   mindeltaR_jetallpartons = deltaR_jetallpartons;
			 }
		       }
		     }
		   }

		   if(mindeltaR_jetallpartons<0.3){                                                            
		     if((genindex<=5 && genindex>=-5)){
		       h_qgl_quark_all->Fill(SelectedJets[0].qgl);
		       h_qgl2_quark_all->Fill(SelectedJets[0].qgl2);
		       h_qgl3_quark_all->Fill(SelectedJets[0].qgl3);
		       h_nPart_quark_all->Fill(SelectedJets[0].nPart);
		       h_ptD_quark_all->Fill(SelectedJets[0].ptD);
		       h_minW_quark_all->Fill(-log(SelectedJets[0].minW));
		       h_nPart2_quark_all->Fill(SelectedJets[0].nPart2);
		       h_ptD2_quark_all->Fill(SelectedJets[0].ptD2);
		       h_minW2_quark_all->Fill(-log(SelectedJets[0].minW2));

		     }
		     else if(genindex<=21.1 && genindex>=20.9){
			 h_qgl_gluon_all->Fill(SelectedJets[0].qgl);
			 h_qgl2_gluon_all->Fill(SelectedJets[0].qgl2);
			 h_qgl3_gluon_all->Fill(SelectedJets[0].qgl3);
			 h_nPart_gluon_all->Fill(SelectedJets[0].nPart);
			 h_ptD_gluon_all->Fill(SelectedJets[0].ptD);
			 h_minW_gluon_all->Fill(-log(SelectedJets[0].minW));
			 h_nPart2_gluon_all->Fill(SelectedJets[0].nPart2);
			 h_ptD2_gluon_all->Fill(SelectedJets[0].ptD2);
			 h_minW2_gluon_all->Fill(-log(SelectedJets[0].minW2));
		     }
		     else{
		       h_qgl_undef_all->Fill(SelectedJets[0].qgl);
		       h_qgl2_undef_all->Fill(SelectedJets[0].qgl2);
		       h_qgl3_undef_all->Fill(SelectedJets[0].qgl3);
		       h_nPart_undef_all->Fill(SelectedJets[0].nPart);
		       h_ptD_undef_all->Fill(SelectedJets[0].ptD);
		       h_minW_undef_all->Fill(-log(SelectedJets[0].minW));
		       h_nPart2_undef_all->Fill(SelectedJets[0].nPart2);
		       h_ptD2_undef_all->Fill(SelectedJets[0].ptD2);
		       h_minW2_undef_all->Fill(-log(SelectedJets[0].minW2));
		       
		     }
		   }
		   else{
		     
		     if((SelectedJets[0].jetflavour<=5 && SelectedJets[0].jetflavour>=-5 && SelectedJets[0].jetflavour!=0)){
		       h_qgl_quark_all->Fill(SelectedJets[0].qgl);
		       h_qgl2_quark_all->Fill(SelectedJets[0].qgl2);
		       h_qgl3_quark_all->Fill(SelectedJets[0].qgl3);
		       h_nPart_quark_all->Fill(SelectedJets[0].nPart);
		       h_ptD_quark_all->Fill(SelectedJets[0].ptD);
		       h_minW_quark_all->Fill(-log(SelectedJets[0].minW));
		       h_nPart2_quark_all->Fill(SelectedJets[0].nPart2);
		       h_ptD2_quark_all->Fill(SelectedJets[0].ptD2);
		       h_minW2_quark_all->Fill(-log(SelectedJets[0].minW2));
		     }

		     else if((SelectedJets[0].jetflavour<=21.1 && SelectedJets[0].jetflavour>=20.9)){
		        h_qgl_gluon_all->Fill(SelectedJets[0].qgl);
			h_qgl2_gluon_all->Fill(SelectedJets[0].qgl2);
			h_qgl3_gluon_all->Fill(SelectedJets[0].qgl3);
			h_nPart_gluon_all->Fill(SelectedJets[0].nPart);
			h_ptD_gluon_all->Fill(SelectedJets[0].ptD);
			h_minW_gluon_all->Fill(-log(SelectedJets[0].minW));
			h_nPart2_gluon_all->Fill(SelectedJets[0].nPart2);
			h_ptD2_gluon_all->Fill(SelectedJets[0].ptD2);
			h_minW2_gluon_all->Fill(-log(SelectedJets[0].minW2));
		     }
		     else if((SelectedJets[0].jetflavour==0)){
		       h_qgl_undef_all->Fill(SelectedJets[0].qgl);
		       h_qgl2_undef_all->Fill(SelectedJets[0].qgl2);
		       h_qgl3_undef_all->Fill(SelectedJets[0].qgl3);
		       h_nPart_undef_all->Fill(SelectedJets[0].nPart);
		       h_ptD_undef_all->Fill(SelectedJets[0].ptD);
		       h_minW_undef_all->Fill(-log(SelectedJets[0].minW));
		       h_nPart2_undef_all->Fill(SelectedJets[0].nPart2);
		       h_ptD2_undef_all->Fill(SelectedJets[0].ptD2);
		       h_minW2_undef_all->Fill(-log(SelectedJets[0].minW2));
		     }
		     
		     h_qgl_undef_all->Fill(SelectedJets[0].qgl);
		       h_qgl2_undef_all->Fill(SelectedJets[0].qgl2);
		       h_qgl3_undef_all->Fill(SelectedJets[0].qgl3);
		       h_nPart_undef_all->Fill(SelectedJets[0].nPart);
		       h_ptD_undef_all->Fill(SelectedJets[0].ptD);
		       h_minW_undef_all->Fill(-log(SelectedJets[0].minW));
		       h_nPart2_undef_all->Fill(SelectedJets[0].nPart2);
		       h_ptD2_undef_all->Fill(SelectedJets[0].ptD2);
		       h_minW2_undef_all->Fill(-log(SelectedJets[0].minW2));
		       
		   }
		   */
		   /*for(int i=0;i<9;i++){
		     for(int j=0;j<5;j++){
		       if(abs((SelectedJets[0].vect).Eta())>etaRatiobins[j] && abs((SelectedJets[0].vect).Eta())<etaRatiobins[j+1] && Z.Pt()>ptRatiobins[i] && Z.Pt()<ptRatiobins[i+1]){                                     
			 
			 if(mindeltaR_jetallpartons<0.3){                                                            
			   //  if((SelectedJets[0].flavour<=5 && SelectedJets[0].flavour>=-5 && SelectedJets[0].flavour!=0)){
			   if((genindex<=5 && genindex>=-5)){
			     //  if((SelectedJets[0].jetflavour<=5 && SelectedJets[0].jetflavour>=-5 && SelectedJets[0].jetflavour!=0)){
			     h_chg_quark[i][j]->Fill(SelectedJets[0].chg);
			     h_neu_quark[i][j]->Fill(SelectedJets[0].neu);
			     h_ptD_quark[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_quark[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW2_quark[i][j]->Fill(-log(SelectedJets[0].minW2));
			     h_ptD2_quark[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_quark[i][j]->Fill(SelectedJets[0].nPart2);
			     h_minW_quark[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_qgl_quark[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_quark[i][j]->Fill(SelectedJets[0].qgl2);
			     h_qgl3_quark[i][j]->Fill(SelectedJets[0].qgl3);
			   }
			   //else if(SelectedJets[0].flavour<=21.2 && SelectedJets[0].flavour>=20.9){
			   else if(genindex<=21.1 && genindex>=20.9){
			     //else if((SelectedJets[0].flavour<=21.1 && SelectedJets[0].flavour>=20.9)){
			     h_chg_gluon[i][j]->Fill(SelectedJets[0].chg);
                             h_neu_gluon[i][j]->Fill(SelectedJets[0].neu);
			     h_minW2_gluon[i][j]->Fill(-log(SelectedJets[0].minW2));
			     h_ptD2_gluon[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_gluon[i][j]->Fill(SelectedJets[0].nPart2);
			     h_ptD_gluon[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_gluon[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW_gluon[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_qgl_gluon[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_gluon[i][j]->Fill(SelectedJets[0].qgl2);
			     h_qgl3_gluon[i][j]->Fill(SelectedJets[0].qgl3);
			   }
			   else{
			     h_ptD_undef[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_undef[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW_undef[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_ptD2_undef[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_undef[i][j]->Fill(SelectedJets[0].nPart2);
			     h_minW2_undef[i][j]->Fill(-log(SelectedJets[0].minW2));
			     h_qgl_undef[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_undef[i][j]->Fill(SelectedJets[0].qgl2);
			     h_qgl3_undef[i][j]->Fill(SelectedJets[0].qgl3);
			   }
			 }
			   else{
			     if((SelectedJets[0].flavour<=5 && SelectedJets[0].flavour>=-5 && SelectedJets[0].flavour!=0)){

			     h_chg_quark[i][j]->Fill(SelectedJets[0].chg);
			     h_neu_quark[i][j]->Fill(SelectedJets[0].neu);
			     h_ptD_quark[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_quark[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW_quark[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_ptD2_quark[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_quark[i][j]->Fill(SelectedJets[0].nPart2);
			     h_minW2_quark[i][j]->Fill(-log(SelectedJets[0].minW2)); 
			     h_qgl_quark[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_quark[i][j]->Fill(SelectedJets[0].qgl2);
			     h_qgl3_quark[i][j]->Fill(SelectedJets[0].qgl3);
			   }
			   else if((SelectedJets[0].flavour<=21.1 && SelectedJets[0].flavour>=20.9)){
			     h_chg_gluon[i][j]->Fill(SelectedJets[0].chg);
			     h_neu_gluon[i][j]->Fill(SelectedJets[0].neu);
			     h_ptD_gluon[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_gluon[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW_gluon[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_ptD2_gluon[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_gluon[i][j]->Fill(SelectedJets[0].nPart2);
			     h_minW2_gluon[i][j]->Fill(-log(SelectedJets[0].minW2)); 
			     h_qgl_gluon[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_gluon[i][j]->Fill(SelectedJets[0].qgl2);
			     h_qgl3_gluon[i][j]->Fill(SelectedJets[0].qgl3);
			   }
			   else if(SelectedJets[0].flavour==0){
			     h_chg_undef[i][j]->Fill(SelectedJets[0].chg);
			     h_neu_undef[i][j]->Fill(SelectedJets[0].neu);
			     h_ptD_undef[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_undef[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW_undef[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_ptD2_undef[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_undef[i][j]->Fill(SelectedJets[0].nPart2);
			     h_minW2_undef[i][j]->Fill(-log(SelectedJets[0].minW2)); 
			     h_qgl_undef[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_undef[i][j]->Fill(SelectedJets[0].qgl2);
			     h_qgl3_undef[i][j]->Fill(SelectedJets[0].qgl3);
			     }
			   h_chg_undef[i][j]->Fill(SelectedJets[0].chg);
			     h_neu_undef[i][j]->Fill(SelectedJets[0].neu);
			     h_ptD_undef[i][j]->Fill(SelectedJets[0].ptD);
			     h_nPart_undef[i][j]->Fill(SelectedJets[0].nPart);
			     h_minW_undef[i][j]->Fill(-log(SelectedJets[0].minW));
			     h_ptD2_undef[i][j]->Fill(SelectedJets[0].ptD2);
			     h_nPart2_undef[i][j]->Fill(SelectedJets[0].nPart2);
			     h_minW2_undef[i][j]->Fill(-log(SelectedJets[0].minW2)); 
			     h_qgl_undef[i][j]->Fill(SelectedJets[0].qgl);
			     h_qgl2_undef[i][j]->Fill(SelectedJets[0].qgl2);
		           h_qgl3_undef[i][j]->Fill(SelectedJets[0].qgl3);
			   //}
			   	   }
			   }
			   }
		   }*/
		   }
		 }
		 }
	       }
	     }
	 }	 
       }
     }
     
   //   TString outfile = "/scratch/grauco/jetMet_zjets/"+sample + "_" +cat+"_"+channel+".root";
   TString outfile = "res_v3/"+sample + "_" +cat+"_"+channel+"_status23.root";
   TFile fout(outfile, "recreate");

   h_rho->Write();
   h_ptbalance->Write();
   h_Zpt->Write();
   h_Zmass->Write();
   h_genZpt->Write();
   h_genZmass->Write();
   h_leadmuonPt->Write();
   h_subleadmuonPt->Write();
   h_leadmuonEta->Write();
   h_leadmuonPhi->Write();
   h_subleadmuonEta->Write();
   h_subleadmuonPhi->Write();
   h_leadjetPt->Write();
   h_subleadjetPt->Write();
   h_leadjetEta->Write();
   h_leadjetPhi->Write();
   h_subleadjetEta->Write();
   h_subleadjetPhi->Write();

   h_deltaPhi->Write();

   h_qgl_all->Write();
   h_qgl_gluon_all->Write();
   h_qgl_quark_all->Write();
   h_qgl_undef_all->Write();
    h_qgl_unmatched_all->Write();
   
   h_qgl2_all->Write();
   h_qgl2_gluon_all->Write();
   h_qgl2_quark_all->Write();
   h_qgl2_undef_all->Write();
      h_qgl2_unmatched_all->Write();

   h_qgl3_all->Write();
   h_qgl3_gluon_all->Write();
   h_qgl3_quark_all->Write();
   h_qgl3_undef_all->Write();
      h_qgl3_unmatched_all->Write();

   h_ptD_all->Write();
   h_ptD_gluon_all->Write();
   h_ptD_quark_all->Write();
   h_ptD_undef_all->Write();
      h_ptD_unmatched_all->Write();

   h_minW_all->Write();
   h_minW_gluon_all->Write();
   h_minW_quark_all->Write();
   h_minW_undef_all->Write();
      h_minW_unmatched_all->Write();
   h_nPart_all->Write();
   h_nPart_gluon_all->Write();
   h_nPart_quark_all->Write();
   h_nPart_undef_all->Write();
    h_nPart_unmatched_all->Write();

      h_ptD2_all->Write();
   h_ptD2_gluon_all->Write();
   h_ptD2_quark_all->Write();
   h_ptD2_undef_all->Write();

   h_minW2_all->Write();
   h_minW2_gluon_all->Write();
   h_minW2_quark_all->Write();
   h_minW2_undef_all->Write();
   h_nPart2_all->Write();
   h_nPart2_gluon_all->Write();
   h_nPart2_quark_all->Write();
   h_nPart2_undef_all->Write();

   h_ptD2_unmatched_all->Write();
   h_nPart2_unmatched_all->Write();
   h_minW2_unmatched_all->Write();
   

   for(a=0; a<N; a++){
     for(b=0; b<M; b++){


       h_qgl_unmatched[a][b]->Write();
       h_qgl2_unmatched[a][b]->Write();
       h_qgl3_unmatched[a][b]->Write();
       h_ptD2_unmatched[a][b]->Write();
       h_minW2_unmatched[a][b]->Write();
       h_nPart2_unmatched[a][b]->Write();
       h_ptD_unmatched[a][b]->Write();
       h_minW_unmatched[a][b]->Write();
       h_nPart_unmatched[a][b]->Write();
       
       h_qgl[a][b]->Write();
       h_qgl_gluon[a][b]->Write();
       h_qgl_quark[a][b]->Write();
       h_qgl_undef[a][b]->Write();

       h_qgl2[a][b]->Write();
       h_qgl2_gluon[a][b]->Write();
       h_qgl2_quark[a][b]->Write();
       h_qgl2_undef[a][b]->Write();

       h_chg[a][b]->Write();
       h_chg_gluon[a][b]->Write();
       h_chg_quark[a][b]->Write();
       h_chg_undef[a][b]->Write();
 
       h_neu[a][b]->Write();
       h_neu_gluon[a][b]->Write();
       h_neu_quark[a][b]->Write();
       h_neu_undef[a][b]->Write();

       h_qgl3[a][b]->Write();
       h_qgl3_gluon[a][b]->Write();
       h_qgl3_quark[a][b]->Write();
       h_qgl3_undef[a][b]->Write();

       h_ptD2_quark[a][b]->Write();
       h_minW2_quark[a][b]->Write();
       h_nPart2_quark[a][b]->Write();

       h_ptD2_gluon[a][b]->Write();
       h_minW2_gluon[a][b]->Write();
       h_nPart2_gluon[a][b]->Write();

       h_ptD2_undef[a][b]->Write();
       h_minW2_undef[a][b]->Write();
       h_nPart2_undef[a][b]->Write();

       h_ptD2[a][b]->Write();
       h_minW2[a][b]->Write();
       h_nPart2[a][b]->Write();

       
       h_ptD_quark[a][b]->Write();
       h_minW_quark[a][b]->Write();
       h_nPart_quark[a][b]->Write();

       h_ptD_gluon[a][b]->Write();
       h_minW_gluon[a][b]->Write();
       h_nPart_gluon[a][b]->Write();

       h_ptD_undef[a][b]->Write();
       h_minW_undef[a][b]->Write();
       h_nPart_undef[a][b]->Write();

       h_ptD[a][b]->Write();
       h_minW[a][b]->Write();
       h_nPart[a][b]->Write();
      
     }
   }

   h_cutFlow->SetBinContent(1,nEvents);
   h_cutFlow->GetXaxis()->SetBinLabel(1,"no selection");
   h_cutFlow->SetBinContent(2,n_trig);
   h_cutFlow->GetXaxis()->SetBinLabel(2,"trigger");
   h_cutFlow->SetBinContent(3,n_twomuons);
   h_cutFlow->GetXaxis()->SetBinLabel(3,"muons");
   h_cutFlow->SetBinContent(4,n_isZ);
   h_cutFlow->GetXaxis()->SetBinLabel(4,"Z");
   h_cutFlow->SetBinContent(5,n_jet);
   h_cutFlow->GetXaxis()->SetBinLabel(5,"jet");
   h_cutFlow->SetBinContent(6,n_isBackToBack);
   h_cutFlow->GetXaxis()->SetBinLabel(6,"DeltaPhi");
   h_cutFlow->SetBinContent(7,n_Leadjet);
   h_cutFlow->GetXaxis()->SetBinLabel(7,"additional jet");
   h_cutFlow->Write();
   fout.Close();
   fileout.close();
   
   std::cout<< "---> "<<sample<<std::endl;
   std::cout<< "Number of events           : "<<nEvents<<std::endl;
   std::cout<< "Events after trigger cut   : "<<n_trig<<std::endl;
   std::cout<< "Events after muon cut   : "<<n_twomuons<<std::endl;
   std::cout<< "Events after Z cut   : "<<n_test<<std::endl;
   std::cout<< "Events after jet cut   : "<<n_jet<<std::endl;
   std::cout<< "Events after deltaPhi cut   : "<<n_isBackToBack<<std::endl;
   std::cout<< "Events after additional jet cut   : "<<n_Leadjet<<std::endl;
}
