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
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

void TrackingAction::PostUserTrackingAction(const G4Track *)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
