#include <iostream>
#include <iomanip>
using namespace std;
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TAttFill.h"
#include "TCanvas.h"
#include <vector>
#include "stdio.h"
#include <stdlib.h>
#include "math.h"
#include "TMath.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TStyle.h"
#include "THStack.h"
#include "TFitResultPtr.h"
#include <fstream>

void Example_for_Dave()
{
     TString fileName="/home/elb8/EMTF_pT_Assign/EMTFPtAssign2017/PtRegression_for_DNN_Vars_MODE_15_noBitCompr_RPC.root";
     TString directoryName="f_MODE_15_invPtTarg_invPtWgt_noBitCompr_RPC/TrainTree";
     TFile* myFile = new TFile(fileName);//load data
     TTree* myTree = (TTree*) myFile->Get(directoryName);
     Float_t GEN_pt;
     Float_t dPhi_12;
     Float_t dPhi_23;
     Float_t dPhi_34;
     Float_t dTh_12;
     Float_t dTh_23;
     Float_t dTh_34;
     
     myTree->SetBranchAddress("GEN_pt",&GEN_pt);
     myTree->SetBranchAddress("dPhi_12",&dPhi_12);
     myTree->SetBranchAddress("dPhi_23",&dPhi_23);
     myTree->SetBranchAddress("dPhi_34",&dPhi_34);
     myTree->SetBranchAddress("dTh_12",&dTh_12);
     myTree->SetBranchAddress("dTh_23",&dTh_23);
     myTree->SetBranchAddress("dTh_34",&dTh_34);
     
     ofstream output("Example_for_Dave.txt");
     Long64_t numEvents = 10;
     for (Long64_t iEntry = 0;iEntry<numEvents;iEntry++){
       myTree->GetEntry(iEntry*100);
       output<< setw(10)<< "      " << setw(6)<<"dTh" << setw(6)<< "dPhi" << endl;
       output<< setw(10)<< "dSt_12" << setw(6)<<dTh_12 << setw(6)<< dPhi_12 << endl;
       output<< setw(10)<< "dSt_23" << setw(6)<<dTh_23 << setw(6)<< dPhi_23 << endl;
       output<< setw(10)<< "dSt_34" << setw(6)<<dTh_34 << setw(6)<< dPhi_34 << endl;
       output<< setw(10)<<" pT = "<< GEN_pt << endl;
       output << endl;
     }
      
}
