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

  //h10 = 0;
  //h20 = 0;
}

AnalysisManager::~AnalysisManager() 
{}

void AnalysisManager::Initialise() 
{ 
  auto manager = G4AnalysisManager::Instance();
  
  manager->SetVerboseLevel(0);
 
  // Create a root file
  G4String fileName = "ProtonAnalysis";

  // Create directories  
  //manager->SetNtupleDirectoryName("ProtonAnalysis");
  

  G4bool fileOpen = manager->OpenFile(fileName);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " 
           << fileName[1] 
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
  manager -> CreateNtuple("TEdep", "TotalEdep");
  //manager -> CreateNtupleDColumn("TotalEdep"); 
  fNtColId[0] = manager -> CreateNtupleDColumn("TotalEdep");
  manager -> FinishNtuple();

  //Create Energy Deposition of electrons
  manager -> CreateNtuple("eEdep", "eEdep");
  fNtColId[1] = manager -> CreateNtupleDColumn("eEdep");
  manager -> FinishNtuple();

  //Create Energy Deposition of positrons                
  manager -> CreateNtuple("epEdep", "e+Edep");               
  fNtColId[2] = manager -> CreateNtupleDColumn("e+Edep"); 
  manager -> FinishNtuple();                             

  //Create Energy Deposition of photons                 
  manager -> CreateNtuple("gammaEdep", "gammaEdep");                
  fNtColId[3] = manager -> CreateNtupleDColumn("gammaEdep");  
  manager -> FinishNtuple();                               
  
  //Create Energy Deposition of pions                        
  manager -> CreateNtuple("105", "pionEdep");                 
  fNtColId[4] = manager -> CreateNtupleDColumn("pionEdep");   
  manager -> FinishNtuple();                                   

  //Create Energy Deposition of proton                           
  manager -> CreateNtuple("pEdep", "protonEdep");                   
  fNtColId[5] = manager -> CreateNtupleDColumn("protonEdep");     
  manager -> FinishNtuple();                                    

  //Create Energy Deposition of neutron                                    
  manager -> CreateNtuple("nEdep", "neutronEdep");                    
  fNtColId[6] = manager -> CreateNtupleDColumn("neutronEdep");             
  manager -> FinishNtuple();                                              

  //factoryOn = true;    
}

void AnalysisManager::NtupleMerging(G4bool canMerge)
{
  auto manager = G4AnalysisManager::Instance();
  manager->SetNtupleMerging(canMerge);
} 

void AnalysisManager::FillTotalEdepHist(G4double edep)
{
  G4cout << "Accessing FillHist Method" << G4endl;
  auto manager = G4AnalysisManager::Instance();
  manager->FillH1(1, edep);
  G4cout << "Hist stored" << G4endl;
}

void AnalysisManager::StoreTotalEdep(G4double edep)
{
  G4cout << "Accessing StoreNtuple Method" << G4endl;  
  auto manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, fNtColId[0], edep);
  manager -> AddNtupleRow(1); 
  G4cout << "Ntuple stored" << G4endl;
}

void AnalysisManager::StoreElectronEdep(G4double edep)
{
  auto manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(2, fNtColId[1], edep);
  manager -> AddNtupleRow(2); 
}

//void AnalysisManager::StorePositronEdep(G4double edep)        
//{                                                             
//  auto manager = G4AnalysisManager::Instance(); 
//  manager -> FillNtupleDColumn(3, fNtColId[2], edep);         
//  manager -> AddNtupleRow(3);                                 
//}                                                             
//
//void AnalysisManager::StorePhotonEdep(G4double edep)        
//{                                                             
//  auto manager = G4AnalysisManager::Instance(); 
//  manager -> FillNtupleDColumn(4, fNtColId[3], edep);         
//  manager -> AddNtupleRow(4);                                 
//}                                                             
//
//void AnalysisManager::StorePionEdep(G4double edep)           
//{                                                              
//  auto manager = G4AnalysisManager::Instance();  
//  manager -> FillNtupleDColumn(5, fNtColId[4], edep);          
//  manager -> AddNtupleRow(5);                                  
//}                                                              
 
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
