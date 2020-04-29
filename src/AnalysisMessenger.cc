// \file AnalysisMessenger.cc
// \brief definition of the AnalysisMessenger class

#include "AnalysisMessenger.hh"
#include "AnalysisManager.hh"

#include "G4UImessenger.hh" 
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

AnalysisMessenger::AnalysisMessenger(AnalysisManager* analysis)
: G4UImessenger(),
  fOutputDirectory(0),
  fFileName(0),
  fAnalysisManager(analysis)
{
  // Set the command path for the new UI command
  fOutputDirectory = new G4UIdirectory("/Output/");
  fOutputDirectory->SetGuidance("Commands to set output options.");

  // Set the specific command for setting output file name
  fFileName = new G4UIcmdWithAString("/Output/FileName", this);
  fFileName->SetGuidance("Set the output ROOT file name.");
  fFileName->SetParameterName("RootFileName", false);

  // Set initial value to AnalysisManager
  fAnalysisManager->SetRootFileName("MuonAnalysis.root");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......  

AnalysisMessenger::~AnalysisMessenger()
{
  delete fOutputDirectory;
  delete fFileName;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4String AnalysisMessenger::GetCurrentValue(G4UIcommand *command)
{
  if (command == fFileName) return fAnalysisManager->GetRootFileName();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
void AnalysisMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
  if (command == fFileName)
  {
    fAnalysisManager->SetRootFileName(newValue);
    G4cout << "\n----> Output file is open in "
           << newValue
           << G4endl;

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 



