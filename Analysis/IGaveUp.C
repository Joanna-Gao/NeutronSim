{
  int distance = 10;
  int energyNumber;
  int energyList[] = {100, 300, 500, 700, 1};

  std::cout << "How many source energies do you want to look at? (Max no. 5)"
            << std::endl;
  std::cin >> energyNumber;    

  TCanvas * c1 = new TCanvas("c1", "2D Histogram Showing Neutron Multiplicity\
 wrt Source Energy", 1000, 600);
  
  TH2D * histo = new TH2D("histo",
                          "2D Histogram Showing Neutron Multiplicity wrt\
 Source Energy",
                          15, 0, 15, 100, 50, 1050);
  for (size_t ifile = 0; ifile < energyNumber; ++ifile)
  {
    int sourceEnergy = energyList[ifile]; 

    std::string fname;

    if (energyList[ifile] != 1) 
      fname = 
        "~/Documents/PhD/Geant4_Projects/RootFiles/replot/"
        +std::to_string(sourceEnergy)+"GeVMuon"+std::to_string(distance)+"m_HP.root";
    else
      fname =
        "~/Documents/PhD/Geant4_Projects/RootFiles/replot/"
        +std::to_string(sourceEnergy)+"TeVMuon"+std::to_string(distance)+"m_HP.root";
    
    TFile *file = TFile::Open(fname.c_str());
    std::cout << "Plotting " << fname << std::endl;
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

    // Convert 1TeV to 1000GeV for plotting
    if (sourceEnergy == 1) sourceEnergy = 1000;

    for (int i=0; i<nEntries; ++i)
    {
      InfoNtuple->GetEntry(i);
      for (int j=0; j<particleID->size(); ++j)      
      { 
          if ((*particleID)[j] == 2112 && (*nCapture)[j] == 1) ++counter;
      }
      //std::cout << "no. of ncap " << (double)counter
      //         << ", source energy " << (double)sourceEnergy << '\n';
      histo->Fill((double)counter, (double)sourceEnergy);
      counter = 0;
    }
  }

  histo->GetXaxis()->SetTitle("No. of Neutron Captured");
  histo->GetYaxis()->SetTitle("Muon Energy at Source (GeV)");
  histo->GetZaxis()->SetTitle("No. of Events");

  //std::cout << "No problem before, about to plot" << std::endl;
  histo->Draw("surf3");
  c1->Update();

  c1->SaveAs("/Users/SilverJr/Documents/PhD/Geant4_Projects/2DncapHisto.pdf");
}