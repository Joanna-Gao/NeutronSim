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

  // Create a root file                 
  G4String fileName = "ProtonAnalysis"; 

  G4bool fileOpen = manager->OpenFile(fileName);
  if (!fileOpen) {
    G4cout << "\n---> AnalysisManager::Initialise(): cannot open " 
           << manager->GetFileName()
           << G4endl;
    return;
  }

  manager->SetFirstHistoId(1);
  manager->SetFirstNtupleId(1); 
  
  manager->CreateH1("TotalEdep","Total Edep in water", 100, 0., 1*TeV);

  // Create Total Energy Deposition Ntuple
  // Ntuple 1
  InitialiseNtuple(0, "TEdep", "TotalEdep", "TotalEdep");
  
  // Ntuple 2
  manager->CreateNtuple("eventInfo", 
                        "Energy and particle information of the event");               
  fNtColId[1] = manager->CreateNtupleIColumn("EventNum"); // int branch
  fNtColId[2] = manager->
                CreateNtupleIColumn("ParticleID");  // based on PDG convention
  fNtColId[3] = manager->CreateNtupleDColumn("Edep"); // per particle
  // a branch for recording neutron capture when the other branches work
  manager->FinishNtuple();                                    

  //factoryOn = true;    
}

// Making ntuple creation easier
void AnalysisManager::InitialiseNtuple
    (G4int index, G4String tupleName, G4String tupleTitle, G4String columnName)
{
  auto manager = G4AnalysisManager::Instance();
  manager->CreateNtuple(tupleName, tupleTitle);
  fNtColId[index] = manager->CreateNtupleDColumn(columnName);
  manager->FinishNtuple();
}

void AnalysisManager::FillTotalEdepHist(G4double edep)
{
  auto manager = G4AnalysisManager::Instance();
  manager->FillH1(1, edep);
}

void AnalysisManager::StoreTotalEdep(G4double edep)
{
  auto manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, fNtColId[0], edep);
  manager -> AddNtupleRow(1); 
}

void AnalysisManager::StoreParticleInfo
     (G4int eventNum, G4int particleID, G4double edep)        
{                                                             
  auto manager = G4AnalysisManager::Instance(); 
  manager -> FillNtupleIColumn(2, fNtColId[1], eventNum);          
  manager -> FillNtupleIColumn(2, fNtColId[2], particleID);         
  manager -> FillNtupleDColumn(2, fNtColId[3], edep);          
  manager -> AddNtupleRow(2);                                 
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
