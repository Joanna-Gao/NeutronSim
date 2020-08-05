// \file PrimaryGeneratorMessenger.cc                       
// \brief definition of the PrimaryGeneratorMessenger class 

#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
: G4UImessenger(),
  fPGAction(Gun),
  fGunDirectory(0)
{
  // Set the command path for the new UI command 
  fGunDirectory = new G4UIdirectory("/Source/position/");
  fGunDirectory->SetGuidance("Commands to control the position of\
 the particle gun");

  // Set the specific command for changing the z-position of the particle gun
  fGunZPosition = 
      new G4UIcmdWithADoubleAndUnit("/Source/position/SetZPosition", this);
  fGunZPosition->
      SetGuidance("Set the distance between the source and the water tank");
  fGunZPosition->
      SetGuidance("Default z position is at the water-concret boundary");
  fGunZPosition->SetGuidance("Only accept meter as unit");
  fGunZPosition->SetParameterName("Z", false);
  fGunZPosition->SetRange("Z>=0.");
  fGunZPosition->SetUnitCandidates("m");
  
  // Set default value for gun's z position
  fPGAction->SetGunZPosition(0.);
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fGunZPosition;
  delete fGunDirectory;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand *command, 
                                            G4String newValue)
{
  if (command == fGunZPosition)
    fPGAction->SetGunZPosition(fGunZPosition->GetNewDoubleValue(newValue*m));

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

