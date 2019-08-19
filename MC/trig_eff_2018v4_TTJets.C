void trig_eff_2018v4_TTJets(TString var="nb", float begin=0, float end=2000, int nbins=20)
{
	/* Make Chain */
	TChain ch("outputTree");
	ch.Add("/home/cwchung95/exampleV/2018TTJets/skimmed_files/*");
	//ch.SetWeight(evWeight,"global");
	cout << "Number of Entries : " << ch.GetEntries() << endl;

	/* Make Label, Denominators, and Trigger strings */

	TString xlabel = var;

	// Make a independent trigger and Njet denominator component //
	TString indeno = " Sum$(Jet_pt>40 && abs(Jet_eta)<2.4)>=8 "; 
	// Make a Nb denominator component //
	TString nbdeno = " && Sum$(Jet_btagDeepB>0.4184 && abs(Jet_eta)<2.4 && Jet_pt>40)>=2 ";        
	// Make a HT denominator component //
	TString htdeno = " && Sum$((Jet_pt>40 && abs(Jet_eta) < 2.4)* Jet_pt)> 700";
	TString deno;
	// Make a trigger string //
	TString trig = "(HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 || HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59)";

	/* Make elementary histogram */
	// HT //
	if(var=="ht")
	{
		xlabel.ReplaceAll("ht","HT [GeV]");
		var = "Sum$((Jet_pt && abs(Jet_eta)<2.4)*Jet_pt)";
		begin = 0;
		end = 2000;
		nbins = 20;
		deno = indeno + nbdeno;
	}
	// Njets //
	if(var=="njets")
	{
		xlabel.ReplaceAll("njets","Njets");
		var = "Sum$(Jet_pt>40 && abs(Jet_eta)<2.4)";
		begin = -0.5;
		end = 15.5;
		nbins = 16;
		deno = indeno;
	}
	// Nb //
	if(var == "nb")
	{
		xlabel.ReplaceAll("nb","Nb");
		var = "Sum$(Jet_btagDeepB>0.4184 && abs(Jet_eta)<2.4 && Jet_pt>40)";
		begin = -0.5;
		end = 4.5;
		nbins = 5;
		deno = indeno+htdeno;
	}

	/* Draw Histograms*/

	TH1D *h1_den = new TH1D("h1_den", "h1_den", nbins, begin, end);
	TH1D *h1_num = new TH1D("h1_num", "h1_num", nbins, begin, end);
	

	ch.Draw(Form("min(%s,%f-0.00001)>>+h1_den", var.Data(), end), "evWeight*("+deno+")", "goff");
	ch.Draw(Form("min(%s,%f-0.00001)>>+h1_num", var.Data(), end), "evWeight*("+deno+"&&"+trig+")", "goff");

	//   *********** Drawing Sequence **********  //
	
	cout << "eff="<< h1_num->Integral() << "/" <<  h1_den->Integral() << " = " <<  h1_num->Integral()/h1_den->Integral() <<  endl;
	Double_t denmax = h1_den->GetMaximum();
	Double_t denmin = h1_den->GetMinimum();
	TH1D *h1_eff = dynamic_cast<TH1D*>(h1_num->Clone("h1_eff"));
	Double_t effmax = h1_eff->GetMaximum();

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

	TString outfile = xlabel+"2018v4";
	c->Print(outfile+".pdf"); 
	c->Print(outfile+".C");                                 // Making Output File.
	
	TFile *newfile;
	newfile = new TFile(outfile+".root","recreate");
	h1_eff->Write();
	newfile->Close();


} 
