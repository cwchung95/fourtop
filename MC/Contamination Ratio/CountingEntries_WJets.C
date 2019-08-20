void CountingEntries_WJets(TString var="ht", float begin = 0, float end=2000, int nbins=20){


	/* Make Chain */

	TChain ch("outputTree");
	ch.Add("/home/cwchung95/4top20162017/2017/2017WJetskimmedfiles/WJetsToLNu/*.root");

	/* Make Label and Cuts */

	TString xlabel = var;

	TString cuts = "Sum$(Jet_pt>30 && Jet_jetId>1 && abs(Jet_eta)<2.4)>=8 && Sum$(Jet_btagDeepB>0.4941 && abs(Jet_eta)<2.4 && Jet_pt>30 && Jet_jetId>1)>=3 && Sum$((Jet_pt>30 && Jet_jetId>1 && abs(Jet_eta)<2.4)*Jet_pt)>=700";

	TString Muons = "Sum$(Muon_tightId && Muon_pfIsoId >= 4 && Muon_pt >= 30 && abs(Muon_eta) < 2.4) >= 1 ";

	/* Redefine var*/

	var = "Sum$((Jet_pt>30 && Jet_jetId>1 && abs(Jet_eta)<2.4)*Jet_pt)";

	/* Drawing Histograms */

	TH1D *Entries = new TH1D("Entries","Entries",nbins,begin,end);

	ch.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), "(evWeight)*("+cuts+"&&"+Muons+")","goff");

	/* Drawing Canvas */

	TCanvas *c = new TCanvas("c", "c", 1000, 800);

	c->DrawFrame(begin,0,end,1.2);

	Entries->SetTitle("HT");

	Entries->SetLineColor(kBlue);
	Entries->GetXaxis()->SetTitle(xlabel);

	Entries->Draw("hist");

	cout << "Number of Entries : " << Entries->Integral() << endl;

}

