#include "../interface/cutsAndBin_bgk.h"
#include "../interface/commonUtility.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "../interface/tdrstyle.C"
#include "../interface/CMS_lumi.C"


void SetTPaveTxt( TPaveText * txtemplate, int txtsize ) {
	txtemplate->SetFillColor(0);
	txtemplate->SetBorderSize(0);
	txtemplate->SetTextFont(43);
	txtemplate->SetTextAlign(12);
	txtemplate->SetTextSize(txtsize);
}

void SetLegend( TLegend * legtemplate, int legsize ) {
	legtemplate->SetFillColor(0);
	legtemplate->SetBorderSize(0);
	legtemplate->SetTextFont(43);
	legtemplate->SetTextSize(legsize);
}

void g1_plotDijetV2_PtSys(){

	setTDRStyle();
	TString writeExtraText = true;
	TString extraText = "Preliminary";
	TString lumi_5TeV = "Pb+Pb 0.38 nb^{-1}";
	int iPeriod = 5;
	TGaxis::SetMaxDigits(3);
	int W = 600;
	int H = 600;
	int W_ref = 600;
	int H_ref = 600;
	float T = 0.08*H_ref;
	float B = 0.12*H_ref;
	float L = 0.15*W_ref;
	float R = 0.04*W_ref;
	//This file has the histograms of V2 vs PT
	TFile* f1 = new TFile("objects/roots/ptsys/g1_dijetV2_ptsys.root");
	TFile* f2 = new TFile("objects/roots/ptsys/g1_dijetV2Cent_ptsys.root");
	TFile* f3 = new TFile("objects/roots/ptsys/g1_dijetRVal_ptsys.root");
	TFile* f4 = new TFile("objects/roots/ptsys/g1_dijetRValCent_ptsys.root");

	TCanvas * c = new TCanvas("c", "c", 2100, 1500);
	c->Divide(3,1,0,0);
	//Panel one
	TH1D* h1 = (TH1D*)f1->Get("p2b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	TH1D* h2 = (TH1D*)f1->Get("p6b");
	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kGreen);
	TProfile* p18 = (TProfile*)f3->Get("p18");
	TH1D* p18h = p18->ProjectionX("p18h");
	h1->Multiply(p18h);
	p18h->SetTitle("p18h");
	Double_t x[5]  = {20.5, 25.5, 30.5, 35.5, 40.5};
   	Double_t y[5]  = {h1->GetBinContent(1),h1->GetBinContent(2),h1->GetBinContent(3),h1->GetBinContent(4),h1->GetBinContent(5)};
   	Double_t ex[5] = {1,1,1,1,1}; 
   	Double_t ey[5] = {0.022,0.023,0.022,0.028,0.035};
   	TGraphErrors* gr = new TGraphErrors(5,x,y,ex,ey);
   	gr->SetFillColor(4);
  	gr->SetFillStyle(3010);
	TPad* pad1 = (TPad *) c->cd(1);
	pad1->SetTopMargin(0.12);
    gr->Draw("a2");
    h2->Draw("same");
   	h1->Draw("same");
	TPaveText * tx0 = new TPaveText(0.201, 0.90, 0.319, 1.0, "NDC");
	SetTPaveTxt(tx0, 25);
	tx0->AddText("#bf{CMS} #it{Preliminary}");
	tx0->Draw("same");
	TPaveText * tx1 = new TPaveText(0.601, 0.748, 0.819, 0.8, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("Q_{T}<5 GeV/c");
	tx1->Draw();
	TPaveText * tx3 = new TPaveText(0.201, 0.748, 0.319, 0.8, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("LRG");
	tx3->Draw();
	gr->SetMaximum(2);
	gr->SetMinimum(-2);
	gr->GetYaxis()->SetTitle("V_{2}");
	//Panel two 
	TH1D* h3 = (TH1D*)f1->Get("p3b");
	h3->SetMarkerStyle(20);
	h3->SetMarkerColor(kRed);
	TH1D* h4 = (TH1D*)f1->Get("p7b");
	h4->SetMarkerStyle(21);
	h4->SetMarkerColor(kGreen);
	TProfile* p19 = (TProfile*)f3->Get("p19");
	TH1D* p19h = p19->ProjectionX("p19h");
	h3->Multiply(p19h);
	p19h->SetTitle("p19h");
   	Double_t y2[5]  = {h3->GetBinContent(1),h3->GetBinContent(2),h3->GetBinContent(3),h3->GetBinContent(4),h3->GetBinContent(5)};
   	gr = new TGraphErrors(5,x,y2,ex,ey);
   	gr->SetFillColor(4);
  	gr->SetFillStyle(3010);
	TPad* pad2 = (TPad *) c->cd(2);
	pad2->SetTopMargin(0.12);
    gr->Draw("a2");
    h4->Draw("same");
   	h3->Draw("same");
	TPaveText * tx4 = new TPaveText(0.201, 0.748, 0.719, 0.8, "NDC");
	SetTPaveTxt(tx4, 25);
	tx4->AddText("5<Q_{T}<10 GeV/c");
	tx4->Draw();
	gr->SetMaximum(2);
	gr->SetMinimum(-2);

	//Panel three
	TH1D* h5 = (TH1D*)f1->Get("p1b");
	h5->SetMarkerStyle(20);
	h5->SetMarkerColor(kRed);
	TH1D* h6 = (TH1D*)f1->Get("p5b");
	h6->SetMarkerStyle(21);
	h6->SetMarkerColor(kGreen);
	TProfile* p17 = (TProfile*)f3->Get("p17");
	TH1D* p17h = p17->ProjectionX("p17h");
	h5->Multiply(p17h);
	p19h->SetTitle("p19h");
   	Double_t y3[5]  = {h5->GetBinContent(1),h5->GetBinContent(2),h5->GetBinContent(3),h5->GetBinContent(4),h5->GetBinContent(5)};
   	gr = new TGraphErrors(5,x,y3,ex,ey);
   	gr->SetFillColor(4);
  	gr->SetFillStyle(3010);
	TPad* pad3 = (TPad *) c->cd(3);
	pad3->SetTopMargin(0.12);
	pad3->SetRightMargin(0.01);
    gr->Draw("a2");
    h6->Draw("same");
   	h5->Draw("same");
	TPaveText * tx5 = new TPaveText(0.201, 0.9, 0.319, 1.0, "NDC");
	SetTPaveTxt(tx5, 25);
	tx5->AddText("Pb+Pb 0.38 nb^{-1} (5.02 TeV)");
	tx5->Draw();
	TLegend * leg1 = new TLegend(0.64, 0.63, 0.93, 0.79);
	SetLegend(leg1, 22);
	leg1->AddEntry(h5,"DATA","p");
	leg1->AddEntry(h6,"RAPGAP","p");
	leg1->Draw();
	TPaveText * tx6 = new TPaveText(0.201, 0.748, 0.519, 0.8, "NDC");
	SetTPaveTxt(tx6, 25);
	tx6->AddText("No Q_{T} Cut");
	tx6->Draw();
	gr->GetXaxis()->SetTitle("#phi(Q_{T}, P_{T})");
	gr->SetMaximum(2);
	gr->SetMinimum(-2);

	c->Update();
	c->RedrawAxis();
	c->Draw();
	c->Print("c.pdf");
	c->Print("c.png");
}
