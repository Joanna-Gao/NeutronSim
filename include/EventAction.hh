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
//
/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "AnalysisManager.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

class RunAction;
class PrimaryGeneratorAction;

/// Event action class
///

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction, AnalysisManager* analysis);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    
    void FillVectorParticleID(G4int particleID)
    { fParticleID.push_back(particleID); }
    void FillVectorEdep(G4double edep)
    { fStoredEdep.push_back(edep); }
    void FillVectorTotalEnergy(G4double energy)
    { fTotalEnergy.push_back(energy); }
    void FillVectorIsCaptured(G4int isCaptured)
    { fIsCaptured.push_back(isCaptured); }
    void SetEntryEnergy(G4double entryEnergy)
    { fEntryEnergy = entryEnergy; }

    G4String GetSourceParticle() { return fSourceParticle; }

    // Function for checking if the energy should be stored as 
    // the true entry energy of the source particle
    G4bool IsTrueEntryEnergy() { return fCanStore; }
    void StoredEntryEnergy() { fCanStore = false; }
    

  private:
    RunAction*             fRunAction;
    G4double                    fEdep;
    AnalysisManager* fAnalysisManager;
    G4String          fSourceParticle;
    G4int                    fEventID;
    std::vector<G4int>    fParticleID; 
    std::vector<G4double> fStoredEdep;
    std::vector<G4double> fTotalEnergy;
    std::vector<G4int>    fIsCaptured;
    G4double             fEntryEnergy;
    G4bool                  fCanStore;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
