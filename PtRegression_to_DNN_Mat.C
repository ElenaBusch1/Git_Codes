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

void PtRegression_to_DNN_Mat()
{
    //TString MODE[11]={"15","14","13","11","7","12","10","9","6","5","3"};
    //Double_t mode[11]={15,  14,  13,  11,  7,  12,  10,  9,  6,  5,  3};
    //TString MODE[1]={"15"};
    //Double_t mode[1] = {15};
    //int MODES;//number of modes
    //MODES = sizeof(MODE) / sizeof(TString);


	//loop through all modes
	// for (int i=0;i<MODES;i++){        
	//TString fileName="/storage1/users/jtr6/EMTF_ML_training_results/PtRegression_Apr_2017_06_05_invPtTarg_invPtWgt_MODE_" + MODE[0] + "_bitCompr_noRPC.root";
	//TString directoryName="f_MODE_"+ MODE[0]+ "_15_invPtTarg_invPtWgt_bitCompr_noRPC/TrainTree";

	TString fileName="/home/elb8/EMTF_pT_Assign/EMTFPtAssign2017/PtRegression_for_DNN_Vars_MODE_15_noBitCompr_RPC.root";
	TString directoryName="f_MODE_15_invPtTarg_invPtWgt_noBitCompr_RPC/TrainTree";

	TFile* myFile = new TFile(fileName);//load data
	TTree* myTree = (TTree*) myFile->Get(directoryName);

	Float_t GEN_pt;
        Float_t EMTF_mode;
        Float_t TRK_mode;
	Float_t dPhi_12;
	Float_t dPhi_23;
	Float_t dPhi_34;
	//Float_t dPhi_14;
	//Float_t dPhi_13;
	//Float_t dPhi_24;
	Float_t dTh_12;
	Float_t dTh_23;
	Float_t dTh_34;
	Float_t theta;
	Float_t GEN_eta;

	myTree->SetBranchAddress("GEN_pt",&GEN_pt);//GEN pT
        myTree->SetBranchAddress("EMTF_mode",&EMTF_mode);
        myTree->SetBranchAddress("TRK_mode",&TRK_mode);
	myTree->SetBranchAddress("dPhi_12",&dPhi_12);
	myTree->SetBranchAddress("dPhi_23",&dPhi_23);
	myTree->SetBranchAddress("dPhi_34",&dPhi_34);
	myTree->SetBranchAddress("dTh_12",&dTh_12);
	myTree->SetBranchAddress("dTh_23",&dTh_23);
	myTree->SetBranchAddress("dTh_34",&dTh_34);
	myTree->SetBranchAddress("theta",&theta);
	myTree->SetBranchAddress("GEN_eta",&GEN_eta);

	int DATATYPE = 1; // Set 1 for one array per event, set 3 for 3 arrays per event

	Long64_t numEvents = myTree->GetEntries();//read the number of entries in myTree
        cout<<">>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout<<numEvents<<" events to process..."<<endl;
	ofstream output("First_100_64_3_Station_mats.csv");

	// loop over all events
	for(Long64_t iEntry = 0; iEntry <100; iEntry++){
        	//load the i-th event, replace 100 w numEvents
		if (iEntry % 100000 == 0){
			cout<< "Analyzing event " << iEntry << endl;
		}
		myTree->GetEntry(iEntry);

		int col_12;		
		int row_12;	
                int col_23;
                int row_23;
                int col_34;
                int row_34;

		row_12 = ceil(dTh_12 + 8); // Map dTh-12(-8 -> 8) to 0 -> 63 (0 -> 16)
		row_23 = ceil(dTh_23 + 8); // Map dTh-23(-8 -> 8) to 0 -> 63 (0 -> 16)
		row_34 = ceil(dTh_34 + 8); // Map dTh-34(-8 -> 8) to 0 -> 63 (0 -> 16)
		col_12 = floor(dPhi_12/16.5); //Map dPhi_12(0->1050) to 0->63
		col_23 = floor((dPhi_23+1050)/32.9); // Map dPhi_23(-1050->1050) to 0->63
		col_34 = floor((dPhi_34+1050)/32.9); // Map dPhi_34(-1050->1050) to 0->63
		
		if (DATATYPE == 3){
			output << GEN_pt << endl;
			int array_12[64][64] = {0};//Station 1-2
			int array_23[64][64] = {0};//Station 2-3
			int array_34[64][64] = {0};//Station 3-4
			array_12[row_12][col_12] = 1;	
			array_23[row_23][col_23] = 1;
			array_34[row_34][col_34] = 1;
			for (int i=0; i<64; i++){
	 	   		for(int j=0; j<64; j++){
					if(j == 63){
					output<<array_12[i][j]<< endl;}
					else{
					output<<array_12[i][j]<< ",";}
		  		 }
			}
			output << endl;
                        for (int i=0; i<64; i++){
                                for(int j=0; j<64; j++){
                                        if(j == 63){
                                        output<<array_23[i][j]<< endl;}
                                        else{
                                        output<<array_23[i][j]<< ",";}
                                 }
                        }
                        output << endl;
                        for (int i=0; i<64; i++){
                                for(int j=0; j<64; j++){
                                        if(j == 63){
                                        output<<array_34[i][j]<< endl;}
                                        else{
                                        output<<array_34[i][j]<< ",";}
                                 }
                        }
                        output << endl;
		}//end if DATATYPE == 3
		if (DATATYPE == 1){
			output << GEN_pt << endl;
			int array[64][64] = {0};
			array[row_12][col_12] += 1;
			array[row_23][col_23] += 2;
			array[row_34][col_34] += 4;
			for (int i=0; i<64; i++){
                                for(int j=0; j<64; j++){
					if (j == 63){
                                 	output <<array[i][j]<< endl;}//last entry
					else{
					output <<array[i][j]<<",";}
                                }
			}
			output << endl; //skip line between matricies
		}//end if DATATYPE == 1
		if (DATATYPE != 3 && DATATYPE != 1){
		cout << "Error: No valid data type selected" << endl;
		break;
		}
	}//end loop over events
cout << "Done looping over files" << endl;
}//end pT Regression analysis
