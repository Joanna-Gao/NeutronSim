#include <string> 

{
  int fileNumber;
  cout << "How many ROOT files do you want to look at?" << endl;
  cin >> fileNumber;

  int distanceList [] = {0, 1, 10, 30, 50, 70, 100};

  // Create a profile plot                                           
  TCanvas *can = new TCanvas("can","Muon visible energy histogram"); 
  can->Clear();                                                      

  TProfile * hprof = new TProfile("hprof",
                                  "Profile of No. of Neutrons Deposited Energy in Water",
                                   100,-1, 101,0,1000000);

  for (int x=0; x<fileNumber; ++x)
  {
    double distance = (double)distanceList[x];


    // Open the desired ROOT file
    //string fname;                              
    //cout << "Please input a ROOT file which you need to display:" << endl;
    //cin >> fname;       //Input a ROOT file       
    string fname =  "~/Documents/PhD/Geant4_Projects/ProtonAnalysis-build/HPRootFiles/1000Events1TeVMu"+std::to_string((int)distance)+"m.root";
    auto file = TFile::Open(fname.c_str());
                                          
    cout << "Plotting " << fname << endl;

    // Get Ntuples from file                      
    TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 
    std::vector<int> * particleID = 0;
    std::vector<double> * totalEnergy = 0; 

    InfoNtuple->SetBranchAddress("ParticleID", &particleID);
    InfoNtuple->SetBranchAddress("TotalEnergy", &totalEnergy); 

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

  hprof->Draw();                                  
  hprof->GetXaxis()->SetTitle("Source Distance from the Water (m)");    
  hprof->GetYaxis()->SetTitle("Number of Neutrons");
                                               
  //can->SetLogx();                            
                                               
  //string imageName;                            
  //cout << "Please input a name which you like to save your image as:" << endl;
  //cin >> imageName;       //Input a name for the saved file
  //can->SaveAs(imageName.c_str());                          

  can->SaveAs("NumberOfNeutron.pdf");



}
