#include <string> 

{
  int fileNumber;
  cout << "How many ROOT files do you want to look at? (Max no. 5)" << endl;
  cin >> fileNumber;

  string sourceEnergy;
  cout << "What energy do you want to look at? \
(Choose from 100GeV, 500GeV and 1TeV)"
       << endl;
  cin >> sourceEnergy;

  int distanceList [] = {0, 1, 10, 50, 100};

  // Create a profile plot                                           
  TCanvas *can = new TCanvas("can","Number of Neutrons");
  can->Clear();                                                      

  TProfile * hprof = new TProfile("hprof",
                                  "No. of Neutrons Deposited Energy in Water",
                                   102,-1, 101,0,10000);

  for (int x=0; x<fileNumber; ++x)
  {
    double distance = (double)distanceList[x];


    // Open the desired ROOT file
    //string fname;                              
    //cout << "Please input a ROOT file which you need to display:" << endl;
    //cin >> fname;       //Input a ROOT file       
    string fname =
        "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events"+
sourceEnergy+"mu"+std::to_string((int)distance)+"m.root";
    auto file = TFile::Open(fname.c_str());
                                          
    cout << "Plotting " << fname << endl;

    // Get Ntuples from file                      
    TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 
    std::vector<int> * particleID = 0;

    InfoNtuple->SetBranchAddress("ParticleID", &particleID);

    // Loop through events to count up the number of neutrons
    // and add to the profile plot
    int nEntries = (int)InfoNtuple->GetEntries();
    int counter = 0;
    
    //std::cout << nEntries << std::endl; 

    for (int i=0; i<nEntries; ++i)
    {
      InfoNtuple->GetEntry(i);
      for (int j=0; j<particleID->size(); ++j)      
      { 
        if ((*particleID)[j] == 2112) ++counter;
      }
      
      hprof->Fill(distance, (double)counter);
      counter = 0;
    }

  }

  int binList [] = {2,3,12,52,102};             
                                                
  for (int bin=0; bin<5; ++bin)                 
    cout << "100GeV, Bin no "                   
         << binList[bin]                        
         << ", bin content "                    
         << hprof->GetBinContent(binList[bin]) 
         << ", bin error "                      
         << hprof->GetBinError(binList[bin])   
         << endl;                               

  hprof->Draw();                                  
  hprof->GetXaxis()->SetTitle("Source Distance from the Water (m)");    
  hprof->GetYaxis()->SetTitle("Number of Neutrons");
                                               
  //can->SetLogx();                            
                                               
  can->SaveAs(Form("/Users/SilverJr/Documents/PhD/Geant4_Projects/NeutronSim/GeneratedPlots/NumberOfNeutron(%s).pdf", sourceEnergy.c_str()));



}
