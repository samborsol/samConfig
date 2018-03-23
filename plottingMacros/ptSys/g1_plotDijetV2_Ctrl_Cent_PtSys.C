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

void g1_plotDijetV2_Ctrl_Cent_PtSys(){

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
	TFile* f1 = new TFile("objects/roots/ptsys/g1_dijetV2.root");
	TFile* f2 = new TFile("objects/roots/ptsys/g1_dijetV2Cent.root");
	TFile* f3 = new TFile("objects/roots/ptsys/g1_dijetRVal.root");
	TFile* f4 = new TFile("objects/roots/ptsys/g1_dijetRValCent.root");


	//Final A
	TCanvas * c1 = new TCanvas("c1", "c1", 800, 800);
	TH1D* h1 = (TH1D*)f2->Get("p2b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	TH1D* h2 = (TH1D*)f2->Get("p6b");
	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kGreen);
	TProfile* p18 = (TProfile*)f4->Get("p18");
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
    gr->Draw("a2");
    h2->Draw("same");
   	h1->Draw("same");
	TPaveText* tx0 = new TPaveText(0.201, 0.90, 0.319, 1.0, "NDC");
	SetTPaveTxt(tx0, 25);
	tx0->AddText("#bf{CMS} #it{Preliminary}");
	tx0->Draw("same");
	TPaveText* tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("Q_{T}<5 GeV/c");
	tx1->Draw();
	TPaveText* tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	TPaveText* tx4 = new TPaveText(0.601, 0.90, 0.919, 1.0, "NDC");
	SetTPaveTxt(tx4, 25);
	tx4->AddText("Pb+Pb 0.38 nb^{-1} (5.02 TeV)");
	tx4->Draw();
	gr->SetMaximum(1.5);
	gr->SetMinimum(-1.5);
	gr->GetYaxis()->SetTitle("V_{2}");
	gr->GetXaxis()->SetTitle("PT (GeV/c))");
	TLegend * leg1 = new TLegend(0.74, 0.75, 1.0, 0.83);
	SetLegend(leg1, 22);
	leg1->AddEntry(h1,"DATA","p");
	leg1->AddEntry(h2,"RAPGAP","p");
	leg1->Draw();
	c1->Update();
	c1->RedrawAxis();
	c1->Draw();
	c1->Print("PLOTS/CENT/pdf/v2_pt_qtu5_final.pdf");
	c1->Print("PLOTS/CENT/png/v2_pt_qtu5_final.png");

	//Final B
	TCanvas * c2 = new TCanvas("c2", "c2", 800, 800);
	h1 = (TH1D*)f2->Get("p3b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	h2 = (TH1D*)f2->Get("p7b");
	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kGreen);
	p18 = (TProfile*)f4->Get("p19");
	p18h = p18->ProjectionX("p18h");
	h1->Multiply(p18h);
	p18h->SetTitle("p18h");
	Double_t y2[5]  = {h1->GetBinContent(1),h1->GetBinContent(2),h1->GetBinContent(3),h1->GetBinContent(4),h1->GetBinContent(5)};
   	gr = new TGraphErrors(5,x,y2,ex,ey);
   	gr->SetFillColor(4);
  	gr->SetFillStyle(3010);
    gr->Draw("a2");
    h2->Draw("same");
   	h1->Draw("same");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("5<Q_{T}<10 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	gr->SetMaximum(1.5);
	gr->SetMinimum(-1.5);
	gr->GetYaxis()->SetTitle("V_{2}");
	gr->GetXaxis()->SetTitle("PT (GeV/c))");
	leg1->Draw();
	c2->Update();
	c2->RedrawAxis();
	c2->Draw();
	c2->Print("PLOTS/CENT/pdf/v2_pt_qta5u10_final.pdf");
	c2->Print("PLOTS/CENT/png/v2_pt_qta5u10_final.png");

	//Final C
	TCanvas* c3 = new TCanvas("c3","c3",800,800);
	h1 = (TH1D*)f2->Get("p1b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	h2 = (TH1D*)f2->Get("p5b");
	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kGreen);
	p18 = (TProfile*)f4->Get("p17");
	p18h = p18->ProjectionX("p18h");
	h1->Multiply(p18h);
	p18h->SetTitle("p18h");
	Double_t y3[5]  = {h1->GetBinContent(1),h1->GetBinContent(2),h1->GetBinContent(3),h1->GetBinContent(4),h1->GetBinContent(5)};
   	gr = new TGraphErrors(5,x,y3,ex,ey);
   	gr->SetFillColor(4);
  	gr->SetFillStyle(3010);
    gr->Draw("a2");
    h2->Draw("same");
   	h1->Draw("same");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("No QT Cut");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	gr->SetMaximum(1.5);
	gr->SetMinimum(-1.5);
	gr->GetYaxis()->SetTitle("V_{2}");
	gr->GetXaxis()->SetTitle("PT (GeV/c))");
	leg1->Draw();
	c3->Update();
	c3->RedrawAxis();
	c3->Draw();
	c3->Print("PLOTS/CENT/pdf/v2_pt_allQt_final.pdf");
	c3->Print("PLOTS/CENT/png/v2_pt_allQt_final.png");


	//Subbed A
	TCanvas* c4 = new TCanvas("c4","c4",800,800);
	h1 = (TH1D*)f2->Get("p2b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("QT<5 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c))");
	leg1->Draw();
	c4->Update();
	c4->RedrawAxis();
	c4->Draw();
	c4->Print("PLOTS/CENT/pdf/v2_pt_qtu5_subbed.pdf");
	c4->Print("PLOTS/CENT/png/v2_pt_qtu5_subbed.png");

	//Subbed B
	TCanvas* c5 = new TCanvas("c5","c5",800,800);
	h1 = (TH1D*)f2->Get("p3b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("5<QT<10 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c5->Update();
	c5->RedrawAxis();
	c5->Draw();
	c5->Print("PLOTS/CENT/pdf/v2_pt_qta5u10_subbed.pdf");
	c5->Print("PLOTS/CENT/png/v2_pt_qta5u10_subbed.png");

	//Subbed C
	TCanvas* c6 = new TCanvas("c6","c6",800,800);
	h1 = (TH1D*)f2->Get("p1b");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("No QT Cut");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c6->Update();
	c6->RedrawAxis();
	c6->Draw();
	c6->Print("PLOTS/CENT/pdf/v2_pt_allQt_subbed.pdf");
	c6->Print("PLOTS/CENT/png/v2_pt_allQt_subbed.png");	

	//Mixed A
	TCanvas* c7 = new TCanvas("c7","c7",800,800);
	h1 = (TH1D*)f2->Get("p2a");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("QT<5 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c7->Update();
	c7->RedrawAxis();
	c7->Draw();
	c7->Print("PLOTS/CENT/pdf/v2_pt_qtu5_mixed.pdf");
	c7->Print("PLOTS/CENT/png/v2_pt_qtu5_mixed.png");	

	//Mixed B
	TCanvas* c8 = new TCanvas("c8","c8",800,800);
	h1 = (TH1D*)f2->Get("p3a");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("5<QT<10 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c))");
	leg1->Draw();
	c8->Update();
	c8->RedrawAxis();
	c8->Draw();
	c8->Print("PLOTS/CENT/pdf/v2_pt_qta5u10_mixed.pdf");
	c8->Print("PLOTS/CENT/png/v2_pt_qta5u10_mixed.png");	

	//Mixed C
	TCanvas* c9 = new TCanvas("c9","c9",800,800);
	h1 = (TH1D*)f2->Get("p1a");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("No QT Cut");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c9->Update();
	c9->RedrawAxis();
	c9->Draw();
	c9->Print("PLOTS/CENT/pdf/v2_pt_allQt_mixed.pdf");
	c9->Print("PLOTS/CENT/png/v2_pt_allQt_mixed.png");

	//Raw A
	TCanvas* c10 = new TCanvas("c10","c10",800,800);
	h1 = (TH1D*)f2->Get("p6a");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("QT<5 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c10->Update();
	c10->RedrawAxis();
	c10->Draw();
	c10->Print("PLOTS/CENT/pdf/v2_pt_qtu5_raw.pdf");
	c10->Print("PLOTS/CENT/png/v2_pt_qtu5_raw.png");

	//Raw B
	TCanvas* c11 = new TCanvas("c11","c11",800,800);
	h1 = (TH1D*)f2->Get("p7a");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("5<QT<10 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c11->Update();
	c11->RedrawAxis();
	c11->Draw();
	c11->Print("PLOTS/CENT/pdf/v2_pt_qta5u10_raw.pdf");
	c11->Print("PLOTS/CENT/png/v2_pt_qta5u10_raw.png");

	//Raw C
	TCanvas* c12 = new TCanvas("c12","c12",800,800);
	h1 = (TH1D*)f2->Get("p5a");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("No QT Cut");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	leg1->Draw();
	c12->Update();
	c12->RedrawAxis();
	c12->Draw();
	c12->Print("PLOTS/CENT/pdf/v2_pt_allQt_raw.pdf");
	c12->Print("PLOTS/CENT/png/v2_pt_allQt_raw.png");		


	//R-Value A
	TCanvas* c13 = new TCanvas("c13","c13",800,800);
	p18 = (TProfile*)f4->Get("p18");
	h1 = p18->ProjectionX("p18h");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("QT<5 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("R-Value");
	h1->GetXaxis()->SetTitle("PT (GeV/c))");
	//leg1->Draw();
	c13->Update();
	c13->RedrawAxis();
	c13->Draw();
	c13->Print("PLOTS/CENT/pdf/rval_v2_pt_qtu5.pdf");
	c13->Print("PLOTS/CENT/png/rval_v2_pt_qtu5.png");


	//R-Value B
	TCanvas* c14 = new TCanvas("c14","c14",800,800);
	p18 = (TProfile*)f4->Get("p19");
	h1 = p18->ProjectionX("p18h");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("5<QT<10 GeV/c");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("R-Value");
	h1->GetXaxis()->SetTitle("PT (GeV/c))");
	//leg1->Draw();
	c14->Update();
	c14->RedrawAxis();
	c14->Draw();
	c14->Print("PLOTS/CENT/pdf/rval_v2_pt_qta5u10.pdf");
	c14->Print("PLOTS/CENT/png/rval_v2_pt_qta5u10.png");

	//R-Value C
	TCanvas* c15 = new TCanvas("c15","c15",800,800);
	p18 = (TProfile*)f4->Get("p17");
	h1 = p18->ProjectionX("p18h");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
   	h1->Draw("");
	tx0->Draw("same");
	tx1 = new TPaveText(0.601, 0.848, 0.819, 0.9, "NDC");
	SetTPaveTxt(tx1, 25);
	tx1->AddText("No QT Cut");
	tx1->Draw();
	tx3 = new TPaveText(0.201, 0.848, 0.319, 0.9, "NDC");
	SetTPaveTxt(tx3, 30);
	tx3->AddText("Central");
	tx3->Draw();
	tx4->Draw();
	h1->SetMaximum(1.5);
	h1->SetMinimum(-1.5);
	h1->GetYaxis()->SetTitle("R-Value");
	h1->GetXaxis()->SetTitle("PT (GeV/c)");
	//leg1->Draw();
	c15->Update();
	c15->RedrawAxis();
	c15->Draw();
	c15->Print("PLOTS/CENT/pdf/rval_v2_pt_allQt.pdf");
	c15->Print("PLOTS/CENT/png/rval_v2_pt_allQt.png");

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

	//Final A
	TCanvas * c16 = new TCanvas("c16", "c16", 800, 800);
	h1 = (TH1D*)f1->Get("hQTDataSub");
	h1->SetMarkerStyle(20);
	h1->SetMarkerColor(kRed);
	h2 = (TH1D*)f1->Get("hQTGenSub");
	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kGreen);
	p18 = (TProfile*)f3->Get("p25");
	p18h = p18->ProjectionX("p18h");
	h1->Multiply(p18h);
	h1->GetYaxis()->SetTitle("V_{2}");
	h1->GetXaxis()->SetTitle("QT (GeV/c))");
	h1->SetMinimum(0);
	h1->SetMaximum(1);
 	h1->Draw("");
   	h2->Draw("same");
	tx0->Draw("same");
	tx1->Draw();
	tx3->Draw();
	tx4->Draw();
	leg1->Draw();
	c16->Update();
	c16->RedrawAxis();
	c16->Draw();
	c16->Print("PLOTS/CENT/pdf/v2_QT_final.pdf");
	c16->Print("PLOTS/CENT/png/v2_QT_final.png");

}
