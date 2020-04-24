//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/AnaEx02/include/HistoManager.hh
/// \brief Definition of the AnalysisManager class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef AnalysisManager_h
#define AnalysisManager_h 1

#include "globals.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
class TH1D;
class AnalysisMessenger;

const G4int kMaxHisto = 1;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class AnalysisManager
{
  public:
    AnalysisManager();
   ~AnalysisManager();
   
    void Initialise();
    void Save();

    void FillHisto(G4int ih, G4double xvalue, G4double weight = 1.0);

    void FillTotalEdepNtuple(G4double totalEnergyAbs);

    void FillParticleInfoNtuple(G4int eventID,
                                std::vector<G4int> particleID, 
                                std::vector<G4double> edep,
                                std::vector<G4double> totalEnergy,
                                std::vector<G4int> isCaptured,
                                G4double entryEnergy);
        
    G4String GetRootFileName() { return fFileName; }
    void SetRootFileName(G4String name) { fFileName = name; }

  private:
    TFile*                fRootFile;
    TH1D*                 fHisto[kMaxHisto];
    TTree*                fTEdepNtuple;
    TTree*                fParticleInfoNtuple;
    
    AnalysisMessenger*    fMessenger;
    G4String              fFileName;

    G4bool                fInitialised;
    G4double              fTEdep;
    G4int                 fEventID;
    std::vector<G4int>    fParticleID;
    std::vector<G4double> fEdep;
    std::vector<G4double> fTotalEnergy;
    std::vector<G4int>    fIsCaptured;
    G4double              fEntryEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

