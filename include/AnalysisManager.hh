#ifndef ANALYSISMANAGER_HH
#define ANALYSISMANAGER_HH 

#include "globals.hh"
#include "g4root.hh"
//#include "g4csv.hh"
//#include "g4xml.hh"

// Define the total number of columns in the ntuple
//const G4int MaxHisto = 10;
const G4int MaxNtCol = 20;


class AnalysisManager
{ 

public:
   AnalysisManager();
  ~AnalysisManager();
  
  void Initialise(); // Creating the ROOT file

  void InitialiseNtuple(G4int index, G4String tupleName,
                        G4String tupleTitle, G4String columnName);

  void NtupleMerging(G4bool canMerge);

  void FillTotalEdepHist(G4double edep);

  void StoreTotalEdep(G4double edep);

  void StoreElectronEdep(G4double edep);
  
  void StorePositronEdep(G4double edep); 

  void StorePhotonEdep(G4double edep);   

  void StoreProtonEdep(G4double edep);      

  void StoreNeutronEdep(G4double edep);      

  void StorePiPlusEdep(G4double edep);

  void StorePiMinusEdep(G4double edep);

  void StorePiZeroEdep(G4double edep);

  void StoreKaonPlusEdep(G4double edep);  
                                        
  void StoreKaonMinusEdep(G4double edep); 
                                        
  void StoreKaonZeroEdep(G4double edep);  

  void StoreMuMinusEdep(G4double edep);

  void StoreMuPlusEdep(G4double edep);

  void Finish();
  // Close the ROOT file with all the results stored in nutples 

private:
  //G4bool    factoryOn; 
  //G4int     fHistId[MaxHisto];
  G4int     fNtColId[MaxNtCol];

};

#endif
















































