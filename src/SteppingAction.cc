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
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "AnalysisManager.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4DynamicParticle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction,
                               AnalysisManager* analysis)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{
  analysisManager = analysis;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) { 
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;


  // the following steps are to store individual particle Edep
  previousTrackID = trackID;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  //G4cout << "GetTotalEnergyDeposit: " << edepStep << G4endl;
  fEventAction->AddEdep(edepStep); 

  // attempt to extract particle name 
  G4Track *track = step->GetTrack();
  
  trackID = track->GetTrackID();

  const G4DynamicParticle *dynParticle = track->GetDynamicParticle();

  G4ParticleDefinition *particle = dynParticle->GetDefinition();

  G4double kinEnergy = dynParticle->GetKineticEnergy();

  particleName = particle->GetParticleName();

  if (trackID != previousTrackID) {
    //G4cout << "Track ID has changed from " << previousTrackID << " to " << trackID << G4endl;
    //G4cout << "Accumulated EnergyDeposit: " << localEdep << " stored, initialising..." << G4endl;

    if (particleName == "mu-") analysisManager->StoreMuMinusKE(kinEnergy);  
    if (particleName == "mu+") analysisManager->StoreMuPlusKE(kinEnergy);  
    if (particleName == "mu-") analysisManager->StoreMuMinusEdep(localEdep); 
    if (particleName == "mu+") analysisManager->StoreMuPlusEdep(localEdep);  

    localEdep = 0;
  }
  else {
    
    localEdep += edepStep;
   
    //G4cout << "EnergyDeposit in this step: " << edepStep << G4endl;  
    //G4cout << "Accumulated energy deposit: " << localEdep << G4endl; 
   
  }
  
  //G4cout << trackID << ". " 
  //       << particleName 
  //       << ": kinetic energy of " 
  //       << (kinEnergy / CLHEP::MeV) 
  //       << " MeV" 
  //       << G4endl;
  
      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

