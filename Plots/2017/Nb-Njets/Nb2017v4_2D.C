void Nb2017v4_2D()
{
//=========Macro generated from canvas: c/c
//=========  (Tue Aug 20 14:34:49 2019) by ROOT version 6.17/01
   TCanvas *c = new TCanvas("c", "c",0,23,1000,800);
   c->Range(2.25,6.875,4.75,13.125);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH2D *h1_eff = new TH2D("h1_eff","Efficiency",2,2.5,4.5,5,7.5,12.5);
   h1_eff->SetBinContent(0,0.6012658);
   h1_eff->SetBinContent(1,0.875);
   h1_eff->SetBinContent(4,0.6128683);
   h1_eff->SetBinContent(5,0.9056047);
   h1_eff->SetBinContent(6,0.9807692);
   h1_eff->SetBinContent(8,0.6308685);
   h1_eff->SetBinContent(9,0.9246988);
   h1_eff->SetBinContent(10,0.9818182);
   h1_eff->SetBinContent(12,0.6440559);
   h1_eff->SetBinContent(13,0.9621212);
   h1_eff->SetBinContent(14,0.9677419);
   h1_eff->SetBinContent(16,0.6774194);
   h1_eff->SetBinContent(17,0.9215686);
   h1_eff->SetBinContent(18,1);
   h1_eff->SetBinContent(20,0.7474747);
   h1_eff->SetBinContent(21,0.8461538);
   h1_eff->SetBinContent(22,1);
   h1_eff->SetBinError(0,0.0389535);
   h1_eff->SetBinError(1,0.1169268);
   h1_eff->SetBinError(4,0.007169354);
   h1_eff->SetBinError(5,0.01587979);
   h1_eff->SetBinError(6,0.01904496);
   h1_eff->SetBinError(8,0.008266281);
   h1_eff->SetBinError(9,0.01448212);
   h1_eff->SetBinError(10,0.01801577);
   h1_eff->SetBinError(12,0.01266149);
   h1_eff->SetBinError(13,0.01661598);
   h1_eff->SetBinError(14,0.03173351);
   h1_eff->SetBinError(16,0.02328603);
   h1_eff->SetBinError(17,0.03764642);
   h1_eff->SetBinError(20,0.04366496);
   h1_eff->SetBinError(21,0.1000683);
   h1_eff->SetMinimum(0);
   h1_eff->SetMaximum(1.2);
   h1_eff->SetEntries(11148);
   h1_eff->SetStats(0);
   h1_eff->SetContour(20);
   h1_eff->SetContourLevel(0,0);
   h1_eff->SetContourLevel(1,0.06);
   h1_eff->SetContourLevel(2,0.12);
   h1_eff->SetContourLevel(3,0.18);
   h1_eff->SetContourLevel(4,0.24);
   h1_eff->SetContourLevel(5,0.3);
   h1_eff->SetContourLevel(6,0.36);
   h1_eff->SetContourLevel(7,0.42);
   h1_eff->SetContourLevel(8,0.48);
   h1_eff->SetContourLevel(9,0.54);
   h1_eff->SetContourLevel(10,0.6);
   h1_eff->SetContourLevel(11,0.66);
   h1_eff->SetContourLevel(12,0.72);
   h1_eff->SetContourLevel(13,0.78);
   h1_eff->SetContourLevel(14,0.84);
   h1_eff->SetContourLevel(15,0.9);
   h1_eff->SetContourLevel(16,0.96);
   h1_eff->SetContourLevel(17,1.02);
   h1_eff->SetContourLevel(18,1.08);
   h1_eff->SetContourLevel(19,1.14);
   
   TPaletteAxis *palette = new TPaletteAxis(4.5125,7.5,4.625,12.5,h1_eff);
   palette->SetLabelColor(1);
   palette->SetLabelFont(42);
   palette->SetLabelOffset(0.005);
   palette->SetLabelSize(0.035);
   palette->SetTitleOffset(1);
   palette->SetTitleSize(0.035);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f9f90e");
   palette->SetFillColor(ci);
   palette->SetFillStyle(1001);
   h1_eff->GetListOfFunctions()->Add(palette,"br");

   ci = TColor::GetColor("#0000ff");
   h1_eff->SetLineColor(ci);
   h1_eff->SetMarkerStyle(20);
   h1_eff->SetMarkerSize(2);
   h1_eff->GetXaxis()->SetTitle("Nb");
   h1_eff->GetXaxis()->SetLabelFont(42);
   h1_eff->GetXaxis()->SetLabelSize(0.03);
   h1_eff->GetXaxis()->SetTitleOffset(1);
   h1_eff->GetXaxis()->SetTitleFont(42);
   h1_eff->GetYaxis()->SetTitle("Njets");
   h1_eff->GetYaxis()->SetLabelFont(42);
   h1_eff->GetYaxis()->SetLabelSize(0.03);
   h1_eff->GetYaxis()->SetTitleFont(42);
   h1_eff->GetZaxis()->SetLabelFont(42);
   h1_eff->GetZaxis()->SetLabelSize(0.035);
   h1_eff->GetZaxis()->SetTitleSize(0.035);
   h1_eff->GetZaxis()->SetTitleOffset(1);
   h1_eff->GetZaxis()->SetTitleFont(42);
   h1_eff->Draw("COLZ text e");
   
   TPaveText *pt = new TPaveText(0.3953106,0.9345349,0.6046894,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Efficiency");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
