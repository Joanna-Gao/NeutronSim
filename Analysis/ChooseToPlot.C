#include <string> 

{
  int plotWhat;
  int distanceNumber;
  string sourceEnergy;
  bool plotSameEnergy;
  int distance;
  int energyNumber;

  //int distanceList [] = {0, 1, 10, 50, 100, 300, 500, 700, 1000};
  int distanceList [] = {1, 700};
  string energyList [] = {"100GeV", "300GeV", "500GeV", "700GeV", "1TeV"};

  cout << "1 for plotting same energy different distances;\n\
2 for plotting different energies same distance." 
       << endl;
  cin >> plotWhat; 

  switch (plotWhat)
  {
    case 1:
      plotSameEnergy = true;
      cout << "How many ROOT files do you want to look at? (Max no. 9, 100m is\
 the 5th)" 
           << endl;
      cin >> distanceNumber;
      
      cout << "What energy do you want to look at? \
(Choose from 100GeV, 300GeV, 500GeV, 700GeV and 1TeV)"
           << endl;
      cin >> sourceEnergy;

      cout << "You will be looking at events with "
           << sourceEnergy
           << " energy, and source distance up to "
           << distanceList[distanceNumber]
           << " metres."
           << endl;

     break;

    case 2:
      plotSameEnergy = false;
      cout << "What distance (in metres) do you want to look at?"
           << endl;
      cin >> distance;

      cout << "How many energies do you want to look at? (Max no. 2)"
           << endl;
      cin >> energyNumber;

      cout << "You will be looking at events at distance "
           << distance
           << " metres with energy up to "
           << energyList[energyNumber]
           << " "
           << endl;

  }

  TCanvas *can = new TCanvas("can","Number of Neutrons");                                                

  //TProfile * hprof = new TProfile("hprof",
  //                                "No. of Neutrons Deposited Energy in Water",
  //                                 1002,-1, 1001,0,10000)

  std::vector<TH1D*> histos;
  auto legend = new TLegend(0.85,0.7,0.6,0.9);

  // initialise the histos based on the number of files
  for (size_t i = 0; i != (plotSameEnergy ? distanceNumber : energyNumber); ++i)
    histos.push_back(new TH1D("","", 600, 0, 600));

  cout<<"set histo works fine"<<endl;

  // loop through all the files to fill the histos
  for (size_t ifile = 0;
       ifile!=(plotSameEnergy ? distanceNumber : energyNumber);
       ++ifile)
  {
    if (plotSameEnergy)
      distance = distanceList[ifile];

    if (!plotSameEnergy)
      sourceEnergy = energyList[ifile];

    string fname =
        "~/Documents/PhD/Geant4_Projects/RootFiles/replot/"+sourceEnergy
        +"Muon"+std::to_string(distance)+"m_HP.root";

//        "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events"+
//sourceEnergy+"mu"+std::to_string((int)distance)+"m.root";
    auto file = TFile::Open(fname.c_str());
                                          
    cout << "Plotting " << fname << endl;

    // Get Ntuples from file                      
    TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 
    std::vector<int> * particleID = 0;
    std::vector<int> * nCapture = 0;

    InfoNtuple->SetBranchAddress("ParticleID", &particleID);
    InfoNtuple->SetBranchAddress("NeutronCapture", &nCapture);

    // Loop through events to count up the number of neutrons
    // and add to the profile plot
    int nEntries = (int)InfoNtuple->GetEntries();
    int counter = 0;

    for (int i=0; i<nEntries; ++i)
    {
      InfoNtuple->GetEntry(i);
      for (int j=0; j<particleID->size(); ++j)      
      { 
        if ((*nCapture)[j] == 1) ++counter;
      }
      
      //hprof->Fill((double)distance, (double)counter);
      histos[ifile]->AddBinContent(counter);
      counter = 0;
    }

    histos[ifile]->Draw("SAME");
    histos[ifile]->SetLineWidth(3);
    histos[ifile]->SetLineColor((ifile+1));
    histos[ifile]->SetStats(0);
    legend->
      AddEntry(histos[ifile], Form("Distance = %dm, Energy = %s",
                                   (int)distance, sourceEnergy.c_str()));
  }

  // extract the bin information for plotting in python because the profile
  // hist doesn't like being plot in the same canvas
  //int binList [] = {2,3,12,52,102,302,502,702,1002};             
  //                                              
  //for (int bin=0; bin<distanceNumber; ++bin)                 
  //  cout << sourceEnergy
  //       << ", Bin no "                   
  //       << binList[bin]                        
  //       << ", bin content "                    
  //       << hprof->GetBinContent(binList[bin]) 
  //       << ", standard diviation is "                      
  //       << hprof->GetBinError(binList[bin])
  //       << endl;                               

  // plot profile hist
  //hprof->Draw();                                  
  //hprof->GetXaxis()->SetTitle("Source Distance from the Water (m)");
  //hprof->GetYaxis()->SetTitle("Number of Neutrons");

  histos[0]->SetTitle("No. of Neutrons Captured in Water");
  histos[0]->GetXaxis()->SetTitle("No. of Neutrons Captured");
  histos[0]->GetYaxis()->SetTitle("No. of Events");

  can->SetLogy();
  //can->SetLogx();
  legend->Draw();
                                               
  //can->SaveAs(Form("/Users/SilverJr/Documents/PhD/Geant4_Projects/NeutronSim/GeneratedPlots/NumberOfNeutron(%s).pdf", sourceEnergy.c_str()));


}
