#include "../../interface/cutsAndBin_bgk.h"
#include "../../interface/commonUtility.h"
#include "TProfile.h"
#include "TProfile2D.h"

void g1_dijetV2_EtaSys(){
	//This script is for plotting the V2 vs PT. The event mixing effect is subtracted. 
	//Both BRP and FRP are summed up. GEN-level RAPGAP is also histogramed.

	Int_t forMixingQuota = 1;
	TString treeFolder = "/home/samboren/Workspace/samConfig/trees/";

	TFile *fMCTrig = new TFile(treeFolder+"TrkCutsppreco_TrueMC_trigHLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_jetCollectionak4PFJetAnalyzer_minJetPt0.root");
	TFile *fDATA = new TFile(treeFolder+"TrkCutsppreco_upcDiJetSkim2ndVer171107_v2_trigHLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_jetCollectionak4PFJetAnalyzer_minJetPt0.root");
	TFile *fGEN = new TFile(treeFolder+"TrkCutsppreco_GenMC_trig_jetCollectionak4PFJetAnalyzer_minJetPt0.root");
	//"TrkCutsppreco_GenMC_trigHLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_jetCollectionak4PFJetAnalyzer_minJetPt0.root");
	//"TrkCutsppreco_GenMC_trig_jetCollectionak4PFJetAnalyzer_minJetPt0.root");

	TTree *dijetTree_DATA   = (TTree*)fDATA->Get("dijet");
	TTree *trkTree_DATA     = (TTree*)fDATA->Get("fullTrkTree");
	TTree *calTree_DATA = (TTree*)fDATA->Get("Cal");
	TTree *evtTree_DATA = (TTree*)fDATA->Get("evt");
	dijetTree_DATA->AddFriend(trkTree_DATA);
	dijetTree_DATA->AddFriend(calTree_DATA);
	dijetTree_DATA->AddFriend(evtTree_DATA);

	Float_t BRP;
	Float_t FRP;

	UPCdiJet djObj;
	Float_t HFplusmax;
	Float_t HFminusmax;
	TLorentzVector jet1a;
	TLorentzVector jet2a;

	TLorentzVector jet1b;
	TLorentzVector jet2b;

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
	TProfile *p1a = new TProfile("p1a","V2 vs PT: Mixed Data, All QT, Nominal Cuts"			,prfBins,prfMin,prfMax);
	TProfile *p2a = new TProfile("p2a","V2 vs PT: Mixed Data, QT<5 GeV/c, Nominal Cuts"		,prfBins,prfMin,prfMax);
	TProfile *p3a = new TProfile("p3a","V2 vs PT: Mixed Data, 5<QT<10 GeV/c, Nominal Cuts"	,prfBins,prfMin,prfMax);
	TProfile *p4a = new TProfile("p4a","V2 vs PT: Mixed Data, QT<10 GeV/c, Nominal Cuts"   	,prfBins,prfMin,prfMax);
	TProfile *p5a = new TProfile("p5a","V2 vs PT: Data, All QT, Nominal Cuts"     			,prfBins,prfMin,prfMax);
	TProfile *p6a = new TProfile("p6a","V2 vs PT: Data, QT<5 GeV/c, Nominal Cuts"      		,prfBins,prfMin,prfMax);
	TProfile *p7a = new TProfile("p7a","V2 vs PT: Data, 5<QT<10 GeV/c, Nominal Cuts"      	,prfBins,prfMin,prfMax);
	TProfile *p8a = new TProfile("p8a","V2 vs PT: Data, QT<10 GeV/c, Nominal Cuts"			,prfBins,prfMin,prfMax);
	TProfile *p9a = new TProfile("p9a","V2 vs PT: Mixed GEN, All QT, Nominal Cuts"			,prfBins,prfMin,prfMax);
	TProfile *p10a = new TProfile("p10a","V2 vs PT: Mixed GEN, QT<5 GeV/c, Nominal Cuts"		,prfBins,prfMin,prfMax);
	TProfile *p11a = new TProfile("p11a","V2 vs PT: Mixed GEN, 5<QT<10 GeV/c, Nominal Cuts"	,prfBins,prfMin,prfMax);
	TProfile *p12a = new TProfile("p12a","V2 vs PT: Mixed GEN, QT<10 GeV/c, Nominal Cuts"   	,prfBins,prfMin,prfMax);
	TProfile *p13a = new TProfile("p13a","V2 vs PT: GEN, All QT, Nominal Cuts"     			,prfBins,prfMin,prfMax);
	TProfile *p14a = new TProfile("p14a","V2 vs PT: GEN, QT<5 GeV/c, Nominal Cuts"      		,prfBins,prfMin,prfMax);
	TProfile *p15a = new TProfile("p15a","V2 vs PT: GEN, 5<QT<10 GeV/c, Nominal Cuts"      	,prfBins,prfMin,prfMax);
	TProfile *p16a = new TProfile("p16a","V2 vs PT: GEN, QT<10 GeV/c, Nominal Cuts"			,prfBins,prfMin,prfMax);

	prfBins = 100;
	prfMax = 3;
	prfMin = -3;
	TH1F *h1a = new TH1F("h1a","Dijet Eta (kinematic): Mixed Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h2a = new TH1F("h2a","Dijet Eta (kinematic): Mixed Data, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h3a = new TH1F("h3a","Dijet Eta (kinematic): Mixed Data, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h4a = new TH1F("h4a","Dijet Eta (kinematic): Mixed Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h5a = new TH1F("h5a","Dijet Eta (kinematic): Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h6a = new TH1F("h6a","Dijet Eta (kinematic): Data, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h7a = new TH1F("h7a","Dijet Eta (kinematic): Data, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h8a = new TH1F("h8a","Dijet Eta (kinematic): Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h9a = new TH1F("h9a",	 "Dijet Eta (kinematic): Mixed GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h10a = new TH1F("h10a","Dijet Eta (kinematic): Mixed GEN, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h11a = new TH1F("h11a","Dijet Eta (kinematic): Mixed GEN, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h12a = new TH1F("h12a","Dijet Eta (kinematic): Mixed GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h13a = new TH1F("h13a","Dijet Eta (kinematic): GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h14a = new TH1F("h14a","Dijet Eta (kinematic): GEN, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h15a = new TH1F("h15a","Dijet Eta (kinematic): GEN, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h16a = new TH1F("h16a","Dijet Eta (kinematic): GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);

	prfBins = 100;
	prfMax = 3.14159;
	prfMin = 0;
	TH1F *h1b = new TH1F("h1b","Dijet Phi (kinematic): Mixed Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h2b = new TH1F("h2b","Dijet Phi (kinematic): Mixed Data, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h3b = new TH1F("h3b","Dijet Phi (kinematic): Mixed Data, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h4b = new TH1F("h4b","Dijet Phi (kinematic): Mixed Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h5b = new TH1F("h5b","Dijet Phi (kinematic): Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h6b = new TH1F("h6b","Dijet Phi (kinematic): Data, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h7b = new TH1F("h7b","Dijet Phi (kinematic): Data, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h8b = new TH1F("h8b","Dijet Phi (kinematic): Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h9b = new TH1F("h9b",	 "Dijet Phi (kinematic): Mixed GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h10b = new TH1F("h10b","Dijet Phi (kinematic): Mixed GEN, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h11b = new TH1F("h11b","Dijet Phi (kinematic): Mixed GEN, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h12b = new TH1F("h12b","Dijet Phi (kinematic): Mixed GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h13b = new TH1F("h13b","Dijet Phi (kinematic): GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h14b = new TH1F("h14b","Dijet Phi (kinematic): GEN, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h15b = new TH1F("h15b","Dijet Phi (kinematic): GEN, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h16b = new TH1F("h16b","Dijet Phi (kinematic): GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);

	prfBins = 100;
	prfMax = 100;
	prfMin = 0;
	TH1F *h1c = new TH1F("h1c","Dijet pt: Mixed Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h2c = new TH1F("h2c","Dijet pt: Mixed Data, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h3c = new TH1F("h3c","Dijet pt: Mixed Data, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h4c = new TH1F("h4c","Dijet pt: Mixed Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h5c = new TH1F("h5c","Dijet pt: Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h6c = new TH1F("h6c","Dijet pt: Data, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h7c = new TH1F("h7c","Dijet pt: Data, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h8c = new TH1F("h8c","Dijet pt: Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h9c = new TH1F("h9c",	 "Dijet pt: Mixed GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h10c = new TH1F("h10c","Dijet pt: Mixed GEN, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h11c = new TH1F("h11c","Dijet pt: Mixed GEN, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h12c = new TH1F("h12c","Dijet pt: Mixed GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h13c = new TH1F("h13c","Dijet pt: GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h14c = new TH1F("h14c","Dijet pt: GEN, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h15c = new TH1F("h15c","Dijet pt: GEN, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h16c = new TH1F("h16c","Dijet pt: GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);

	prfBins = 100;
	prfMax = 100;
	prfMin = 0;
	TH1F *h1d = new TH1F("h1d","PT: Mixed Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h2d = new TH1F("h2d","PT: Mixed Data, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h3d = new TH1F("h3d","PT: Mixed Data, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h4d = new TH1F("h4d","PT: Mixed Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h5d = new TH1F("h5d","PT: Data, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h6d = new TH1F("h6d","PT: Data, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h7d = new TH1F("h7d","PT: Data, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h8d = new TH1F("h8d","PT: Data, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h9d = new TH1F("h9d",	 "PT: Mixed GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h10d = new TH1F("h10d","PT: Mixed GEN, QT<5 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h11d = new TH1F("h11d","PT: Mixed GEN, 5<QT<10 GeV/c, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h12d = new TH1F("h12d","PT: Mixed GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h13d = new TH1F("h13d","PT: GEN, All QT, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h14d = new TH1F("h14d","PT: GEN, QT<5 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h15d = new TH1F("h15d","PT: GEN, 5<QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);
	TH1F *h16d = new TH1F("h16d","PT: GEN, QT<10 GeV, Nominal Cuts",prfBins,prfMin,prfMax);

	TProfile *hQTDataMix = new TProfile("hQTDataMix","hQTDataMix",2,0,10);
	TProfile *hQTData = new TProfile("hQTData","hQTData",2,0,10);
	TProfile *hQTGenMix = new TProfile("hQTGenMix","hQTGenMix",2,0,10);
	TProfile *hQTGen = new TProfile("hQTGen","hQTGen",2,0,10);

	dijetTree_DATA->SetBranchAddress("dj",&djObj);
	calTree_DATA->SetBranchAddress("HFplusmax",&HFplusmax);
	calTree_DATA->SetBranchAddress("HFminusmax",&HFminusmax);

	Float_t trkPt[1000];
	Float_t trkEta[1000];
	Int_t nTrks;
	Float_t etaEdg = 2.5;
	Float_t ptThreshold = 0.400; //started .200

	Int_t nEvents;
	Int_t matched = 0;
	Int_t tooLoop = dijetTree_DATA->GetEntries();

	dijetTree_DATA->SetBranchAddress("dj",&djObj);
	calTree_DATA->SetBranchAddress("HFplusmax",&HFplusmax);
	calTree_DATA->SetBranchAddress("HFminusmax",&HFminusmax);
	trkTree_DATA->SetBranchAddress("pT",&trkPt);
	trkTree_DATA->SetBranchAddress("Eta",&trkEta);
	trkTree_DATA->SetBranchAddress("ntrk",&nTrks);

	UPCEvent event;
	evtTree_DATA->SetBranchAddress("event",&event);	

	nEvents = dijetTree_DATA->GetEntries();
	Int_t mixingNum = forMixingQuota;
	Float_t vz1 = 0;
	Float_t vz2 = 0;

	Bool_t leftSide = false;
	Bool_t rightSide = false;

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

	//Mixed data, nominal cuts
	//nEvents=5000;
	for(Long64_t i=0; i<nEvents; i++){
		cout<<"mixed data lrg: "<<1.0*i/nEvents<<endl;
		leftSide = false;
		rightSide = false;
		dijetTree_DATA->GetEntry(i);

		if(djObj.e1>djObj.e2){
			jet1a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
			jet2a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		}else{
			jet2a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
			jet1a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		}

		if(djObj.nJet!=2 || abs(djObj.eta1)>1.7 || djObj.pt1<20 || abs(djObj.eta2)>1.7 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;
		jetplus=jet1a+jet2a;
		jetminus=(1-zee)*jet1a - zee*jet2a;
		BRP =  rapidityGapAlgorithm("left",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		FRP =  rapidityGapAlgorithm("right",etaEdg,trkPt,trkEta,ptThreshold,nTrks);		                           
		vz1 = event.vz;

		if( !(BRP>1.2 && BRP>FRP) && !(FRP>1.2 && FRP>BRP)  ) continue;
		if( FRP>1.2 && FRP>BRP) rightSide = true;
		if( BRP>1.2 && BRP>FRP) leftSide = true;

		for(Long64_t j=i+1; j<nEvents-20; j++){
			if(mixingNum==0) continue;
			dijetTree_DATA->GetEntry(j);
			if(i==j || djObj.nJet!=2 || abs(djObj.eta1)>1.7 || djObj.pt1<20 || abs(djObj.eta2)>1.7 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;

			if(djObj.e1>djObj.e2){
				jet1b.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
				jet2b.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
			}else{
				jet2b.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
				jet1b.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
			}

			BRP =  rapidityGapAlgorithm("left",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
			FRP =  rapidityGapAlgorithm("right",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
			vz2 = event.vz;
			if( !(BRP>1.2 && BRP>FRP && leftSide) && !(FRP>1.2 && FRP>BRP && rightSide)  ) continue;
			if( abs(vz1-vz2)>3 ) continue;

			mixingNum--;
			jetplus=jet1a+jet2b;
			jetminus=(1-zee)*jet1a - zee*jet2b;

 	       	TVector2 p, v1;
        	TVector2 q, v2;
       	 	p.Set(jet1a[0],jet1a[1]);
        	q.Set(jet2b[0],jet2b[1]);
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

			p1a->Fill(jetminus.Pt(),cos(2*anglePerp));
			h1a->Fill(jetplus.Eta());
			h1b->Fill(jetplus.Phi());
			h1c->Fill(jetplus.Pt());
			h1d->Fill(jetminus.Pt());

			hQTDataMix->Fill(jetplus.Pt(),cos(2*anglePerp));

			if(jetplus.Pt()<5){
				p2a->Fill(jetminus.Pt(),cos(2*anglePerp));
				h2a->Fill(jetplus.Eta());
				h2b->Fill(jetplus.Phi());
				h2c->Fill(jetplus.Pt());
				h2d->Fill(jetminus.Pt());
			}
			if(5<jetplus.Pt() && jetplus.Pt()<10){
				p3a->Fill(jetminus.Pt(),cos(2*anglePerp));
				h3a->Fill(jetplus.Eta());
				h3b->Fill(jetplus.Phi());
				h3c->Fill(jetplus.Pt());
				h3d->Fill(jetminus.Pt());
			}
			if(jetplus.Pt()<10){
				p4a->Fill(jetminus.Pt(),cos(2*anglePerp));
				h4a->Fill(jetplus.Eta());
				h4b->Fill(jetplus.Phi());
				h4c->Fill(jetplus.Pt());
				h4d->Fill(jetminus.Pt());
			}
		}
		mixingNum=forMixingQuota;
	}

	//The pure data, nominal cuts
	nEvents=dijetTree_DATA->GetEntries();
	for(Long64_t i=0; i<nEvents; i++){
		matched=0;
		cout<<"data lrg "<<1.0*i/nEvents<<endl;
		dijetTree_DATA->GetEntry(i);

		if(djObj.e1>djObj.e2){
			jet1a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
			jet2a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		}else{
			jet2a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
			jet1a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		}

		if(djObj.nJet!=2 || abs(djObj.eta1)>1.7 || djObj.pt1<20 || abs(djObj.eta2)>1.7 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;
		BRP =  rapidityGapAlgorithm("left",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		FRP =  rapidityGapAlgorithm("right",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		jetplus=jet1a+jet2a;
		jetminus=(1-zee)*jet1a - zee*jet2a;

		if( !(BRP>1.2 && BRP>FRP) && !(FRP>1.2 && FRP>BRP)  ) continue;
		vz1 = event.vz;

		jetplus=jet1a+jet2a;
		jetminus=(1-zee)*jet1a - zee*jet2a;

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

		p5a->Fill(jetminus.Pt(),cos(2*anglePerp));
		h5a->Fill(jetplus.Eta());
		h5b->Fill(jetplus.Phi());
		h5c->Fill(jetplus.Pt());
		h5d->Fill(jetminus.Pt());

		hQTData->Fill(jetplus.Pt(),cos(2*anglePerp));

		if(jetplus.Pt()<5){
			p6a->Fill(jetminus.Pt(),cos(2*anglePerp));
			h6a->Fill(jetplus.Eta());
			h6b->Fill(jetplus.Phi());
			h6c->Fill(jetplus.Pt());
			h6d->Fill(jetminus.Pt());
		}
		if(5<jetplus.Pt() && jetplus.Pt()<10){
			p7a->Fill(jetminus.Pt(),cos(2*anglePerp));
			h7a->Fill(jetplus.Eta());
			h7b->Fill(jetplus.Phi());
			h7c->Fill(jetplus.Pt());
			h7d->Fill(jetminus.Pt());
		}
		if(jetplus.Pt()<10){
			p8a->Fill(jetminus.Pt(),cos(2*anglePerp));
			h8a->Fill(jetplus.Eta());
			h8b->Fill(jetplus.Phi());
			h8c->Fill(jetplus.Pt());
			h8d->Fill(jetminus.Pt());
		}
	}

	//Fill in the Gen result plotss
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
	UPCdiJet djObjGen;
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
	mixingNum = forMixingQuota;
	nEvents = dijetTree_MC->GetEntries();

	//nEvents = 5000;
	for(Long64_t i=0; i<nEvents; i++){
		dijetTree_GEN->GetEntry(i);
		cout<<"mixed mc:"<<1.0*i/nEvents<<endl;

		if(djObjGen.pt1>djObjGen.pt2){
			jet1a.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);
			jet2a.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);

			if( abs(djObjGen.eta1)>1.7 || djObjGen.pt1<20 || abs(djObjGen.eta2)>1.7 || djObjGen.pt2<15 || djObjGen.mass<35 || djObjGen.dphi<2) continue;
			BRP =  rapidityGapAlgorithmGEN("left",etaEdg,ptGen,etaGen,ptThreshold);
			FRP =  rapidityGapAlgorithmGEN("right",etaEdg,ptGen,etaGen,ptThreshold);

			if( BRP<1.2 ) continue;
			if( BRP<FRP ) continue;

			vz1 = event.vz;
			for(Long64_t j=i+1; j<nEvents; j++){
				if(mixingNum==0) continue;
				dijetTree_GEN->GetEntry(j);
				if( abs(djObjGen.eta1)>1.7 || djObjGen.pt1<20 || abs(djObjGen.eta2)>1.7 || djObjGen.pt2<15 || djObjGen.mass<35 || djObjGen.dphi<2) continue;
				BRP =  rapidityGapAlgorithmGEN("left",etaEdg,ptGen,etaGen,ptThreshold);
				FRP =  rapidityGapAlgorithmGEN("right",etaEdg,ptGen,etaGen,ptThreshold);
				if( BRP<1.2 ) continue;
				if( BRP<FRP ) continue;
				vz2 = event.vz;
				if( abs(vz1-vz2)>3 ) continue;
				mixingNum--;

				dijetTree_GEN->GetEntry(i);
				jet1a.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);

				dijetTree_GEN->GetEntry(j);
				jet2b.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);

				if(jet1a.E()<jet2b.E()){
					TLorentzVector v;
					v = jet2b;
					jet2b = jet1a;
					jet1a = v;
				}

				jetplusGen=jet1a+jet2b;
				jetminusGen=(1-zee)*jet1a - zee*jet2b;

	       		TVector2 p, v1;
		    	TVector2 q, v2;
		   	 	p.Set(jet1a[0],jet1a[1]);
		    	q.Set(jet2b[0],jet2b[1]);
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
				anglePerpGen=a12;

				p9a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
				h9a->Fill(jetplusGen.Eta());
				h9b->Fill(jetplusGen.Phi());
				h9c->Fill(jetplusGen.Pt());
				h9d->Fill(jetminusGen.Pt());

				hQTGenMix->Fill(jetplusGen.Pt(),cos(2*anglePerpGen));

				if(jetplusGen.Pt()<5){
					p10a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
					h10a->Fill(jetplusGen.Eta());
					h10b->Fill(jetplusGen.Phi());
					h10c->Fill(jetplus.Pt());
					h10d->Fill(jetminusGen.Pt());
				}
				if(5<jetplusGen.Pt() && jetplusGen.Pt()<10){
					p11a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
					h11a->Fill(jetplusGen.Eta());
					h11b->Fill(jetplusGen.Phi());
					h11c->Fill(jetplusGen.Pt());
					h11d->Fill(jetminusGen.Pt());
				}
				if(jetplusGen.Pt()<10){
					p12a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
					h12a->Fill(jetplusGen.Eta());
					h12b->Fill(jetplusGen.Phi());
					h12c->Fill(jetplusGen.Pt());
					h12d->Fill(jetminusGen.Pt());
				}			
			}
			mixingNum=forMixingQuota;
		}
	}

	for(Long64_t i=0; i<nEvents; i++){
		dijetTree_GEN->GetEntry(i);
		cout<<"pure mc:"<<1.0*i/nEvents<<endl;
		if( abs(djObjGen.eta1)>1.7 || djObjGen.pt1<20 || abs(djObjGen.eta2)>1.7 || djObjGen.pt2<15|| djObjGen.mass<35 || djObjGen.dphi<2) continue;
		BRP =  rapidityGapAlgorithmGEN("left",etaEdg,ptGen,etaGen,ptThreshold);
		FRP =  rapidityGapAlgorithmGEN("right",etaEdg,ptGen,etaGen,ptThreshold);
		if( !(BRP>1.2) ) continue;
		if( !(BRP>FRP) ) continue;


		dijetTree_GEN->GetEntry(i);
		jet1a.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);
		jet2a.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);

		if(jet1a.E()<jet2a.E()){
			TLorentzVector v;
			v = jet2a;
			jet2a = jet1a;
			jet1a = v;
		}

		jetplusGen=jet1a+jet2a;
		jetminusGen=(1-zee)*jet1a - zee*jet2a;

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
		anglePerpGen=a12;

		p13a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
		h13a->Fill(jetplusGen.Eta());
		h13b->Fill(jetplusGen.Phi());
		h13c->Fill(jetplusGen.Pt());
		h13d->Fill(jetminusGen.Pt());

		hQTGen->Fill(jetplusGen.Pt(),cos(2*anglePerpGen));

		if(jetplusGen.Pt()<5){
			p14a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
			h14a->Fill(jetplusGen.Eta());
			h14b->Fill(jetplusGen.Phi());
			h14c->Fill(jetplusGen.Pt());
			h14d->Fill(jetminusGen.Pt());
		}
		if(5<jetplusGen.Pt() && jetplusGen.Pt()<10){
			p15a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
			h15a->Fill(jetplusGen.Eta());
			h15b->Fill(jetplusGen.Phi());
			h15c->Fill(jetplusGen.Pt());
			h15d->Fill(jetminusGen.Pt());
		}
		if(jetplusGen.Pt()<10){
			p16a->Fill(jetminusGen.Pt(),cos(2*anglePerpGen));
			h16a->Fill(jetplusGen.Eta());
			h16b->Fill(jetplusGen.Phi());
			h16c->Fill(jetplusGen.Pt());
			h16d->Fill(jetminusGen.Pt());
		}
	}

	gStyle->SetPadGridX(true);
	gStyle->SetPadGridY(true);
	gStyle->SetOptStat(0);

	TFile* outputFile = new TFile("objects/roots/etasys/g1_dijetV2_etasys.root","RECREATE");

	p1a->Write(); 
	p2a->Write(); 
	p3a->Write(); 
	p4a->Write(); 
	p5a->Write(); 
	p6a->Write(); 
	p7a->Write(); 
	p8a->Write(); 
	p9a->Write(); 
	p10a->Write(); 
	p11a->Write(); 
	p12a->Write(); 
	p13a->Write(); 
	p14a->Write();
	p15a->Write(); 
	p16a->Write();

	TH1D* p1b = getProfileDifference(p5a,p1a);
	TH1D* p2b = getProfileDifference(p6a,p2a);
	TH1D* p3b = getProfileDifference(p7a,p3a);
	TH1D* p4b = getProfileDifference(p8a,p4a);
	p1b->SetTitle("Subbed Result, Data, QT All, Nominal Cuts");
	p2b->SetTitle("Subbed Result, Data,  QT<5 GeV/c, Nominal Cuts");
	p3b->SetTitle("Subbed Result, Data, 5<QT<10 GeV/c, Nominal Cuts");
	p4b->SetTitle("Subbed Result, Data, QT<10 GeV/c, Nominal Cuts");


	TH1D* p5b = getProfileDifference(p13a,p9a);
	TH1D* p6b = getProfileDifference(p14a,p10a);
	TH1D* p7b = getProfileDifference(p15a,p11a);
	TH1D* p8b = getProfileDifference(p16a,p12a);	
	p5b->SetTitle("Subbed Result, RAPGAP GEN, QT All, Nominal Cuts");
	p6b->SetTitle("Subbed Result, RAPGAP GEN, QT<5 GeV/c, Nominal Cuts");
	p7b->SetTitle("Subbed Result, RAPGAP GEN, 5<QT<10 GeV/c, Nominal Cuts");
	p8b->SetTitle("Subbed Result, RAPGAP GEN, QT<10 GeV/c, Nominal Cuts");

	p1b->SetName("p1b");
	p2b->SetName("p2b");
	p3b->SetName("p3b");
	p4b->SetName("p4b");
	p5b->SetName("p5b");
	p6b->SetName("p6b");
	p7b->SetName("p7b");
	p8b->SetName("p8b");

	p1b->Write();
	p2b->Write();
	p3b->Write();
	p4b->Write();
	p5b->Write();
	p6b->Write();
	p7b->Write();
	p8b->Write();


	TH1D* hQTDataSub = getProfileDifference(hQTData,hQTDataMix);
	TH1D* hQTGenSub = getProfileDifference(hQTGen,hQTGenMix);
	hQTDataSub->SetName("hQTDataSub");
	hQTGenSub->SetName("hQTGenSub");

	hQTGen->Write();
	hQTData->Write();
	hQTDataMix->Write();
	hQTGenMix->Write();
	hQTDataSub->Write();
	hQTGenSub->Write();


	h1a->Write();
	h2a->Write();
	h3a->Write();
	h4a->Write();
	h5a->Write();
	h6a->Write();
	h7a->Write();
	h8a->Write();
	h9a->Write();
	h10a->Write();
	h11a->Write();
	h12a->Write();
	h13a->Write();
	h14a->Write();
	h15a->Write();
	h16a->Write();

	h1b->Write();
	h2b->Write();
	h3b->Write();
	h4b->Write();
	h5b->Write();
	h6b->Write();
	h7b->Write();
	h8b->Write();
	h9b->Write();
	h10b->Write();
	h11b->Write();
	h12b->Write();
	h13b->Write();
	h14b->Write();
	h15b->Write();
	h16b->Write();

	h1c->Write();
	h2c->Write();
	h3c->Write();
	h4c->Write();
	h5c->Write();
	h6c->Write();
	h7c->Write();
	h8c->Write();
	h9c->Write();
	h10c->Write();
	h11c->Write();
	h12c->Write();
	h13c->Write();
	h14c->Write();
	h15c->Write();
	h16c->Write();

	h1d->Write();
	h2d->Write();
	h3d->Write();
	h4d->Write();
	h5d->Write();
	h6d->Write();
	h7d->Write();
	h8d->Write();
	h9d->Write();
	h10d->Write();
	h11d->Write();
	h12d->Write();
	h13d->Write();
	h14d->Write();
	h15d->Write();
	h16d->Write();

	outputFile->Save();
	outputFile->Close();
}
