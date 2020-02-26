#include <stdlib.h>
#include "AnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//#include "G4AnalysisManager.hh"


AnalysisManager::AnalysisManager() 
{
  factoryOn = false;

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
  G4AnalysisManager *manager = G4AnalysisManager::Instance();
  
  manager->SetVerboseLevel(2);
 
  // Create a root file
  G4String fileName = "ProtonAnalysis.root";

  // Create directories  
  //manager->SetNtupleDirectoryName("ProtonAnalysis");
  

  G4bool fileOpen = manager->OpenFile(fileName);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " 
           << fileName[1] 
           << G4endl;
    return;
  }

  manager->SetFirstNtupleId(1);

  //Create Total Energy Deposition Ntuple
  manager -> CreateNtuple("TotalEdep", "TotalEdep");
  fNtColId[0] = manager -> CreateNtupleDColumn("TotalEdep");
  manager -> FinishNtuple();

  //Create Energy Deposition of electrons
  manager -> CreateNtuple("102", "eEdep");
  fNtColId[1] = manager -> CreateNtupleDColumn("eEdep");
  manager -> FinishNtuple();

  //Create Energy Deposition of positrons                
  manager -> CreateNtuple("103", "e+Edep");               
  fNtColId[2] = manager -> CreateNtupleDColumn("epEdep"); 
  manager -> FinishNtuple();                             

  //Create Energy Deposition of photons                 
  manager -> CreateNtuple("104", "gammaEdep");                
  fNtColId[3] = manager -> CreateNtupleDColumn("gammaEdep");  
  manager -> FinishNtuple();                               
  
  //Create Energy Deposition of pions                        
  manager -> CreateNtuple("105", "pionEdep");                 
  fNtColId[4] = manager -> CreateNtupleDColumn("pionEdep");   
  manager -> FinishNtuple();                                   

  factoryOn = true;    
}

void AnalysisManager::StoreTotalEdep(G4double edep)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, fNtColId[0], edep);
  manager -> AddNtupleRow(1); 
}

void AnalysisManager::StoreElectronEdep(G4double edep)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(2, fNtColId[1], edep);
  manager -> AddNtupleRow(2); 
}

void AnalysisManager::StorePositronEdep(G4double edep)        
{                                                             
  G4AnalysisManager* manager = G4AnalysisManager::Instance(); 
  manager -> FillNtupleDColumn(3, fNtColId[2], edep);         
  manager -> AddNtupleRow(3);                                 
}                                                             

void AnalysisManager::StorePhotonEdep(G4double edep)        
{                                                             
  G4AnalysisManager* manager = G4AnalysisManager::Instance(); 
  manager -> FillNtupleDColumn(4, fNtColId[3], edep);         
  manager -> AddNtupleRow(4);                                 
}                                                             

void AnalysisManager::StorePionEdep(G4double edep)           
{                                                              
  G4AnalysisManager* manager = G4AnalysisManager::Instance();  
  manager -> FillNtupleDColumn(5, fNtColId[4], edep);          
  manager -> AddNtupleRow(5);                                  
}                                                              
 
void AnalysisManager::Finish() 
{   
 if (factoryOn) 
   {
    G4AnalysisManager* manager = G4AnalysisManager::Instance();    
    manager -> Write();
    manager -> CloseFile();  
      
    delete G4AnalysisManager::Instance();
    factoryOn = false;
   }
}
