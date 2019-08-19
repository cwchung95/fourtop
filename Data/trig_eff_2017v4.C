#include <stdio.h>
#include <stdlib.h>

// run ranges in golden json
// 2016: 273158-284044
// 2017: 297050-306460
// 2018: 315257-325172


//** Numerator triggers: 
//2016 
//HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 
//HLT_PFHT450_SixJet40_BTagCSV_p056
//2017 
//HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 
//HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 
//HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94
//2018 
//HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94
//HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59

//** Denominator triggers: 
//HLT_IsoMu24 || HLT_IsoMu27 || HLT_IsoMu30

float tec(TString nb, TString njets);


void trig_eff_2017v4(TString var="ht", int quad=1, float begin=0, float end=2000, int nbins=20)
{
  TString nbcut = "Sum$(Jet_btagDeepB>0.4941 && abs(Jet_eta)<2.4 && Jet_pt>30)"; 
  TString njetscut = "Sum$((Jet_pt>30 && abs(Jet_eta)<2.4))";
  //
  TChain ch1("Events");
  TChain ch2("Events");
  ch1.Add("skim_trig_8jet_2017v4_data_SingleMuon_B.root");
  ch2.Add("skim_trig_8jet_2017v4_data_SingleMuon_C.root");
  ch2.Add("skim_trig_8jet_2017v4_data_SingleMuon_D.root");
  ch2.Add("skim_trig_8jet_2017v4_data_SingleMuon_E.root");
  ch2.Add("skim_trig_8jet_2017v4_data_SingleMuon_F.root");
  //ch.Add("skim_trig_2017v4_data_SingleMuon_B.root");

  //
  cout << "Nentries: " << ch1.GetEntries() + ch2.GetEntries() << endl;
  //
  TString xlabel = var;
  TString deno1="( HLT_IsoMu27 || HLT_IsoMu24 ) && Sum$(Jet_btagDeepB>0.4941 && abs(Jet_eta)<2.4 && Jet_pt>30 && Jet_jetId>1 )>=3 && Sum$(Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_jetId>1 )>=8";
  TString deno2="( HLT_IsoMu27 || HLT_IsoMu24 ) && Sum$(Jet_btagDeepB>0.4941 && abs(Jet_eta)<2.4 && Jet_pt>30 && Jet_jetId>1 )>=3 && Sum$((Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_jetId>1 )*Jet_pt)>700";
  TString deno3="( HLT_IsoMu27 || HLT_IsoMu24 ) && Sum$((Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_jetId>1 )*Jet_pt)>700 && Sum$(Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_jetId>1 )>=8";
  TString denomt="&& (sqrt(2*Muon_pt*MET_pt*(1-cos(Muon_phi-MET_phi)))*((Muon_pfIsoId>=4&&Muon_tightId&&Muon_pt>=30&&abs(Muon_eta)<2.4)?1:0))>=30 && Sum$( Muon_pt>=30 && abs(Muon_eta)<2.4 && Muon_pfIsoId>=4 && Muon_tightId )==1";
  TString deno;

  //
  if(var=="ht") 
  {
    xlabel.ReplaceAll("ht","HT [GeV]");
    var = "Sum$((Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_jetId>1 )*Jet_pt)"; 
    begin = 0;
    end = 2000;
    nbins = 20;
    deno=deno1;//+denomt;
  }
  if(var=="njets") 
  {
    xlabel.ReplaceAll("njets","Njets");
    var = "Sum$((Jet_pt>30 && abs(Jet_eta)<2.4 && Jet_jetId>1 ))";
    begin = -0.5;
    end = 15.5;
    nbins = 16;
    deno=deno2;//+denomt;
  }
  if(var=="nb") 
  {
    xlabel.ReplaceAll("nb","Nb");
    var = "Sum$(Jet_btagDeepB>0.4941 && abs(Jet_eta)<2.4 && Jet_pt>30 && Jet_jetId>1 )";
    begin = -0.5;
    end =4.5;
    nbins  = 5;
    deno=deno3;//+denomt;
  }
  if(var=="run") 
  {
    var   = "run";
    begin = 297050;
    end   = 306460;
    nbins  = 50;
    deno = deno1+"&&"+deno2;
  }
  //
  TH1D *h1_den = new TH1D("h1_den", "h1_den", nbins, begin, end); 
  TH1D *h1_num = new TH1D("h1_num", "h1_num", nbins, begin, end); 

  //
  TString trig1="&& ( HLT_PFHT380_SixJet32_DoubleBTagCSV_p075 || HLT_PFHT430_SixJet40_BTagCSV_p080 )";
  TString trig2="&& ( HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 || HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0 )";
  TString trig;
  TString pdfname;
   
  //  deno1="( HLT_IsoMu27 || HLT_IsoMu24 )";
  //  ch.SetWeight(tec(nbcut.Data(),njetscut.Data()));
  //  cout<<tec(nbcut.Data(),njetscut.Data())<<endl;

  ch1.Draw(Form("min(%s,%f-0.000001)>>h1_den",var.Data(),end), "((("+nbcut+"==3&&"+njetscut+"==8))+"+"(("+nbcut+"==3&&"+njetscut+"==9))+"+"(("+nbcut+">=4&&"+njetscut+"==8))+"+"(("+nbcut+">=4&&"+njetscut+">=9))+"+"(("+nbcut+"==3&&"+njetscut+">=10))"+")*"+"("+deno+")", "goff");
  ch2.Draw(Form("min(%s,%f-0.000001)>>h1_den",var.Data(),end), "((("+nbcut+"==3&&"+njetscut+"==8))+"+"(("+nbcut+"==3&&"+njetscut+"==9))+"+"(("+nbcut+">=4&&"+njetscut+"==8))+"+"(("+nbcut+">=4&&"+njetscut+">=9))+"+"(("+nbcut+"==3&&"+njetscut+">=10))"+")*"+"("+deno+")", "goff");
  ch1.Draw(Form("min(%s,%f-0.000001)>>h1_num",var.Data(),end), "((("+nbcut+"==3&&"+njetscut+"==8)/0.91)+"+"(("+nbcut+"==3&&"+njetscut+"==9)/0.92)+"+"(("+nbcut+">=4&&"+njetscut+"==8)/0.98)+"+"(("+nbcut+">=4&&"+njetscut+"==9)/0.98)+"+"(("+nbcut+">=4&&"+njetscut+">=10)/0.98)+"+"(("+nbcut+"==3&&"+njetscut+">=10)/0.94)"+")*"+"("+deno+trig1+")", "goff"); 
  ch2.Draw(Form("min(%s,%f-0.000001)>>h1_num",var.Data(),end), "((("+nbcut+"==3&&"+njetscut+"==8)/0.91)+"+"(("+nbcut+"==3&&"+njetscut+"==9)/0.92)+"+"(("+nbcut+">=4&&"+njetscut+"==8)/0.98)+"+"(("+nbcut+">=4&&"+njetscut+"==9)/0.98)+"+"(("+nbcut+">=4&&"+njetscut+">=10)/0.98)+"+"(("+nbcut+"==3&&"+njetscut+">=10)/0.94)"+")*"+"("+deno+trig2+")", "goff"); 

  //ch.Draw(Form("min(%s,%f-0.000001)>>h1_den",var.Data(),end),"("+deno+")", "goff");
  //ch.Draw(Form("min(%s,%f-0.000001)>>h1_num",var.Data(),end),"("+deno+trig+")", "goff"); 
  
  cout << "eff="<< h1_num->Integral() << "/" <<  h1_den->Integral() << " = " <<  h1_num->Integral()/h1_den->Integral() <<  endl;
  Double_t denmax = h1_den->GetMaximum();
  Double_t denmin = h1_den->GetMinimum();
  TH1D *h1_eff = dynamic_cast<TH1D*>(h1_num->Clone("h1_eff"));
  Double_t effmax = h1_eff->GetMaximum();

  
  
  //  *********** Drawing Sequence **********  //
  
  
  TCanvas *c = new TCanvas("c", "c", 1000, 800);
  //c->Divide(2,1);
  //c->cd(1);
  c->DrawFrame(begin,0,end,1.2);                     // Setting the canvas.
  
  h1_eff->SetTitle("Efficiency"); 
  
  h1_eff->Divide(h1_num, h1_den, 1, 1, "B"); 
  h1_eff->SetLineColor(kBlue); 
  h1_eff->SetMarkerColor(kBlue); 
  h1_eff->SetMaximum(1.2);
  h1_eff->SetMinimum(0);                             // Setting Maximum and Minimum.

  h1_eff->GetYaxis()->SetTitle("Efficiency");
  h1_eff->GetXaxis()->SetTitle(xlabel);
  h1_eff->GetXaxis()->SetTitleSize(0.04);
  h1_eff->GetYaxis()->SetTitleSize(0.04);
  h1_eff->GetXaxis()->SetLabelSize(0.03);
  h1_eff->GetYaxis()->SetLabelSize(0.03);            // Setting Axis.
  
  h1_eff->SetMarkerStyle(20); 
  h1_eff->SetMarkerSize(0.5); 
  h1_eff->SetStats(0);
  h1_eff->SetLineStyle(1);                           // Setting Style of Marker and Line. 
  
  h1_eff->Draw("");
 
  //

  TGaxis *ax1 = new TGaxis(gPad->GetUxmax(),0,gPad->GetUxmax(),1.2,0,denmax*3,10510,"+L");//gPad->GetUxmax()
  ax1->SetLabelSize(0.03);
  ax1->SetLabelFont(40);                             // Setting Label's Font and Size.
  
  ax1->SetTitle("Events");
  ax1->SetTitleSize(0.04);
  ax1->SetTitleFont(40);                             // Setting Title's Name, Font and Size.
  
  ax1->Draw("same");
  
  //

  h1_den->SetLineColor(kBlack);
  h1_den->SetStats(0);
  h1_den->SetTitle("");
  h1_den->SetLineStyle(2);
  h1_den->SetLineWidth(2);                            // Setting Lines and Titles.
  
  h1_den->GetXaxis()->SetTitle(xlabel);
  h1_den->GetXaxis()->SetTitleSize(0.05);
  h1_den->GetXaxis()->SetLabelSize(0.02);
  h1_den->GetYaxis()->SetTitle("Events");
  h1_den->GetYaxis()->SetTitleOffset(0.9);
  h1_den->GetYaxis()->SetTitleSize(0.05);
  h1_den->GetYaxis()->SetLabelSize(0.02);              // Setting Axis.
  
  h1_den->Scale(1/(3*denmax));                         // Rescaling The Histogram.
  
  h1_den->Draw("hist same");                           // Draw as Histogram graph.
  
  h1_num->SetLineWidth(2);
  h1_num->SetLineColor(kBlack);
  h1_num->SetFillColor(kGray);
  h1_num->SetFillStyle(3254);                           // Fill the Histogram.

  h1_num->SetStats(0);                                  // Erasing the Statistic Box.

  h1_num->Scale(1/(3*denmax));                          // Rescaling The Histogram.
  
  h1_num->Draw("hist same"); 

  // ***** LaTeX Options ****** //
  //TLatex *texf = new TLatex((end-begin)*0.97,h1_den->GetMaximum()*0.97,Form("%.f/%.f = %.2f",h1_num->Integral(),h1_den->Integral(),h1_num->Integral()/h1_den->Integral()));
  //texf->SetTextColor(kBlack);
  //texf->SetTextAlign(31); 
  //texf->SetTextSize(0.02);
  //texf->Draw();
  
  //

  TLegend *l1 = new TLegend(0.7, 0.85, 0.9, 0.9);        // Making Legends.
  
  //l1->SetNColumns(1);
  //l1->SetFillColor(kGray);
  l1->SetBorderSize(1);
  l1->SetFillStyle(3245);                                 // Fill the Legend Box.

  l1->SetTextFont(42);
  l1->SetTextAlign(22);
  l1->SetTextSize(0.02);                                  // Setting Text Size, Font, and Align.

  l1->SetFillColor(kGray);
  l1->SetLineColor(kBlack);
  l1->SetShadowColor(kWhite);                             // Legend Box Styling Options.
  
  l1->AddEntry(h1_den, "Denominator", "l");
  l1->AddEntry(h1_num, "Numerator", "l");                 // Add Entries to the Legend.
  
  l1->Draw("same");

  TString outfile = xlabel+pdfname+"2017v4_Others";
  c->Print(outfile+".pdf");                              // Making Output File.
  c->Print(outfile+".C");                                // Making Output File.
  TFile *newfile;
  newfile = new TFile(outfile+".root","recreate");

  h1_eff->Write();                                      // Making Output File.
  newfile->Close();
}


float tec(TString nb, TString njets){
  float ret;
  if(nb=="3"){
    if(njets=="8"){
      ret = 1./0.92;
    }
    if(njets=="9"){
      ret = 1./0.96;
    }
    if(njets>="10"){
      ret = 1./1.00;
    }
  }
  if(nb>="4"){
    if(njets=="8"){
      ret = 1./0.99;
    }
    if(njets=="9"){
      ret = 1./1.00;
    }
    if(njets>="10"){
      ret = 1./1.00; 
    }
  }
  return ret;
}
