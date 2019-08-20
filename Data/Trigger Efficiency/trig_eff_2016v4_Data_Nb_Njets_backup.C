void trig_eff_2016v4_Data_Nb_Njets_backup(TString var1="nb",TString var2="njets")
{
	/* Make Chain */
	TChain ch("Events");
	ch.Add("/home/cwchung95/exampleV/skim_trig/public/skim_trig_8jet_2016v4_data_*.root");
	cout << "Number of Entries : " << ch.GetEntries() << endl;

	/* Make Label, Denominators, and Trigger strings */

	TString ylabel = var2;
	TString xlabel = var1;

	// Make a independent trigger and Njet denominator component //
	TString indeno = " Sum$(Jet_pt>30 && Jet_jetId>=1 && abs(Jet_eta)<2.4)>=8 "; 
	// Make a Nb denominator component //
	TString nbdeno = " && Sum$(Jet_btagDeepB>0.6324 && abs(Jet_eta)<2.4 && Jet_pt>30 && Jet_jetId>=1)>=3 ";        
	// Make a HT denominator component //
	TString htdeno = "(HLT_IsoMu27||HLT_IsoMu24) && Sum$((Jet_pt>30 && Jet_jetId>=1 && abs(Jet_eta) < 2.4)* Jet_pt) > 700";
	htdeno = htdeno + " && Sum$((Jet_pt>30 && Jet_jetId>=1 && abs(Jet_eta) < 2.4)* Jet_pt) < 1000";
	TString deno[2];
	// Make a trigger string //
	TString trig = "(HLT_PFHT400_SixJet30_DoubleBTagCSV_p056||HLT_PFHT450_SixJet40_BTagCSV_p056)";

	/* Make elementary histogram */
	// HT //
	TString vari = var1;
	TString var[2];
	float begin[2];
	float end[2];
	float nbins[2];
	TString label;
	for(int i=0; i<2; i++){
		if(vari=="ht")
		{
			label="HT [GeV]";
			var[i] = "Sum$((Jet_pt>30 && Jet_jetId>=1 && abs(Jet_eta)<2.4)*Jet_pt)";
			begin[i] = 0;
			end[i] = 2000;
			nbins[i] = 20;
			deno[i] = indeno + nbdeno;
		}
		// Njets //
		if(vari=="njets")
		{
			label="Njets";
			var[i] = "Sum$(Jet_pt>30 && Jet_jetId>=1 && abs(Jet_eta)<2.4)";
			begin[i] = 7.5;
			end[i] = 12.5;
			nbins[i] = 5;
			deno[i] = indeno + nbdeno;
		}
		// Nb //
		if(vari=="nb")
		{
			label="Nb";
			var[i] = "Sum$(Jet_btagDeepB>0.6324 && abs(Jet_eta)<2.4 && Jet_pt>30 && Jet_jetId>=1)";
			begin[i] = 2.5;
			end[i] = 4.5;
			nbins[i] = 2;
			deno[i] = indeno + htdeno;
		}
		vari=var2;
		if(i==0){xlabel=label;}
		else{ylabel=label;}
	}

	/* Draw Histograms*/

	TH2D *h2_den = new TH2D("h2_den", "h2_den", nbins[0], begin[0], end[0], nbins[1], begin[1], end[1]);
	TH2D *h2_num = new TH2D("h2_num", "h2_num", nbins[0], begin[0], end[0], nbins[1], begin[1], end[1]);

	
	ch.Draw(Form("min(%s,%f-0.00001):min(%s,%f-0.00001)>>+h2_den", var[1].Data(), end[1], var[0].Data(), end[0]), "1*("+htdeno+")", "goff");
	ch.Draw(Form("min(%s,%f-0.00001):min(%s,%f-0.00001)>>+h2_num", var[1].Data(), end[1], var[0].Data(), end[0]), "1*(("+htdeno+")&&("+trig+"))", "goff");

	//   *********** Drawing Sequence **********  //
	
	cout << "eff="<< h2_num->Integral() << "/" <<  h2_den->Integral() << " = " <<  h2_num->Integral()/h2_den->Integral() <<  endl;
	Double_t denmax = h2_den->GetMaximum();
	Double_t denmin = h2_den->GetMinimum();
	TH2D *h1_eff = dynamic_cast<TH2D*>(h2_num->Clone("h1_eff"));
	Double_t effmax = h1_eff->GetMaximum();

	TCanvas *c = new TCanvas("c", "c", 2400, 800);
	c->Divide(3,1);
	c->cd(1);
	//c->DrawFrame(begin,0,end,1.2);                     // Setting the canvas.

	h1_eff->SetTitle("Efficiency"); 

	h1_eff->Divide(h2_num, h2_den, 1, 1, "B"); 
	h1_eff->SetLineColor(kBlue); 
	h1_eff->SetMarkerColor(kBlack); 
	h1_eff->SetMaximum(1.2);
	h1_eff->SetMinimum(0);                             // Setting Maximum and Minimum.

	h1_eff->GetYaxis()->SetTitle(ylabel);
	h1_eff->GetXaxis()->SetTitle(xlabel);
	h1_eff->GetXaxis()->SetTitleSize(0.04);
	h1_eff->GetYaxis()->SetTitleSize(0.04);
	h1_eff->GetXaxis()->SetLabelSize(0.03);
	h1_eff->GetYaxis()->SetLabelSize(0.03);            // Setting Axis.

	h1_eff->SetMarkerStyle(20); 
	h1_eff->SetMarkerSize(2); 
	h1_eff->SetStats(0);
	h1_eff->SetLineStyle(1);                           // Setting Style of Marker and Line. 

	gStyle->SetPaintTextFormat("0.2f");
	h1_eff->Draw("COLZ text e");

        c->cd(2);
        h2_den->SetTitle("Denominator");
        h2_den->SetStats(0);
	h2_den->SetMarkerSize(2);
        h2_den->Draw("colz text");

        c->cd(3);
        h2_num->SetTitle("Numerator");
        h2_num->SetStats(0);
	h2_num->SetMarkerSize(2);
        h2_num->Draw("colz text");

/*
	c->cd(2);
	h2_den->Draw("colz text");
	c->cd(3);
	h2_num->Draw("colz text");
*/	/*	TGaxis *ax1 = new TGaxis(gPad->GetUxmax(),0,gPad->GetUxmax(),1.2,0,denmax*3,10510,"+L");//gPad->GetUxmax()
		ax1->SetLabelSize(0.03);
		ax1->SetLabelFont(40);                             // Setting Label's Font and Size.

		ax1->SetTitle("Events");
		ax1->SetTitleSize(0.04);
		ax1->SetTitleFont(40);                             // Setting Title's Name, Font and Size.

		ax1->Draw("same");

	//

	h2_den->SetLineColor(kBlack);
	h2_den->SetStats(0);
	h2_den->SetTitle("");
	h2_den->SetLineStyle(2);
	h2_den->SetLineWidth(2);                            // Setting Lines and Titles.

	h2_den->GetXaxis()->SetTitle(xlabel);
	h2_den->GetXaxis()->SetTitleSize(0.05);
	h2_den->GetXaxis()->SetLabelSize(0.02);
	h2_den->GetYaxis()->SetTitle("Events");
	h2_den->GetYaxis()->SetTitleOffset(0.9);
	h2_den->GetYaxis()->SetTitleSize(0.05);
	h2_den->GetYaxis()->SetLabelSize(0.02);              // Setting Axis.

	h2_den->Scale(1/(3*denmax));                         // Rescaling The Histogram.

	h2_den->Draw("hist same");                           // Draw as Histogram graph.

	h2_num->SetLineWidth(2);
	h2_num->SetLineColor(kBlack);
	h2_num->SetFillColor(kGray);
	h2_num->SetFillStyle(3254);                           // Fill the Histogram.

	h2_num->SetStats(0);                                  // Erasing the Statistic Box.

	h2_num->Scale(1/(3*denmax));                          // Rescaling The Histogram.

	h2_num->Draw("hist same"); 

	// ***** LaTeX Options ****** //
	//TLatex *texf = new TLatex((end-begin)*0.97,h2_den->GetMaximum()*0.97,Form("%.f/%.f = %.2f",h2_num->Integral(),h1_den->Integral(),h1_num->Integral()/h1_den->Integral()));
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

	l1->AddEntry(h2_den, "Denominator", "l");
	l1->AddEntry(h2_num, "Numerator", "l");                 // Add Entries to the Legend.

	l1->Draw("same");
	*/
	TString outfile = xlabel+"2016v4_2D_Backup";
	c->Print(outfile+".pdf"); 
	c->Print(outfile+".C");                                 // Making Output File.

	TFile *newfile;
	newfile = new TFile(outfile+".root","recreate");
	h1_eff->Write();
	newfile->Close();


} 
