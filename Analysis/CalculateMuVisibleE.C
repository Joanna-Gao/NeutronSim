#include <string> 

{
  int fileNumber;
  cout << "How many ROOT files do you want to look at?" << endl;
  cin >> fileNumber;

  int distanceList [] = {0, 1, 10, 100};

  // Create a profile plot                                           
  TCanvas *can = new TCanvas("can","Muon visible energy histogram"); 
  can->Clear();                                                      

  TProfile * hprof = new TProfile("hprof",
                                  "Profile of Visible Energy to Source Distance",
                                   100,-1, 101,0,1000);

  for (int x=0; x<fileNumber; ++x)
  {
    double distance = (double)distanceList[x];


    // Open the desired ROOT file
    //string fname;                              
    //cout << "Please input a ROOT file which you need to display:" << endl;
    //cin >> fname;       //Input a ROOT file       
    string fname = 
        "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events1TeVmu"+std::to_string((int)distance)+"m.root";
    auto file = TFile::Open(fname.c_str());
                                          
    cout << "Plotting " << fname << endl;

    // Get Ntuples from file                      
    TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 
    std::vector<int> * particleID = 0;
    std::vector<double> * totalEnergy = 0; 

    InfoNtuple->SetBranchAddress("ParticleID", &particleID);
    InfoNtuple->SetBranchAddress("TotalEnergy", &totalEnergy); 

    //TH1I * h1 = new TH1I("h1", "Distribution of Visible Energy Deposited by Muons", 10000, 0, 10000);

    // Loop through events to count up the number of neutrons
    // and add to the profile plot
    int nEntries = (int)InfoNtuple->GetEntries();
    int counter = 0;
    double energy = 0; // For recording visible energy
    double meanEnergy = 0;
    const double protonThreshold = 1420;
    const double pionThreshold   = 212;
    const double kaonThreshold   = 749;

    //std::cout << nEntries << std::endl; 

    for (int i=0; i<nEntries; ++i)
    {
      InfoNtuple->GetEntry(i);
      for (int j=0; j<particleID->size(); ++j)      
      { 
        // Total particle energy visible
        if ((*particleID)[j] == 11  || // e-
            (*particleID)[j] == -11 || // e+
            (*particleID)[j] == 22  || // photons
            (*particleID)[j] == 111 )  // pi0
        { energy += (*totalEnergy)[j]; }//++counter; }

        // Kinetic energy visible if total energy greater than Cherenkov threshold
        else if ((*particleID)[j] == 2212 && // proton
                 (*totalEnergy)[j] > protonThreshold)
        {energy += ((*totalEnergy)[j] - 938);}// ++counter;}
        else if (((*particleID)[j] == 211 || (*particleID)[j] == -211) &&
                 (*totalEnergy)[j] > pionThreshold) // pi+/pi-
        {energy += ((*totalEnergy)[j] - 140);}// ++counter;}
        else if (((*particleID)[j] == 321 || (*particleID)[j] == -321) && 
                 (*totalEnergy)[j] > kaonThreshold) // K+/K-
        {energy += ((*totalEnergy)[j] - 494); }//++counter;}

      }
      
      // Changing the unit of energy from MeV to GeV
      energy = energy/1000;
      meanEnergy += energy;
      //cout << "At distance " << distance << " the total energy is " << energy << endl;
      hprof->Fill(distance, energy);
      energy = 0;
    }

    meanEnergy = meanEnergy/1000;
    cout << "Mean energy: " << meanEnergy << endl;
  }

  hprof->Draw();                                  
  hprof->GetXaxis()->SetTitle("Source Distance from the Water (m)");    
  hprof->GetYaxis()->SetTitle("Visible Muon Energy (GeV)");
                                               
  //can->SetLogy();                            
                                               
  //string imageName;                            
  //cout << "Please input a name which you like to save your image as:" << endl;
  //cin >> imageName;       //Input a name for the saved file
  //can->SaveAs(imageName.c_str());                          

  can->SaveAs("/Users/SilverJr/Documents/PhD/Geant4_Projects/NeutronSim/GeneratedPlots/VisibleEnergy.pdf");



}
