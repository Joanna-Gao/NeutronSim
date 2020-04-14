#include <string> 

{
  int fileNumber;
  cout << "How many distances do you want to look at? (Max no. 5)" << endl;
  cin >> fileNumber;

  int energyNumber;
  cout << "How many source energy do you want to look at? (Max no. 3)" << endl;
  cin >> energyNumber;

  int distanceList [] = {0, 1, 10, 50, 100};
  int energyList [] = {100, 500, 1};
                      //{100, 500, 1};

  // Create a profile plot                                           
  TCanvas *can = new TCanvas("can","Number of Neutrons");

  TProfile * hprof1 = new TProfile("hprof1","",102,-1, 101,0,3000);
  TProfile * hprof2 = new TProfile("hprof2","",102,-1, 101,0,3000); 
  TProfile * hprof3 = new TProfile("hprof3","",102,-1, 101,0,3000);
  hprof1->GetXaxis()->SetTitle("Source Distance from the Water (m)");
  hprof1->GetYaxis()->SetTitle("Number of Neutrons");
  hprof1->SetTitle("No. of Neutrons Deposited Energy in Water");
  
  //hprof1->SetMarkerStyle(1);
  //hprof1->SetMarkerColor(kBlack);
  //hprof2->SetMarkerStyle(2);
  //hprof2->SetMarkerColor(kPink); 
  //hprof3->SetMarkerStyle(3);
  //hprof3->SetMarkerColor(kBlue);


  for (int x=0; x<fileNumber; ++x)
  {
    for (int y=0; y<energyNumber; ++y)
    {
      double distance = (double)distanceList[x];
      double sourceEnergy = (double)energyList[y];

      string fname;
      if (y == 0 || y == 1)
        fname=
          "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events"+
std::to_string((int)sourceEnergy)+"GeVmu"+std::to_string((int)distance)+"m.root";
      else
        fname=
          "~/Documents/PhD/Geant4_Projects/MuonAnalysis-build/1000Events"+ 
std::to_string((int)sourceEnergy)+"TeVmu"+std::to_string((int)distance)+"m.root";

      auto file = TFile::Open(fname.c_str());
                                            
      cout << "Plotting " << fname << endl;

      // Get Ntuples from file                      
      TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 
      std::vector<int> * particleID = 0;

      InfoNtuple->SetBranchAddress("ParticleID", &particleID);

      // Loop through events to count up the number of neutrons
      // and add to the profile plot
      int nEntries = (int)InfoNtuple->GetEntries();
      double counter = 0.;
      double meanCount = 0.;

      for (int i=0; i<nEntries; ++i)
      {
        InfoNtuple->GetEntry(i);
        for (int j=0; j<particleID->size(); ++j)      
        { 
          if ((*particleID)[j] == 2112) ++counter;
        }
        if (y == 0) hprof1->Fill(distance, counter);
        else if (y == 1) hprof2->Fill(distance, counter);
        else if (y == 2) hprof2->Fill(distance, counter); 
        
        meanCount += counter;

        counter = 0;
      }
      meanCount /= 1000;
      cout << "For energy "
           << energyList[y]
           << ", the mean no of neutron is " 
           << meanCount 
           << endl;
    }

  }

  hprof1->Draw();
  hprof2->Draw("SAME"); 
  hprof3->Draw("SAME"); 

  //if (energyNumber == 2) 
  //  hprof2->Draw("SAME");
  //else if (energyNumber == 3) 
  //{
  //  hprof2->Draw("SAME");
  //  hprof3->Draw("SAME");
  //}
 
  can->SaveAs("/Users/SilverJr/Documents/PhD/Geant4_Projects/NeutronSim/GeneratedPlots/NumberOfNeutron.pdf");



}
