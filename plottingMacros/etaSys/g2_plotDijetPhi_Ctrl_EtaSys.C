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

void g2_plotDijetPhi_Ctrl_EtaSys(){

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
	TFile* f1 = new TFile("objects/roots/etasys/g2_dijetPhi_etasys.root");
	TFile* f3 = new TFile("objects/roots/etasys/g1_dijetRVal_etasys.root");

	//Raw A
	TCanvas * c1 = new TCanvas("c1", "c1", 800, 800);
	TH1D* h1 = (TH1D*)f1->Get("h6");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	TH1D* h2 = (TH1D*)f1->Get("h14");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	TPaveText * tx0 = new TPaveText(0.201, 0.90, 0.319, 1.0, "NDC");
	SetTPaveTxt(tx0, 25);
	tx0->AddText("#bf{CMS} #it{Preliminary}");
	tx0->Draw("same");
	TPaveText * tx1 = new TPaveText(0.601, 0.90, 0.919, 1.0, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("Pb+Pb 0.38 nb^{-1} (5.02 TeV)");
	tx1->Draw();
	TPaveText * tx2 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx2, 30);
	tx2->AddText("LRG");
	tx2->Draw();
	TPaveText * tx3 = new TPaveText(0.201, 0.748, 0.719, 0.8, "NDC");
	SetTPaveTxt(tx3, 25);
	tx3->AddText("Q_{T}<5 GeV/c");
	tx3->Draw();
	TLegend * leg1 = new TLegend(0.64, 0.63, 0.93, 0.79);
	SetLegend(leg1, 22);
	leg1->AddEntry(h1,"DATA","p");
	leg1->AddEntry(h2,"RAPGAP","p");
	leg1->Draw();
	c1->Update();
	c1->RedrawAxis();
	c1->Draw();
	c1->Print("PLOTS/LRG/pdf/phi_qtu5_raw.pdf");
	c1->Print("PLOTS/LRG/png/phi_qtu5_raw.png");   

	//Raw B
	TCanvas * c2 = new TCanvas("c2", "c2", 800, 800);
	h1 = (TH1D*)f1->Get("h7");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("h15");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	TPaveText * tx4 = new TPaveText(0.201, 0.748, 0.719, 0.8, "NDC");
	SetTPaveTxt(tx4, 25);
	tx4->AddText("5<Q_{T}<10 GeV/c");
	tx4->Draw();
	leg1->Draw();
	c2->Update();
	c2->RedrawAxis();
	c2->Draw();
	c2->Print("PLOTS/LRG/pdf/phi_qta5u10_raw.pdf");
	c2->Print("PLOTS/LRG/png/phi_qta5u10_raw.png");

	//Raw C
	TCanvas * c3 = new TCanvas("c3", "c3", 800, 800);
	h1 = (TH1D*)f1->Get("h5");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("h13");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	TPaveText * tx5 = new TPaveText(0.201, 0.748, 0.719, 0.8, "NDC");
	SetTPaveTxt(tx5, 25);
	tx5->AddText("No QT Cut");
	tx5->Draw();
	leg1->Draw();
	c3->Update();
	c3->RedrawAxis();
	c3->Draw();
	c3->Print("PLOTS/LRG/pdf/phi_allQt_raw.pdf");
	c3->Print("PLOTS/LRG/png/phi_allQt_raw.png");   

	//Mixed A
	TCanvas * c4 = new TCanvas("c4", "c4", 800, 800);
	h1 = (TH1D*)f1->Get("h2");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("h10");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx3->Draw();
	leg1->Draw();
	c4->Update();
	c4->RedrawAxis();
	c4->Draw();
	c4->Print("PLOTS/LRG/pdf/phi_qtu5_mixed.pdf");
	c4->Print("PLOTS/LRG/png/phi_qtu5_mixed.png"); 

	//Mixed B
	TCanvas * c5 = new TCanvas("c5", "c5", 800, 800);
	h1 = (TH1D*)f1->Get("h3");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("h11");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx4->Draw();
	leg1->Draw();
	c5->Update();
	c5->RedrawAxis();
	c5->Draw();
	c5->Print("PLOTS/LRG/pdf/phi_qta5u10_mixed.pdf");
	c5->Print("PLOTS/LRG/png/phi_qta5u10_mixed.png"); 

	//Mixed C
	TCanvas * c6 = new TCanvas("c6", "c6", 800, 800);
	h1 = (TH1D*)f1->Get("h1");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("h9");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx5->Draw();
	leg1->Draw();
	c6->Update();
	c6->RedrawAxis();
	c6->Draw();
	c6->Print("PLOTS/LRG/pdf/phi_allQt_mixed.pdf");
	c6->Print("PLOTS/LRG/png/phi_allQt_mixed.png");

	//Subbed A 
	TCanvas * c7 = new TCanvas("c7", "c7", 800, 800);
	h1 = (TH1D*)f1->Get("p2b");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("p6b");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx3->Draw();
	leg1->Draw();
	c7->Update();
	c7->RedrawAxis();
	c7->Draw();
	c7->Print("PLOTS/LRG/pdf/phi_qtu5_subbed.pdf");
	c7->Print("PLOTS/LRG/png/phi_qtu5_subbed.png");  

	//Subbed B
	TCanvas * c8 = new TCanvas("c8", "c8", 800, 800);
	h1 = (TH1D*)f1->Get("p3b");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("p7b");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx4->Draw();
	leg1->Draw();
	c8->Update();
	c8->RedrawAxis();
	c8->Draw();
	c8->Print("PLOTS/LRG/pdf/phi_qta5u10_subbed.pdf");
	c8->Print("PLOTS/LRG/png/phi_qta5u10_subbed.png");  

	//Subbed C
	TCanvas * c9 = new TCanvas("c9", "c9", 800, 800);
	h1 = (TH1D*)f1->Get("p1b");
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("p5b");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx5->Draw();
	leg1->Draw();
	c9->Update();
	c9->RedrawAxis();
	c9->Draw();
	c9->Print("PLOTS/LRG/pdf/phi_allQt_subbed.pdf");
	c9->Print("PLOTS/LRG/png/phi_allQt_subbed.png");  

	//R-Value A
	TCanvas* c10 = new TCanvas("c10","c10",800,800);
	TProfile* p18 = (TProfile*)f3->Get("p22");
	h1 = p18->ProjectionX("p18h");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	h1->SetMaximum(5);
   	h1->Draw("");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx3->Draw();
	h1->GetYaxis()->SetTitle("R-Value");
	h1->GetXaxis()->SetTitle("#phi (Q_{T},P_{T})");
	//leg1->Draw();
	c10->Update();
	c10->RedrawAxis();
	c10->Draw();
	c10->Print("PLOTS/LRG/pdf/rval_phi_qtu5.pdf");
	c10->Print("PLOTS/LRG/png/rval_phi_qtu5.png");

	//R-Value B
	TCanvas* c11 = new TCanvas("c11","c11",800,800);
	p18 = (TProfile*)f3->Get("p23");
	h1 = p18->ProjectionX("p18h");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	h1->SetMaximum(5);
   	h1->Draw("");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx4->Draw();
	h1->GetYaxis()->SetTitle("R-Value");
	h1->GetXaxis()->SetTitle("#phi (Q_{T},P_{T})");
	//leg1->Draw();
	c11->Update();
	c11->RedrawAxis();
	c11->Draw();
	c11->Print("PLOTS/LRG/pdf/rval_phi_qta5u10.pdf");
	c11->Print("PLOTS/LRG/png/rval_phi_qta5u10.png");

	//R-Value C
	TCanvas* c12 = new TCanvas("c12","c12",800,800);
	p18 = (TProfile*)f3->Get("p21");
	h1 = p18->ProjectionX("p18h");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	h1->SetMaximum(5);
   	h1->Draw("");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx5->Draw();
	h1->GetYaxis()->SetTitle("R-Value");
	h1->GetXaxis()->SetTitle("#phi (Q_{T},P_{T})");
	//leg1->Draw();
	c12->Update();
	c12->RedrawAxis();
	c12->Draw();
	c12->Print("PLOTS/LRG/pdf/rval_phi_allQt.pdf");
	c12->Print("PLOTS/LRG/png/rval_phi_allQt.png");

	//////////////////
	/////////////////
	///////////////////
	//////////////////

	//Final A 
	TCanvas * c13 = new TCanvas("c13", "c13", 800, 800);
	h1 = (TH1D*)f1->Get("p2b");
	TProfile* p19 = (TProfile*)f3->Get("p22");
	TH1D* h3 = p19->ProjectionX();
	h1->Multiply(h3);
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("p6b");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx3->Draw();
	leg1->Draw();
	c13->Update();
	c13->RedrawAxis();
	c13->Draw();
	c13->Print("PLOTS/LRG/pdf/phi_qtu5_final.pdf");
	c13->Print("PLOTS/LRG/png/phi_qtu5_final.png");  

	//Final B
	TCanvas * c14 = new TCanvas("c14", "c14", 800, 800);
	h1 = (TH1D*)f1->Get("p3b");
	p19 = (TProfile*)f3->Get("p23");
	h3 = p19->ProjectionX();
	h1->Multiply(h3);	
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("p7b");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx4->Draw();
	leg1->Draw();
	c14->Update();
	c14->RedrawAxis();
	c14->Draw();
	c14->Print("PLOTS/LRG/pdf/phi_qta5u10_final.pdf");
	c14->Print("PLOTS/LRG/png/phi_qta5u10_final.png");  

	//Final C
	TCanvas * c15 = new TCanvas("c15", "c15", 800, 800);
	h1 = (TH1D*)f1->Get("p1b");
	p19 = (TProfile*)f3->Get("p21");
	h3 = p19->ProjectionX();
	h1->Multiply(h3);
	formatTH1D(h1,"#phi (Q_{T},P_{T})","#frac{1}{N} #frac{dN}{d#phi}");
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleOffset(1.6);
	h1->SetMinimum(0);
	h1->SetMaximum(.07);
	h2 = (TH1D*)f1->Get("p5b");
	h2->SetMarkerStyle(21);
	h2->SetLineStyle(2);
	h2->SetLineColor(kGreen);
	h2->SetMarkerColor(kGreen);
	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx2->Draw();
	tx5->Draw();
	leg1->Draw();
	c15->Update();
	c15->RedrawAxis();
	c15->Draw();
	c15->Print("PLOTS/LRG/pdf/phi_allQt_final.pdf");
	c15->Print("PLOTS/LRG/png/phi_allQt_final.png");  
}
