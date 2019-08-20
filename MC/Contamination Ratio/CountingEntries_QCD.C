void CountingEntries_QCD(TString var="ht", float begin = 0, float end=2000, int nbins=20){


	/* Make Chain */

	TChain ch1("outputTree");
	TChain ch2("outputTree");
	TChain ch3("outputTree");
	TChain ch4("outputTree");
	TChain ch5("outputTree");
	TChain ch6("outputTree");
	TChain ch7("outputTree");
	TChain ch8("outputTree");
	ch1.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_100to200/*.root");
	ch2.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_200to300/*.root");
	ch3.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_300to500/*.root");
	ch4.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_500to700/*.root");
	ch5.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_700to1000/*.root");
	ch6.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_1000to1500/*.root");
	ch7.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_1500to2000/*.root");
	ch8.Add("/home/cwchung95/4top20162017/2017/2017QCDskimmedfiles/QCD_2000toInf/*.root");

	/* Make Weight */
	
	TString weight1;
	TString weight2;
	TString weight3;
	TString weight4;
	TString weight5;
	TString weight6;
	TString weight7;
	TString weight8;
	weight1 = "27850000000./93231801.";
//	ch1.SetWeight(weight);
	weight2 = "1717000000./59427619.";
//	ch2.SetWeight(weight);
	weight3 = "351300000./60233241.";
//	ch3.SetWeight(weight);
	weight4 = "31630000./56207744.";
//	ch4.SetWeight(weight);
	weight5 = "6802000./47724800.";
//	ch5.SetWeight(weight);
	weight6 = "1206000./16595628.";
//	ch6.SetWeight(weight);
	weight7 = "98710./11634434.";
//	ch7.SetWeight(weight);
	weight8 = "20200./5941306.";
//	ch8.SetWeight(weight);
	
	/* Make Label and Cuts */

	TString xlabel = var;

	TString cuts = "Sum$(Jet_pt>40 && abs(Jet_eta)<2.4)>=8 && Sum$(Jet_btagDeepB>0.4941 && abs(Jet_eta)<2.4 && Jet_pt > 40)>=3 && Sum$((Jet_pt>40 && abs(Jet_eta)<2.4)*Jet_pt)>=700";

	TString Muons = "Sum$(Muon_tightId && Muon_pfIsoId >= 4 && Muon_pt >= 30 && abs(Muon_eta) < 2.4) >= 1 ";

	/* Redefine var*/

	var = "Sum$((Jet_pt>40 && abs(Jet_eta)<2.4)*Jet_pt)";

	/* Drawing Histograms */

	TH1D *Entries = new TH1D("Entries","Entries",nbins,begin,end);

	ch1.Draw(Form("min(%s,%f-0.000001)>>Entries", var.Data(), end), weight1+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch2.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight2+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch3.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight3+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch4.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight4+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch5.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight5+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch6.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight6+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch7.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight7+"*evWeight*("+cuts+"&&"+Muons+")","goff");
	ch8.Draw(Form("min(%s,%f-0.000001)>>+Entries", var.Data(), end), weight8+"*evWeight*("+cuts+"&&"+Muons+")","goff");

	/* Drawing Canvas */

	TCanvas *c = new TCanvas("c", "c", 1000, 800);

	c->DrawFrame(begin,0,end,1.2);

	Entries->SetTitle("HT");

	Entries->SetLineColor(kBlue);
	Entries->GetXaxis()->SetTitle(xlabel);

	Entries->Draw("hist");

	cout << "Number of Entries : " << Entries->Integral() << endl;

}

