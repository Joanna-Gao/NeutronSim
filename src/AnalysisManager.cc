#include <stdlib.h>
#include "AnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

AnalysisManager::AnalysisManager() 
{
  //factoryOn = false;

  // Initialization
  // histograms
  //for (G4int k=0; k<MaxHisto; k++) fHistId[k] = 0;

  // Initialization ntuple
  for (G4int k=0; k<MaxNtCol; k++) fNtColId[k] = 0;
}

AnalysisManager::~AnalysisManager() 
{}

void AnalysisManager::Initialise() 
{ 
  auto manager = G4AnalysisManager::Instance();
  
  manager->SetVerboseLevel(0);
  manager->SetNtupleMerging(true);

  // Create directories  
  manager->SetNtupleDirectoryName("ProtonAnalysis");
  
  G4String fileName = "MuonAnalysis";

  G4bool fileOpen = manager->OpenFile(fileName);
  if (!fileOpen) {
    G4cout << "\n---> AnalysisManager::Initialise(): cannot open " 
           << manager->GetFileName() 
           << G4endl;
    return;
  }

  //manager->SetFirstHistoId(1);
  manager->SetFirstNtupleId(1);
  //manager->SetNtupleMerging(true);

  G4cout << "Creating Histogram" << G4endl;
  manager->CreateH1("TotalEdep","Total Edep in water", 100, 0., 1*GeV);
  G4cout << "Histogram Created" << G4endl;

  // Create Total Energy Deposition Ntuple
  InitialiseNtuple(0, "TEdep", "TotalEdep", "TotalEdep");
  
  // Create Ntuple to store mu- energy when it first enter the tank
  InitialiseNtuple(1, "muMinusKE", "Mu- Energy at the Concret/Water Threshold", 
                   "muMinusKE");  

  // Create Ntuple to store mu+ energy when it first enter the tank              
  InitialiseNtuple(2, "muPlusKE", "Mu+ Energy at the Concret/Water Threshold",  
                   "muPlusKE");                                                 

  //Create Ntuple to store Energy Deposition of mu- in water                
  InitialiseNtuple(3, "muMinusEdep", "Mu- Edep in Water", "muMinusEdep");

  //Create Ntuple to store Energy Deposition of mu+ in water                 
  InitialiseNtuple(4, "muPlusEdep", "Mu+ Edep in Water", "muPlusEdep");    
  
  //factoryOn = true;    
}

// Making ntuple creation easier
void AnalysisManager::InitialiseNtuple(G4int index, G4String tupleName, 
                                   G4String tupleTitle, G4String columnName)
{
  auto manager = G4AnalysisManager::Instance();
  manager->CreateNtuple(tupleName, tupleTitle);
  fNtColId[index] = manager->CreateNtupleDColumn(columnName);
  manager->FinishNtuple();
}

void AnalysisManager::FillTotalEdepHist(G4double edep)
{
  auto manager = G4AnalysisManager::Instance();
  manager->FillH1(0, edep);
}

void AnalysisManager::StoreTotalEdep(G4double edep)
{
  auto manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, fNtColId[0], edep);
  manager -> AddNtupleRow(1); 
}

void AnalysisManager::StoreMuMinusKE(G4double KE)
{
  auto manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(2, fNtColId[1], KE);
  manager -> AddNtupleRow(2); 
}

void AnalysisManager::StoreMuPlusKE(G4double KE)   
{                                                   
  auto manager = G4AnalysisManager::Instance();     
  manager -> FillNtupleDColumn(3, fNtColId[2], KE); 
  manager -> AddNtupleRow(3);                       
}                                                   

void AnalysisManager::StoreMuMinusEdep(G4double edep)        
{                                                             
  auto manager = G4AnalysisManager::Instance(); 
  manager -> FillNtupleDColumn(4, fNtColId[3], edep);         
  manager -> AddNtupleRow(4);                                 
}                                                             

void AnalysisManager::StoreMuPlusEdep(G4double edep)          
{                                                              
  auto manager = G4AnalysisManager::Instance();                
  manager -> FillNtupleDColumn(5, fNtColId[4], edep);          
  manager -> AddNtupleRow(5);                                  
}                                                              


void AnalysisManager::Finish() 
{   
  auto manager = G4AnalysisManager::Instance();     
  manager -> Write();                                             
  manager -> CloseFile();                                         
                                                                  
  delete G4AnalysisManager::Instance();                           

 //if (factoryOn) 
 //  {
 //   auto manager = G4AnalysisManager::Instance();    
 //   manager -> Write();
 //   manager -> CloseFile();  
 //     
 //   delete G4AnalysisManager::Instance();
 //   factoryOn = false;
 //  }
}
