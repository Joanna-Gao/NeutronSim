{
  // Open the desired ROOT file and directory                            
  string fname;                                                          
  cout << "Please input a ROOT file which you need to display:" << endl;

  cin >> fname;       //Input a ROOT file       
  file = TFile::Open(fname.c_str());            
                                                
  // Get Ntuples from file                      
  TNtuple *InfoNtuple = (TNtuple*)file->Get("ParticleInfo"); 

  int eventID = 0;
  std::vector<int> * particleID = 0;

  InfoNtuple->SetBranchAddress("EventID", &eventID);
  InfoNtuple->SetBranchAddress("ParticleID", &particleID);

  // Create a profile plot
  TCanvas *can = new TCanvas("can","Profile histogram");
  can->Clear();

  //hprof  = new TProfile("hprof","Profile of no. of events vs. no. of neutron");
  TH1I * h1 = new TH1I("h1", "Neutron number distribution", 500, 0, 500);


  // Loop through events to count up the number of neutrons
  // and add to the profile plot
  int nEntries = (int)InfoNtuple->GetEntries();
  int counter = 0; // For recording how many neutrons in each event

  std::cout << "So far no problem" << std::endl;

  std::cout << nEntries << std::endl; 

  for (int i=0; i<nEntries; ++i)
  {
    InfoNtuple->GetEntry(i);
    for (int j=0; j<particleID->size(); ++j)      
    {                                             
      if ((*particleID)[j] == 2112) ++counter;
    }                                             
    h1->Fill(counter);
    counter = 0;
  }

  h1->Draw();
  h1->GetXaxis()->SetTitle("No. of Neutrons Deposited Energy in Water");
  h1->GetYaxis()->SetTitle("Number of Events");

  can->SetLogy();
  
  string imageName; 
  cout << "Please input a name which you like to save your image as:" << endl;
  cin >> imageName;       //Input a name for the saved file
  can->SaveAs(imageName.c_str());
  




}
