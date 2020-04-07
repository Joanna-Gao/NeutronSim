#include "TrackingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh" 

#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4DynamicParticle.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"

TrackingAction::TrackingAction(EventAction * eventAction)
: G4UserTrackingAction(),
  fEventAction(eventAction),
  fPhysVolume(0),
  fParticleName(""),
  fParticleID(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

TrackingAction::~TrackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

void TrackingAction::PreUserTrackingAction(const G4Track * track)
{
  if (!fPhysVolume) {
    const DetectorConstruction* detectorConstruction
      = static_cast<const DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fPhysVolume = detectorConstruction->GetPhysicalVolume();
  }                                                
  
  // get volume of the current step
  G4VPhysicalVolume * volume = track->GetVolume();
  
  // check if we are in scoring volume             
  if (volume != fPhysVolume) return;

  // Record particle ID and its total energy at the start of the track
  //
  // Extract particleID as defined by PDG MC numbering scheme             
  const G4DynamicParticle *dynParticle = track->GetDynamicParticle();
  G4ParticleDefinition *particle = dynParticle->GetDefinition();
  fParticleName = particle->GetParticleName();
  fParticleID = particle->GetPDGEncoding();

  // Extract decay time
  //G4double globalTime = track->GetGlobalTime();
  //G4double localTime = track->GetLocalTime();

  //G4VPhysicalVolume * volume = track->GetVolume();
  //G4cout << "Physical volume: " << (*volume) << G4endl;

  G4double totalEnergy = track->GetTotalEnergy(); 
  
 
 
  if (fParticleID == 2212 || // proton                               
      fParticleID == 2112 || // neutron                              
      fParticleID == 11   || fParticleID == -11 || // e-/e+           
      fParticleID == 12   || fParticleID == -12 || // nu_e/nu_e bar   
      fParticleID == 13   || fParticleID == -13 || // mu-/mu+         
      fParticleID == 14   || fParticleID == -14 || // nu_mu/nu_mu bar 
      fParticleID == 22   || // photons                              
      fParticleID == 111  || // neutral pion                         
      fParticleID == 211  || fParticleID == -211|| // pi+/-           
      fParticleID == 321  || fParticleID == -321)  // K+/-
  { 
    fEventAction->FillVectorParticleID(fParticleID);  
    fEventAction->FillVectorTotalEnergy(totalEnergy); 
  }
  
  //G4cout << fParticleName
  //       << " has encoding of "
  //       << fParticleID
  //       << " starts with global time "
  //       << globalTime
  //       << " s, local time "
  //       << localTime
  //       << " s."
  //       << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

void TrackingAction::PostUserTrackingAction(const G4Track *)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
