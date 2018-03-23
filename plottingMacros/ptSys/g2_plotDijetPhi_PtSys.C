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

void g2_plotDijetPhi_PtSys(){

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
	TFile* f1 = new TFile("objects/roots/ptsys/g2_dijetPhi_ptsys.root");
	TFile* f2 = new TFile("objects/roots/ptsys/g2_dijetPhiCent_ptsys.root");

	TCanvas * c = new TCanvas("c", "c", 1100, 800);
	c->Divide(3,2,0,0);

	TPad * pad1 = (TPad *) c->cd(1);
	pad1->SetTopMargin(0.12);
	TH1D* h6 = (TH1D*)f1->Get("h6");
	formatTH1D(h6,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h6->GetYaxis()->SetTitleSize(0.08);
	h6->GetYaxis()->SetTitleOffset(1.0);
	h6->Scale(1/h6->GetEntries());
	h6->SetMaximum(.07);
	TH1D* h14 = (TH1D*)f1->Get("h14");
	h14->SetMarkerStyle(21);
	h14->SetLineStyle(2);
	h14->SetLineColor(kGreen);
	h14->SetMarkerColor(kGreen);
	h14->Scale(1/h14->GetEntries());
	h14->Draw("same");
	TPaveText * tx0 = new TPaveText(0.201, 0.90, 0.319, 1.0, "NDC");
	SetTPaveTxt(tx0, 25);
	tx0->AddText("#bf{CMS} #it{Preliminary}");
	tx0->Draw("same");
	TPaveText * tx2 = new TPaveText(0.601, 0.748, 0.819, 0.8, "NDC");
	SetTPaveTxt(tx2, 25);
	tx2->AddText("Q_{T}<5 GeV/c");
	tx2->Draw();
	TPaveText * tx5 = new TPaveText(0.201, 0.748, 0.319, 0.8, "NDC");
	SetTPaveTxt(tx5, 30);
	tx5->AddText("LRG");
	tx5->Draw();   

	TPad * pad2 = (TPad *) c->cd(2);
	pad2->SetTopMargin(0.12);
	TH1D* h7 = (TH1D*)f1->Get("h7");
	formatTH1D(h7,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h7->Scale(1/h7->GetEntries());
	h7->SetMaximum(.07);
	TH1D* h15 = (TH1D*)f1->Get("h15");
	h15->SetMarkerStyle(21);
	h15->SetLineStyle(2);
	h15->SetLineColor(kGreen);
	h15->SetMarkerColor(kGreen);
	h15->Scale(1/h15->GetEntries());
	h15->Draw("same");
	TPaveText * tx3 = new TPaveText(0.201, 0.748, 0.719, 0.8, "NDC");
	SetTPaveTxt(tx3, 25);
	tx3->AddText("5<Q_{T}<10 GeV/c");
	tx3->Draw();

	TPad * pad3 = (TPad *) c->cd(3);
	pad3->SetTopMargin(0.12);
	pad3->SetRightMargin(0.01);
	TH1D* h5 = (TH1D*)f1->Get("h5");
	formatTH1D(h5,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h5->Scale(1/h5->GetEntries());
	h5->SetMaximum(.07);
	TH1D* h13 = (TH1D*)f1->Get("h13");
	h13->SetMarkerStyle(21);
	h13->SetLineStyle(2);
	h13->SetLineColor(kGreen);
	h13->SetMarkerColor(kGreen);
	h13->Scale(1/h13->GetEntries());
	h13->Draw("same");
	TPaveText * tx1 = new TPaveText(0.201, 0.90, 0.319, 1.0, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("Pb+Pb 0.38 nb^{-1} (5.02 TeV)");
	tx1->Draw();
	TLegend * leg1 = new TLegend(0.64, 0.63, 0.93, 0.79);
	SetLegend(leg1, 22);
	leg1->AddEntry(h5,"DATA","p");
	leg1->AddEntry(h13,"RAPGAP","p");
	leg1->Draw();
	TPaveText * tx4 = new TPaveText(0.201, 0.748, 0.519, 0.8, "NDC");
	SetTPaveTxt(tx4, 25);
	tx4->AddText("No Q_{T} Cut");
	tx4->Draw();

	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	TPad * pad4 = (TPad *) c->cd(4);
	pad4->SetBottomMargin(0.2);
	TH1D* h6b = (TH1D*)f2->Get("h6");
	formatTH1D(h6b,"","");
	h6b->Scale(1/h6b->GetEntries());
	h6b->SetMaximum(.07);
	TH1D* h14b = (TH1D*)f2->Get("h14");
	h14b->SetMarkerStyle(21);
	h14b->SetLineStyle(2);
	h14b->SetLineColor(kGreen);
	h14b->SetMarkerColor(kGreen);
	h14b->Scale(1/h14b->GetEntries());
	h14b->Draw("same");
	TPaveText * tx7 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx7, 30);
	tx7->AddText("Central");
	tx7->Draw();   

	TPad * pad5 = (TPad *) c->cd(5);
	pad5->SetBottomMargin(0.2);
	TH1D* h7b = (TH1D*)f2->Get("h7");
	formatTH1D(h7b,"","");
	h7b->Scale(1/h7b->GetEntries());
	h7b->SetMaximum(.07);
	TH1D* h15b = (TH1D*)f2->Get("h15");
	h15b->SetMarkerStyle(21);
	h15b->SetLineStyle(2);
	h15b->SetLineColor(kGreen);
	h15b->SetMarkerColor(kGreen);
	h15b->Scale(1/h15b->GetEntries());
	h15b->Draw("same");

	TPad * pad6 = (TPad *) c->cd(6);
	pad6->SetRightMargin(0.01);
	pad6->SetBottomMargin(0.2);

	TH1D* h5b = (TH1D*)f2->Get("h5");
	formatTH1D(h5b,"#phi(Q_{T}, P_{T})","");
	h5b->GetXaxis()->SetTitleSize(0.07);
	h5b->Scale(1/h5b->GetEntries());
	h5b->SetMaximum(.07);
	TH1D* h13b = (TH1D*)f2->Get("h13");
	h13b->SetMarkerStyle(21);
	h13b->SetLineStyle(2);
	h13b->SetLineColor(kGreen);
	h13b->SetMarkerColor(kGreen);
	h13b->Scale(1/h13b->GetEntries());
	h13b->Draw("same");

	c->Update();
	c->RedrawAxis();
	c->Draw();
	c->Print("c.pdf");
	c->Print("c.png");
}
