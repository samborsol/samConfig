#include "../interface/cutsAndBin_bgk.h"
#include "../interface/commonUtility.h"
#include "TProfile.h"
#include "TProfile2D.h"

void g2_dijetPhiCent(){
	//This script is for plotting the V2 vs PT. The event mixing effect is subtracted. GEN-level RAPGAP is also plotted.

	Int_t forMixingQuota = 2;
	TString treeFolder = "/home/samboren/Workspace/samConfig/trees/";

//	TFile *fDATA = new TFile(treeFolder+"TrkCutsppreco_TrueMC_trigHLT_HIUPCSingleEG5NotHF2Pixel_SingleTrack_v1_jetCollectionak4PFJetAnalyzer_minJetPt0.root");
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

	dijetTree_DATA->SetBranchAddress("dj",&djObj);
	calTree_DATA->SetBranchAddress("HFplusmax",&HFplusmax);
	calTree_DATA->SetBranchAddress("HFminusmax",&HFminusmax);

	Float_t trkPt[1000];
	Float_t trkEta[1000];
	Int_t nTrks;
	Float_t etaEdg = 2.5;
	Float_t ptThreshold = 0.0; //started .200

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

	Float_t min = 0;
	Float_t max = 6.5;

	TH1F* h1 = new TH1F("h1","Phi(QT,PT) Dist, QT All, Mixed Data",100,min,max);
	TH1F* h2 = new TH1F("h2","Phi(QT,PT) Dist, QT<5 GeV/c, Mixed Data",100,min,max);
	TH1F* h3 = new TH1F("h3","Phi(QT,PT) Dist, 5<QT<10 GeV/c, Mixed Data",100,min,max);
	TH1F* h4 = new TH1F("h4","Phi(QT,PT) Dist, QT<10 GeV/c, Mixed Data",100,min,max);

	TH1F* h5 = new TH1F("h5","Phi(QT,PT) Dist, QT All, Initial Data",100,min,max);
	TH1F* h6 = new TH1F("h6","Phi(QT,PT) Dist, QT<5 GeV/c, Initial Data",100,min,max);
	TH1F* h7 = new TH1F("h7","Phi(QT,PT) Dist, 5<QT<10 GeV/c, Initial Data",100,min,max);
	TH1F* h8 = new TH1F("h8","Phi(QT,PT) Dist, QT<10 GeV/c, Initial Data",100,min,max);

	TH1F* h9  = new TH1F("h9","Phi(QT,PT) Dist, QT All, Mixed GEN",100,min,max);
	TH1F* h10 = new TH1F("h10","Phi(QT,PT) Dist, QT<5 GeV/c, Mixed GEN",100,min,max);
	TH1F* h11 = new TH1F("h11","Phi(QT,PT) Dist, 5<QT<10 GeV/c, Mixed GEN",100,min,max);
	TH1F* h12 = new TH1F("h12","Phi(QT,PT) Dist, QT<10 GeV/c, Mixed GEN",100,min,max);

	TH1F* h13 = new TH1F("h13","Phi(QT,PT) Dist, QT All, Initial GEN",100,min,max);
	TH1F* h14 = new TH1F("h14","Phi(QT,PT) Dist, QT<5 GeV/c, Initial GEN",100,min,max);
	TH1F* h15 = new TH1F("h15","Phi(QT,PT) Dist, 5<QT<10 GeV/c, Initial GEN",100,min,max);
	TH1F* h16 = new TH1F("h16","Phi(QT,PT) Dist, QT<10 GeV/c, Initial GEN",100,min,max);

	nEvents = dijetTree_DATA->GetEntries();
	Int_t mixingNum = forMixingQuota;
	Float_t vz1 = 0;
	Float_t vz2 = 0;

	Bool_t leftSide = false;
	Bool_t rightSide = false;

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

	//Mixed data, nominal cuts
//	nEvents = 5000;
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
		if(djObj.nJet!=2 || abs(djObj.eta1)>1.8 || djObj.pt1<20 || abs(djObj.eta2)>1.8 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;
		BRP =  rapidityGapAlgorithm("left",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		FRP =  rapidityGapAlgorithm("right",etaEdg,trkPt,trkEta,ptThreshold,nTrks);		                           
		vz1 = event.vz;
		if( (BRP>1.2 && BRP>FRP) || (FRP>1.2 && FRP>BRP) ) continue;
		for(Long64_t j=i+1; j<nEvents-20; j++){
			if(mixingNum==0) continue;
			dijetTree_DATA->GetEntry(j);
			if(i==j || djObj.nJet!=2 || abs(djObj.eta1)>1.8 || djObj.pt1<20 || abs(djObj.eta2)>1.8 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;
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
			if( (BRP>1.2 && BRP>FRP) || (FRP>1.2 && FRP>BRP) ) continue;
			if( abs(vz1-vz2)>3 ) continue;
			mixingNum--;
			jetplus = jet1a+jet2b;
//	       	cout<<jet1a.E()<<" "<<jet1a.Px()<<" "<<jet1a.Py()<<" "<<jet1a.Pz()<<" "<<jet2b.E()<<" "<<jet2b.Px()<<" "<<jet2b.Py()<<" "<<jet2b.Pz()<<endl;
        	//From 4-vectors to 2-vectors
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
			h1->Fill(anglePerp);
			if(jetplus.Pt()<5){
				h2->Fill(anglePerp);
			}
			if(5<jetplus.Pt() && jetplus.Pt()<10){
				h3->Fill(anglePerp);
			}
			if(jetplus.Pt()<10){
				h4->Fill(anglePerp);
			}
		}
		mixingNum=forMixingQuota;
	}
	//The pure data, nominal cuts
	nEvents=dijetTree_DATA->GetEntries();
	for(Long64_t i=0; i<nEvents; i++){
		matched=0;
//		cout<<"data lrg "<<1.0*i/nEvents<<endl;
		dijetTree_DATA->GetEntry(i);
		jet1a.SetPtEtaPhiE(djObj.pt1,djObj.eta1,djObj.phi1,djObj.e1);
		jet2a.SetPtEtaPhiE(djObj.pt2,djObj.eta2,djObj.phi2,djObj.e2);
		if(djObj.nJet!=2 || abs(djObj.eta1)>1.8 || djObj.pt1<20 || abs(djObj.eta2)>1.8 || djObj.pt2<15 || djObj.mass<35 || djObj.dphi<2) continue;
		BRP =  rapidityGapAlgorithm("left",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		FRP =  rapidityGapAlgorithm("right",etaEdg,trkPt,trkEta,ptThreshold,nTrks);
		if( (BRP>1.2 && BRP>FRP) || (FRP>1.2 && FRP>BRP) ) continue;
		if(jet1a.E()<jet2a.E()){
			TLorentzVector v;
			v = jet2a;
			jet2a = jet1a;
			jet1a = v;
		}
		jetplus = jet1a+jet2a;
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

		h5->Fill(anglePerp);
		if(jetplus.Pt()<5){
			h6->Fill(anglePerp);
		}
		if(5<jetplus.Pt() && jetplus.Pt()<10){
			h7->Fill(anglePerp);
		}
		if(jetplus.Pt()<10){
			h8->Fill(anglePerp);
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

//	nEvents = 5000;
	for(Long64_t i=0; i<nEvents; i++){
		dijetTree_GEN->GetEntry(i);
		cout<<"mixed mc:"<<1.0*i/nEvents<<endl;
		jet1a.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);
		jet2a.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);
		if( abs(djObjGen.eta1)>1.8 || djObjGen.pt1<20 || abs(djObjGen.eta2)>1.8 || djObjGen.pt2<15 || djObjGen.mass<35 || djObjGen.dphi<2) continue;
		BRP =  rapidityGapAlgorithmGEN("left",etaEdg,ptGen,etaGen,ptThreshold);
		FRP =  rapidityGapAlgorithmGEN("right",etaEdg,ptGen,etaGen,ptThreshold);
		if( (BRP>1.2 && BRP>FRP) || (FRP>1.2 && FRP>BRP) ) continue;
		vz1 = event.vz;
		for(Long64_t j=i+1; j<nEvents; j++){
			if(mixingNum==0) continue;
			dijetTree_GEN->GetEntry(j);
			if( abs(djObjGen.eta1)>1.8 || djObjGen.pt1<20 || abs(djObjGen.eta2)>1.8 || djObjGen.pt2<15 || djObjGen.mass<35 || djObjGen.dphi<2) continue;
			BRP =  rapidityGapAlgorithmGEN("left",etaEdg,ptGen,etaGen,ptThreshold);
			FRP =  rapidityGapAlgorithmGEN("right",etaEdg,ptGen,etaGen,ptThreshold);
			if( (BRP>1.2 && BRP>FRP) || (FRP>1.2 && FRP>BRP) ) continue;
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
//cout<<jet1a.E()<<" "<<jet1a.Px()<<" "<<jet1a.Py()<<" "<<jet1a.Pz()<<" "<<jet2b.E()<<" "<<jet2b.Px()<<" "<<jet2b.Py()<<" "<<jet2b.Pz()<<endl;
			jetplusGen = jet1a+jet2b;
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

			h9->Fill(anglePerpGen);
			if(jetplusGen.Pt()<5){
				h10->Fill(anglePerpGen);
			}
			if(5<jetplusGen.Pt() && jetplusGen.Pt()<10){
				h11->Fill(anglePerpGen);
			}
			if(jetplusGen.Pt()<10){
				h12->Fill(anglePerpGen);
			}			
		}
		mixingNum=forMixingQuota;
	}
	Int_t counter = 0;
	nEvents=dijetTree_GEN->GetEntries();
	for(Long64_t i=0; i<nEvents; i++){
		dijetTree_GEN->GetEntry(i);
		if( abs(djObjGen.eta1)>1.8 || djObjGen.pt1<20 || abs(djObjGen.eta2)>1.8 || djObjGen.pt2<15 || djObjGen.mass<35 || djObjGen.dphi<2) continue;
		BRP =  rapidityGapAlgorithmGEN("left",etaEdg,ptGen,etaGen,ptThreshold);
		FRP =  rapidityGapAlgorithmGEN("right",etaEdg,ptGen,etaGen,ptThreshold);
//		From early march, what John Martens said as a benchmark
//		if( BRP<0.9 && BRP>FRP) continue;
		if( (BRP>1.2 && BRP>FRP) || (FRP>1.2 && FRP>BRP) ) continue;
		jet1a.SetPtEtaPhiE(djObjGen.pt1,djObjGen.eta1,djObjGen.phi1,djObjGen.e1);
		jet2a.SetPtEtaPhiE(djObjGen.pt2,djObjGen.eta2,djObjGen.phi2,djObjGen.e2);
//cout<<jet1a.E()<<" "<<jet1a.Px()<<" "<<jet1a.Py()<<" "<<jet1a.Pz()<<" "<<jet2a.E()<<" "<<jet2a.Px()<<" "<<jet2a.Py()<<" "<<jet2a.Pz()<<endl;
		if(jet1a.E()<jet2a.E()){
			TLorentzVector v;
			v = jet2a;
			jet2a = jet1a;
			jet1a = v;
		}

		jetplusGen = jet1a+jet2a;
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

		h13->Fill(anglePerpGen);
		if(jetplusGen.Pt()<5){
			h14->Fill(anglePerpGen);
		}
		if(5<jetplusGen.Pt() && jetplusGen.Pt()<10){
			h15->Fill(anglePerpGen);
		}
		if(jetplusGen.Pt()<10){
			h16->Fill(anglePerpGen);
		}
	}

	gStyle->SetPadGridX(true);
	gStyle->SetPadGridY(true);
	gStyle->SetOptStat(0);
	TFile* outputFile = new TFile("objects/roots/g2_dijetPhiCent.root","RECREATE");

	h1->Scale(1/h1->GetEntries());
	h2->Scale(1/h2->GetEntries());
	h3->Scale(1/h3->GetEntries());
	h4->Scale(1/h4->GetEntries());
	h5->Scale(1/h5->GetEntries());
	h6->Scale(1/h6->GetEntries());
	h7->Scale(1/h7->GetEntries());
	h8->Scale(1/h8->GetEntries());
	h9->Scale(1/h9->GetEntries());
	h10->Scale(1/h10->GetEntries());
	h11->Scale(1/h11->GetEntries());
	h12->Scale(1/h12->GetEntries());
	h13->Scale(1/h13->GetEntries());
	h14->Scale(1/h14->GetEntries());
	h15->Scale(1/h15->GetEntries());
	h16->Scale(1/h16->GetEntries());

	h1->Write();
	h2->Write();
	h3->Write();
	h4->Write();
	h5->Write();
	h6->Write();
	h7->Write();
	h8->Write();
	h9->Write();
	h10->Write();
	h11->Write();
	h12->Write();
	h13->Write();
	h14->Write();
	h15->Write();
	h16->Write();

	TH1F* p1b = getHistDifference(h5,h1);
	TH1F* p2b = getHistDifference(h6,h2);
	TH1F* p3b = getHistDifference(h7,h3);
	TH1F* p4b = getHistDifference(h8,h4);
	p1b->SetTitle("Subbed Result, Data, QT All, Nominal Cuts");
	p2b->SetTitle("Subbed Result, Data,  QT<5 GeV/c, Nominal Cuts");
	p3b->SetTitle("Subbed Result, Data, 5<QT<10 GeV/c, Nominal Cuts");
	p4b->SetTitle("Subbed Result, Data, QT<10 GeV/c, Nominal Cuts");


	TH1F* p5b = getHistDifference(h13,h9);
	TH1F* p6b = getHistDifference(h14,h10);
	TH1F* p7b = getHistDifference(h15,h11);
	TH1F* p8b = getHistDifference(h16,h12);	
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

	outputFile->Save();
	outputFile->Close();
}
