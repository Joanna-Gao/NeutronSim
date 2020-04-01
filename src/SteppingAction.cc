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

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4DynamicParticle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fPhysEnv(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fPhysEnv) { 
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fPhysEnv = detectorConstruction->GetPhysicalVolume();   
  }

  // get volume of the current step
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
      
  // check if we are in scoring volume
  if (volume != fPhysEnv) return;

  // the following steps are to store individual particle Edep
  fPreviousTrackID = fTrackID;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep); 

  G4Track *track = step->GetTrack();   
  fTrackID = track->GetTrackID();      

  // Extract particleID as defined by PDG MC numbering scheme 
  const G4DynamicParticle *dynParticle = track->GetDynamicParticle();
  G4ParticleDefinition *particle = dynParticle->GetDefinition();
  fParticleName = particle->GetParticleName();
  G4int particleID = particle->GetPDGEncoding();

  G4double kinEnergy = dynParticle->GetKineticEnergy();
  G4double totalEnergy = track->GetTotalEnergy();

  //G4double globalTime = track->GetGlobalTime();
  //G4double localTime  = track->GetLocalTime();


  //G4cout << "TrackID: "
  //       << fTrackID
  //       << ", ParticleID: "
  //       << particleID
  //       << ", Global time: " 
  //       << globalTime 
  //       << ", Local time: " 
  //       << localTime 
  //       << G4endl;
 

  // Extract neutron capture info
  G4TrackStatus trackStatus = track->GetTrackStatus();
  G4String processName = step->GetPostStepPoint()
                             ->GetProcessDefinedStep()->GetProcessName();

  // Record muon decays
  //if (fParticleName == "mu-" && processName == "Decay")
  //  G4cout<<"Muon decayed!"<<G4endl;
  
  //G4cout << fParticleName
  //       << " track status: "
  //       << trackStatus
  //       << ", process name: "
  //       << processName
  //       << G4endl;
  
  //if (processName=="nCapture")
  //G4cout << fParticleName                
  //       << " captured!"                 
  //       << G4endl;                      
         

  if (trackStatus == fStopAndKill) {
    //G4cout << "Track ID has changed from " 
    //       << fPreviousTrackID 
    //       << " to " 
    //       << fTrackID 
    //       << G4endl;
    //
    //G4cout << "Accumulated EnergyDeposit: " 
    //       << fLocalEdep 
    //       << " stored, initialising..." 
    //       << G4endl;


    // Store the particle IDs and the energy deposited in two 1D vectors
    // Next step is to only store the ones we are interested, also store
    // if the neutron is captured
    //
    if (particleID == 2212 || // proton
        particleID == 2112 || // neutron
        particleID == 11   || particleID == -11 || // e-/e+
        particleID == 12   || particleID == -12 || // nu_e/nu_e bar
        particleID == 13   || particleID == -13 || // mu-/mu+
        particleID == 14   || particleID == -14 || // nu_mu/nu_mu bar
        particleID == 22   || // photons
        particleID == 111  || // neutral pion
        particleID == 211  || particleID == -211|| // pi+/-
        particleID == 321  || particleID == -321)  // K+/-
      {
        fEventAction->FillVectorEdep(fLocalEdep);
        fEventAction->FillVectorParticleID(particleID);   
        fEventAction->FillVectorTotalEnergy(totalEnergy); 

        if (processName == "nCapture")            
          fEventAction->FillVectorIsCaptured(1);  
        else                                      
          fEventAction->FillVectorIsCaptured(0);  
          //G4cout << fParticleName               
          //       << " captured!"                
          //       << G4endl;
      }

    fLocalEdep = 0;
  }
  else {
    
    //G4cout << "Energy deposit in this step: " << edepStep << G4endl; 

    fLocalEdep += edepStep;

    //G4cout << "Accumulated energy deposit: " << fLocalEdep << G4endl;
  }

  //G4cout << fParticleName               
  //       << " has total energy of "
  //       << totalEnergy
  //       << " and kinetic energy of "     
  //       << (kinEnergy / CLHEP::MeV)   
  //       << " MeV"                     
  //       << G4endl;  


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

