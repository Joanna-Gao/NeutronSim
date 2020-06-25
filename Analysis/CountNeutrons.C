#include <string> 

{
  int fileNumber;
  cout << "How many ROOT files do you want to look at? (Max no. 9, 100m is\
 the 5th)" 
       << endl;
  cin >> fileNumber;

  string sourceEnergy;
  cout << "What energy do you want to look at? \
(Choose from 100GeV, 300GeV, 500GeV, 700GeV and 1TeV)"
       << endl;
  cin >> sourceEnergy;

  int distanceList [] = {0, 1, 10, 50, 100, 300, 500, 700, 1000};

  // Create a profile plot                                           
  TCanvas *can = new TCanvas("can","Number of Neutrons");
  can->Clear();                                                      

  TProfile * hprof = new TProfile("hprof",
                                  "No. of Neutrons Deposited Energy in Water",
                                   1002,-1, 1001,0,10000,"s");

  for (int x=0; x<fileNumber; ++x)
  {
    double distance = (double)distanceList[x];


    // Open the desired ROOT file
    //string fname;                              
    //cout << "Please input a ROOT file which you need to display:" << endl;
    //cin >> fname;       //Input a ROOT file       
    string fname =
        "~/Documents/PhD/Geant4_Projects/RootFiles/28May/"+sourceEnergy+"Muon"+
std::to_string((int)distance)+"m_HP.root";

//        "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events"+
//sourceEnergy+"mu"+std::to_string((int)distance)+"m.root";
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

  int binList [] = {2,3,12,52,102,302,502,702,1002};             
                                                
  for (int bin=0; bin<fileNumber; ++bin)                 
    cout << sourceEnergy
         << ", Bin no "                   
         << binList[bin]                        
         << ", bin content "                    
         << hprof->GetBinContent(binList[bin]) 
         << ", standard diviation is "                      
         << hprof->GetBinError(binList[bin])
         << endl;                               

  hprof->Draw();                                  
  hprof->GetXaxis()->SetTitle("Source Distance from the Water (m)");    
  hprof->GetYaxis()->SetTitle("Number of Neutrons");
                                               
  //can->SetLogx();                            
                                               
  //can->SaveAs(Form("/Users/SilverJr/Documents/PhD/Geant4_Projects/NeutronSim/GeneratedPlots/NumberOfNeutron(%s).pdf", sourceEnergy.c_str()));



}
