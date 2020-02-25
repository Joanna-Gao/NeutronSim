#include <stdlib.h>
#include "AnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"


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
  manager->SetNtupleDirectoryName("ProtonAnalysis_ntuple");
  

  G4bool fileOpen = manager->OpenFile(fileName);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " 
           << fileName[1] 
           << G4endl;
    return;
  }

  manager->SetFirstNtupleId(1);

  //Create Primary Energy Ntuple
  manager -> CreateNtuple("101", "Primary Energy");
  fNtColId[0] = manager -> CreateNtupleDColumn("Ek");
  manager -> FinishNtuple();

  //Create Energy Deposition within SV Ntuple
  manager -> CreateNtuple("102", "Edep");
  fNtColId[1] = manager -> CreateNtupleDColumn("edep");
  manager -> FinishNtuple();

  //creating a ntuple, containing the information about secondary particles
  manager -> CreateNtuple("103", "secondary");
  fNtColId[2] = manager -> CreateNtupleDColumn("AA");
  fNtColId[3] = manager -> CreateNtupleDColumn("ZZ");
  fNtColId[4] = manager -> CreateNtupleDColumn("KE");
  manager -> FinishNtuple();

  
  factoryOn = true;    
}


void AnalysisManager::SetPrimaryEnergy(G4double energy)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(1, fNtColId[0], energy);
  manager -> AddNtupleRow(1); 
}

void AnalysisManager::StoreEnergyDeposition(G4double edep)
{
  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(2, fNtColId[1], edep);
  manager -> AddNtupleRow(2); 
}

void AnalysisManager::FillSecondaries(G4int AA, G4double charge, G4double energy)
{

  G4AnalysisManager* manager = G4AnalysisManager::Instance();
  manager -> FillNtupleDColumn(3, fNtColId[2], AA);
  manager -> FillNtupleDColumn(3, fNtColId[3], charge);
  manager -> FillNtupleDColumn(3, fNtColId[4], energy);
  manager -> AddNtupleRow(3);  
}
 
void AnalysisManager::finish() 
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
