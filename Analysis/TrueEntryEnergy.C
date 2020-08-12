#include <string> 

{
  int fileNumber;
  cout << "How many ROOT files do you want to look at? (Max no. 9)" << endl;
  cin >> fileNumber;

  string sourceEnergy;
  cout << "What energy do you want to look at? \
(Choose from 100, 300, 500, 700 GeV and 1TeV)" 
       << endl; 
  cin >> sourceEnergy;


  int distanceList [] = //{0,1,10,20,30,50,60,70,100}; // for 100 GeV
                        //{0,1,10,30,50,100,300,500,700}; // for 500 GeV
                        {0, 1, 10, 50, 100, 300, 500, 700, 1000}; // for 1 TeV

  // Create a profile plot                                           
  TCanvas *can = new TCanvas("can","Profile Plot for True Muon Entry Energy"); 
  can->Clear();                                                      

  TProfile * hprof = new TProfile("hprof",
                                  "Energy of Muon When Entering Water",
                                   1002,-1, 1001,0,1000000);

  for (int x=0; x<fileNumber; ++x)
  {
    double distance = (double)distanceList[x];


    // Open the desired ROOT file
    //string fname;                              
    //cout << "Please input a ROOT file which you need to display:" << endl;
    //cin >> fname;       //Input a ROOT file       
    string fname =
        "~/Documents/PhD/Geant4_Projects/RootFiles/replot/"+sourceEnergy+"Muon"+
std::to_string((int)distance)+"m_HP.root";


//        "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events"+
//sourceEnergy+"mu"+std::to_string((int)distance)+"m.root";
    auto file = TFile::Open(fname.c_str());
                                          
    cout << "Plotting " << fname << endl;

    // Get Ntuples from file                      
    TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 
    
    double entryEnergy = 0;
    double totalEnergy = 0;
  
    InfoNtuple->SetBranchAddress("EntryEnergy", &entryEnergy); 


    // Loop through events to count up the number of neutrons
    // and add to the profile plot
    int nEntries = (int)InfoNtuple->GetEntries();

    for (int i=0; i<nEntries; ++i)
    {
      InfoNtuple->GetEntry(i);
      
      // Readjust the energy to have units of GeV
      entryEnergy = entryEnergy/1000;
      totalEnergy += entryEnergy;

      hprof->Fill(distance, entryEnergy);
    }

    totalEnergy /= 1000;
    std::cout << "Entry energy: " << totalEnergy << std::endl;
  }

  int binList [] = {2,3,12,52,102,302,502,702,1002};
  for (int bin=0; bin<9; ++bin)
    cout << sourceEnergy
         << " Bin no "
         << binList[bin]
         << ", bin content "
         << hprof->GetBinContent(binList[bin])
         << ", bin error "
         << hprof->GetBinError(binList[bin])
         << endl;

  hprof->Draw();                                  
  hprof->GetXaxis()->SetTitle("Source Distance from the Water (m)");    
  hprof->GetYaxis()->SetTitle("Entry Energy of the Muon");
                                               
  //can->SetLogx();                            
                                               
  //can->SaveAs(Form("/Users/SilverJr/Documents/PhD/Geant4_Projects/NeutronSim/GeneratedPlots/MuonEntryEnergy(%s).pdf", sourceEnergy.c_str()));



}
