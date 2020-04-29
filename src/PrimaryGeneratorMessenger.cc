// \file PrimaryGeneratorMessenger.cc                       
// \brief definition of the PrimaryGeneratorMessenger class 

#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
: G4UImessenger(),
  fPGAction(Gun),
  fGunDirectory(0)
{



}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fOutputDirectory;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4String PrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand *command)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand *command, 
                                            G4String newValue)
{}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

