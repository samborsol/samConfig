#include "../../interface/cutsAndBin_bgk.h"
#include "../../interface/commonUtility.h"
#include "TProfile.h"
#include "TProfile2D.h"

void g1_dijetRVal_EtaSys(){
	//This macro makes a plot of the MC closure, and plots the R-Value.
	//Both BRP and FRP are summed up.

	Int_t forMixingQuota = 1;
	TString treeFolder = "/home/samboren/Workspace/samConfig/trees/";
	TFile *fGEN = new TFile(treeFolder+"TrkCutsppreco_GenMC_trigHLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_jetCollectionak4PFJetAnalyzer_minJetPt0.root");
	TTree *dijetTree_MC  	= (TTree*)fGEN->Get("dijet");
	TTree *trkTree_MC     	= (TTree*)fGEN->Get("fullTrkTree");
	TTree *calTree_MC 		= (TTree*)fGEN->Get("Cal");
	TTree *evtTree_MC 		= (TTree*)fGEN->Get("evt");
	TTree *dijetTree_GEN 	= (TTree*)fGEN->Get("djGen");
	TTree *genTree      	= (TTree*)fGEN->Get("hi");
	dijetTree_GEN->AddFriend(genTree);
	genTree->SetMakeClass(1);

	dijetTree_MC->AddFriend(trkTree_MC);
	dijetTree_MC->AddFriend(calTree_MC);
	dijetTree_MC->AddFriend(evtTree_MC);
	dijetTree_MC->AddFriend(dijetTree_GEN);

	vector<float>   *etaGen = new vector<float>;
	vector<float>   *ptGen  = new vector<float>;
	Float_t BRP;
	Float_t FRP;

	UPCdiJet djObj;
	UPCdiJet djObjGen;
	UPCEvent event;
	Float_t HFplusmax;
	Float_t HFminusmax;
	TLorentzVector jet1a;
	TLorentzVector jet2a;
	TLorentzVector jet1b;
	TLorentzVector jet2b;
	TLorentzVector jet1aGen;
	TLorentzVector jet2aGen;
	TLorentzVector jet1bGen;
	TLorentzVector jet2bGen;
	TLorentzVector jetplus;
	TLorentzVector jetminus;
	TLorentzVector jetplusGen;
	TLorentzVector jetminusGen;
	Float_t zee = 0.5;
	Float_t anglePerp;
	Float_t anglePerpGen;
	Float_t d_phi;

	Int_t prfBins = 5;
	Float_t prfMax = 43;
	Float_t prfMin = 18;

	TProfile *p17 = new TProfile("p17","R(v2) vs PT: All QT"               ,prfBins,prfMin,prfMax);
	TProfile *p18 = new TProfile("p18","R(v2) vs PT: QT<5 GeV/c"           ,prfBins,prfMin,prfMax);
	TProfile *p19 = new TProfile("p19","R(v2) vs PT: 5<QT<10 GeV/c"        ,prfBins,prfMin,prfMax);
	TProfile *p20 = new TProfile("p20","R(v2) vs PT: QT<10 GeV/c"          ,prfBins,prfMin,prfMax);

	prfBins = 100;
	prfMin = 0;
	prfMax = 6.5;

	TProfile *p21 = new TProfile("p21","R(phi) vs Phi: All QT"               ,prfBins,prfMin,prfMax);
	TProfile *p22 = new TProfile("p22","R(phi) vs Phi: QT<5 GeV/c"           ,prfBins,prfMin,prfMax);
	TProfile *p23 = new TProfile("p23","R(phi) vs Phi: 5<QT<10 GeV/c"        ,prfBins,prfMin,prfMax);
	TProfile *p24 = new TProfile("p24","R(phi) vs Phi: QT<10 GeV/c"          ,prfBins,prfMin,prfMax);

	prfBins = 2;
	prfMin = 0;
	prfMax = 10;
	TProfile *p25 = new TProfile("p25","R(v2) vs QT"        ,prfBins,prfMin,prfMax);

	Float_t trkPt[1000];
	Float_t trkEta[1000];
	Int_t nTrks;	
	Float_t etaEdg = 2.5;
	Float_t ptThreshold = 0.0; //started .200

	dijetTree_MC->SetBranchAddress("dj",&djObj);
	dijetTree_GEN->SetBranchAddress("djGen",&djObjGen);
	calTree_MC->SetBranchAddress("HFplusmax",&HFplusmax);
	calTree_MC->SetBranchAddress("HFminusmax",&HFminusmax);
	trkTree_MC->SetBranchAddress("pT",&trkPt);
	trkTree_MC->SetBranchAddress("Eta",&trkEta);
	trkTree_MC->SetBranchAddress("ntrk",&nTrks);
	genTree->SetBranchAddress("pt",&ptGen);
	genTree->SetBranchAddress("eta",&etaGen);
	evtTree_MC->SetBranchAddress("event",&event);


	Int_t eventsToMix = forMixingQuota;
	Int_t mixingNum = forMixingQuota;
	Int_t sideMarker = 0;

	Float_t vz1 = 0;
	Float_t vz2 = 0;

	Int_t nEvents = dijetTree_MC->GetEntries();

    //Define the TLorentzVectors
    TLorentzVector v01, v02, vv1, vv2, vqt, vpt, m, w, g, h, p, q;
    TVector2 n;
    
    //Define variables
    Double_t pi = TMath::Pi();
    float v1_norm, v2_norm, n_norm, m_norm;
    float c12, s12, v1v2, a12;
    float pt1, pt2, eta1, eta2, phi1, phi2, e1, e2;
    float px1, py1, pz1, ee1, px2, py2, pz2, ee2;
    float ptvqt, ptvpt;
    float sign=0.0;

	//Here there is mixing.

	nEvents = dijetTree_MC->GetEntries();
	for(Long64_t i=0; i<nEvents; i++){
		//cout<<"mc: "<<1.0*i/nEvents<<endl;
		dijetTree_MC->GetEntry(i);
		if( djObj.nJet != 2 || abs(djObj.eta1)>1.7 || djObj.pt1<20 || abs(djObj.eta2)>1.7 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;
		BRP =  rapidityGapAlgorithm("left",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		FRP =  rapidityGapAlgorithm("right",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		if( !(BRP>1.2 && BRP>FRP) ) continue;	

		if(djObj.e1>djObj.e2){
			jet1a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
			jet2a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		}else{
			jet2a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
			jet1a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		}

		jetplus=jet1a+jet2a;
		jetminus=0.5*(jet1a-jet2a);

		TVector2 p, v1;
		TVector2 q, v2;
		p.Set(jet1a[0],jet1a[1]);
		q.Set(jet2a[0],jet2a[1]);
		   //Computing Qt and Pt as 2-Vectors
		v1.Set(p.X() + q.X(),p.Y()+q.Y());
		v2.Set(0.5*(p.X()-q.X()),0.5*(p.Y()-q.Y()));
		//computing the norm of Qt and Pt
		v1_norm = sqrt (  v1.X() * v1.X() + v1.Y() * v1.Y()    );
		v2_norm = sqrt ( v2.X() * v2.X() + v2.Y() * v2.Y()   );
		//Making unit vectors of Qt and Pt, resulting in Qt-hat and Pt-hat, unit vectors
		TVector2 v1unit, v2unit;
		v1unit.Set(v1.X() / v1_norm,v1.Y() / v1_norm);
		v2unit.Set(v2.X() / v2_norm,v2.Y() / v2_norm);
		//Computing the dot product of Qt-hat and Pt-hat
		v1v2 = v1unit.X() * v2unit.X() + v1unit.Y() * v2unit.Y()   ;
		//The dot product is the cosine of the angle
		c12 = v1v2  ;
		//Define a perpendicular angle to Qt-hat, in order to compute the sine of the angle
		n.Set(v1unit.Y(),-v1unit.X()) ;
		n_norm = sqrt ( n.X()*n.X() + n.Y()*n.Y()  );
		//Sine of the angle
		s12 = (n.X()*v2unit.X() + n.Y()*v2unit.Y()  ) ;
		//Computing the angle by using arctan2 function, and considering the sign, so will be from 0,2*pi
		a12 = atan2(s12, c12);			
		if (a12>=0) a12 = a12;
		if (a12<0) a12 = a12 + 2*pi;
		//Computing the cos(2phi) using trigonometry expression
		c12  = cos(a12) * cos(a12) - sin(a12) * sin(a12);
		anglePerp=a12;

		dijetTree_GEN->GetEntry(i);
		if(djObjGen.e1>djObjGen.e2){
			jet1aGen.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);
			jet2aGen.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);
		}else{
			jet2aGen.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);
			jet1aGen.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);
		}

//cout<<jet1a.E()<<" "<<jet1a.Px()<<" "<<jet1a.Py()<<" "<<jet1a.Pz()<<" "<<jet2a.E()<<" "<<jet2a.Px()<<" "<<jet2a.Py()<<" "<<jet2a.Pz()<<" "<<jet1aGen.E()<<" "<<jet1aGen.Px()<<" "<<jet1aGen.Py()<<" "<<jet1aGen.Pz()<<" "<<jet2aGen.E()<<" "<<jet2aGen.Px()<<" "<<jet2aGen.Py()<<" "<<jet2aGen.Pz()<<endl;

		jetplusGen=jet1aGen+jet2aGen;
		jetminusGen=0.5*(jet1aGen-jet2aGen);
		p.Set(jet1aGen[0],jet1aGen[1]);
		q.Set(jet2aGen[0],jet2aGen[1]);
		//Computing Qt and Pt as 2-Vectors
		v1.Set(p.X() + q.X(),p.Y()+q.Y());
		v2.Set(0.5*(p.X()-q.X()),0.5*(p.Y()-q.Y()));
		//computing the norm of Qt and Pt
		v1_norm = sqrt (  v1.X() * v1.X() + v1.Y() * v1.Y()    );
		v2_norm = sqrt ( v2.X() * v2.X() + v2.Y() * v2.Y()   );
		//Making unit vectors of Qt and Pt, resulting in Qt-hat and Pt-hat, unit vectors
		v1unit.Set(v1.X() / v1_norm,v1.Y() / v1_norm);
		v2unit.Set(v2.X() / v2_norm,v2.Y() / v2_norm);
		//Computing the dot product of Qt-hat and Pt-hat
		v1v2 = v1unit.X() * v2unit.X() + v1unit.Y() * v2unit.Y()   ;
		//The dot product is the cosine of the angle
		c12 = v1v2  ;
		//Define a perpendicular angle to Qt-hat, in order to compute the sine of the angle
		n.Set(v1unit.Y(),-v1unit.X()) ;
		n_norm = sqrt ( n.X()*n.X() + n.Y()*n.Y()  );
		//Sine of the angle
		s12 = (n.X()*v2unit.X() + n.Y()*v2unit.Y()  ) ;
		//Computing the angle by using arctan2 function, and considering the sign, so will be from 0,2*pi
		a12 = atan2(s12, c12);			
		if (a12>=0) a12 = a12;
		if (a12<0) a12 = a12 + 2*pi;
		//Computing the cos(2phi) using trigonometry expression
		c12  = cos(a12) * cos(a12) - sin(a12) * sin(a12);
		anglePerpGen=a12;

		p17->Fill(jetminus.Pt(),cos(2*(anglePerp-anglePerpGen)));
		p21->Fill(anglePerp,abs(anglePerp-anglePerpGen));
		p25->Fill(jetplus.Pt(),cos(2*(anglePerp-anglePerpGen)));
		if(jetplus.Pt()<5){
			p18->Fill(jetminus.Pt(),cos(2*(anglePerp-anglePerpGen)));
			p22->Fill(anglePerp,abs(anglePerp-anglePerpGen));
		}
		if(5<jetplus.Pt() && jetplus.Pt()<10){
			p19->Fill(jetminus.Pt(),cos(2*(anglePerp-anglePerpGen)));
			p23->Fill(anglePerp,abs(anglePerp-anglePerpGen));
		}
		if(jetplus.Pt()<10){
			p20->Fill(jetminus.Pt(),cos(2*(anglePerp-anglePerpGen)));
			p24->Fill(anglePerp,abs(anglePerp-anglePerpGen));
		}
	}

	TFile* outputRoot = new TFile("objects/roots/etasys/g1_dijetRVal_etasys.root","RECREATE");
	
	p17->Write();
	p18->Write();
	p19->Write();
	p20->Write();

	p21->Write();
	p22->Write();
	p23->Write();
	p24->Write();

	p25->Write();

	outputRoot->Save();
	outputRoot->Close();
}
