// \file PrimaryGeneratorMessenger.hh                        
// \brief definition of the PrimaryGeneratorMessenger class  

#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcommand;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

class PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
    virtual ~PrimaryGeneratorMessenger();

    virtual G4String GetCurrentValue(G4UIcommand *command);
    virtual void SetNewValue(G4UIcommand *command, G4String newValue);

  private:
    PrimaryGeneratorAction*     fPGAction;
    G4UIdirectory*              fGunDirectory;    

};

#endif
