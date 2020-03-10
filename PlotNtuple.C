void PlotHistogram(TNtuple *ntupleName, string histTitle, string fileName);

void PlotNtuple()
{
  // Open the desired ROOT file and directory
  string fname;
  cout << "Please input a ROOT file which you need to display:" << endl;
  cin >> fname;       //Input a ROOT file
  file = TFile::Open(fname.c_str());
  TDirectory *dir = file->Get("ProtonAnalysis");

  // Get Ntuples from file
  TNtuple *TEdep = (TNtuple*)dir->Get("TEdep");
 
  // prevent showing the plots
  //gROOT->SetBatch(); 

  PlotHistogram(TEdep, "Total Energy Deposited in Water", "TotalEdep.pdf");

  //double edep;
  //TEdep->SetBranchAddress("row_wise_branch", &edep);

  //// Create histograms
  //TCanvas *can = new TCanvas("can", "can");
  //can->Clear();
  //can->SetLogy();

  //TH1D *TEdepHist = new TH1D("TEdepHist", "Total Energy Deposited in Water",
  //        100, 0, 1000);

  //double minValue = 1000, maxValue = 0, fillValue = 0;


  //for (int i = 0; i < TEdep->GetEntries(); ++i)
  //{
  //  TEdep->GetEntry(i);
  //  fillValue = edep/1000;
  //  TEdepHist->Fill(fillValue);
  //  if (fillValue < minValue) minValue = fillValue;
  //  if (fillValue > maxValue) maxValue = fillValue;
  //}

  //std::cout << "min: " << minValue << ", max: " << maxValue << std::endl;


  //TEdepHist->Draw();
  ////TEdepHist->GetXaxis()->
  //TEdepHist->GetXaxis()->SetRangeUser(minValue, maxValue);
  //TEdepHist->GetXaxis()->SetTitle("Energy (GeV)");
  //TEdepHist->GetYaxis()->SetTitle("Number of Events");
  //
  //

  //can->SetTitle("Total Energy Deposited in Water");
  //can->SaveAs("./TotalEdep.pdf");

}

void PlotHistogram(TNtuple *ntupleName, string histTitle, string fileName)
{
  double edep;                                                               
  ntupleName->SetBranchAddress("row_wise_branch", &edep);                         
                                                                             
  // Create histograms                                                       
  TCanvas *can = new TCanvas("can", "can");                                  
  can->Clear();                                                              
  //can->SetLogy();                                                            
                                                                             
  TH1D *TEdepHist = new TH1D("TEdepHist", histTitle.c_str(), 
          100, 0, 1000);                                                     
                                                                             
  double minValue = 1000, maxValue = 0, fillValue = 0;                       
                                                                             
                                                                             
  for (int i = 0; i < ntupleName->GetEntries(); ++i)                              
  {                                                                          
    ntupleName->GetEntry(i);                                                      
    fillValue = edep/1000;                                                   
    TEdepHist->Fill(fillValue);                                              
    if (fillValue < minValue) minValue = fillValue;                          
    if (fillValue > maxValue) maxValue = fillValue;                          
  }                                                                          
                                                                             
  std::cout << "min: " << minValue << ", max: " << maxValue << std::endl;    
                                                                             
                                                                             
  TEdepHist->Draw();                                                         
  //TEdepHist->GetXaxis()->                                                  
  TEdepHist->GetXaxis()->SetRangeUser(minValue, maxValue);                   
  TEdepHist->GetXaxis()->SetTitle("Energy (GeV)");                           
  TEdepHist->GetYaxis()->SetTitle("Number of Events");                       
                                                                             
                                                                             
                                                                             
  can->SetTitle(histTitle.c_str());                         
  can->SaveAs(fileName.c_str());                                            

}
