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
  //manager->SetNtupleMerging(true);

  G4cout << "Creating Histogram" << G4endl;
  manager->CreateH1("TotalEdep","Total Edep in water", 100, 0., 1*GeV);
  G4cout << "Histogram Created" << G4endl;

  //Create Total Energy Deposition Ntuple
  InitialiseNtuple(0, "TEdep", "TotalEdep", "TotalEdep");
  
  //Create Energy Deposition of electrons
  InitialiseNtuple(1, "eEdep", "eEdep", "eEdep");  

  //Create Energy Deposition of positrons                
  InitialiseNtuple(2, "epEdep", "ePlusEdep", "ePlusEdep");

  //Create Energy Deposition of photons                 
  InitialiseNtuple(3, "gammaEdep", "gammaEdep", "gammaEdep"); 

  //Create Energy Deposition of proton                           
  InitialiseNtuple(4, "pEdep", "protonEdep", "protonEdep");

  //Create Energy Deposition of neutron                                    
  InitialiseNtuple(5, "nEdep", "neutronEdep", "neutronEdep");
    
  //Create Energy Deposition of pi+                           
  InitialiseNtuple(6, "piPEdep", "piPlusEdep", "piPlusEdep");

  //Create Energy Deposition of pi-                            
  InitialiseNtuple(7, "piMEdep", "piMinusEdep", "piMinusEdep");  
 
  //Create Energy Deposition of pi0                               
  InitialiseNtuple(8, "piZEdep", "piZeroEdep", "piZeroEdep");   

  //Create Energy Deposition of kaon+                                
  InitialiseNtuple(9, "kaonPEdep", "kaonPlusEdep", "kaonPlusEdep");      
                                                                   
  //Create Energy Deposition of kaon-                                
  InitialiseNtuple(10, "kaonMEdep", "kaonMinusEdep", "kaonMinusEdep");    
                                                                   
  //Create Energy Deposition of kaon0                                
  InitialiseNtuple(11, "kaonZEdep", "kaonZeroEdep", "kaonZeroEdep");      

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

void AnalysisManager::NtupleMerging(G4bool canMerge)
{
  auto manager = G4AnalysisManager::Instance();
  manager->SetNtupleMerging(canMerge);
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

void AnalysisManager::StoreElectronEdep(G4double edep)
{
  auto manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(2, fNtColId[1], edep);
  manager -> AddNtupleRow(2); 
}

void AnalysisManager::StorePositronEdep(G4double edep)        
{                                                             
  auto manager = G4AnalysisManager::Instance(); 
  manager -> FillNtupleDColumn(3, fNtColId[2], edep);         
  manager -> AddNtupleRow(3);                                 
}                                                             

void AnalysisManager::StorePhotonEdep(G4double edep)        
{                                                             
  auto manager = G4AnalysisManager::Instance(); 
  manager -> FillNtupleDColumn(4, fNtColId[3], edep);         
  manager -> AddNtupleRow(4);                                 
}                                                             

void AnalysisManager::StoreProtonEdep(G4double edep)              
{                                                               
  auto manager = G4AnalysisManager::Instance();                 
  manager -> FillNtupleDColumn(5, fNtColId[4], edep);           
  manager -> AddNtupleRow(5);                                   
}                                                               

void AnalysisManager::StoreNeutronEdep(G4double edep)              
{                               
  auto manager = G4AnalysisManager::Instance();                 
  manager -> FillNtupleDColumn(6, fNtColId[5], edep);           
  manager -> AddNtupleRow(6);                                   
}                                                               

void AnalysisManager::StorePiPlusEdep(G4double edep)              
{                                                               
  auto manager = G4AnalysisManager::Instance();                 
  manager -> FillNtupleDColumn(7, fNtColId[6], edep);           
  manager -> AddNtupleRow(7);                                   
}                                                               

void AnalysisManager::StorePiMinusEdep(G4double edep)               
{                                                                  
  auto manager = G4AnalysisManager::Instance();                    
  manager -> FillNtupleDColumn(8, fNtColId[7], edep);              
  manager -> AddNtupleRow(8);                                      
}                                                                  

void AnalysisManager::StorePiZeroEdep(G4double edep)               
{                                                                  
  auto manager = G4AnalysisManager::Instance();                    
  manager -> FillNtupleDColumn(9, fNtColId[8], edep);              
  manager -> AddNtupleRow(9);                                      
}                                                                  

void AnalysisManager::StoreKaonPlusEdep(G4double edep)                 
{                                                                    
  auto manager = G4AnalysisManager::Instance();                      
  manager -> FillNtupleDColumn(10, fNtColId[9], edep);                
  manager -> AddNtupleRow(10);                                        
}                                                                    
                                                                     
void AnalysisManager::StoreKaonMinusEdep(G4double edep)                
{                                                                    
  auto manager = G4AnalysisManager::Instance();                      
  manager -> FillNtupleDColumn(11, fNtColId[10], edep);                
  manager -> AddNtupleRow(11);                                        
}                                                                    
                                                                     
void AnalysisManager::StoreKaonZeroEdep(G4double edep)                 
{                                                                    
  auto manager = G4AnalysisManager::Instance();                      
  manager -> FillNtupleDColumn(12, fNtColId[11], edep);                
  manager -> AddNtupleRow(12);                                        
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
