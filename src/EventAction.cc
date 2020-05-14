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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "RunAction.hh"
#include "AnalysisManager.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4DynamicParticle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(AnalysisManager* analysis)
: G4UserEventAction(),
  fEdep(0.),
  fAnalysisManager(analysis),
  fSourceParticle(""),
  fEventID(0),
  fParticleID(0), 
  fStoredEdep(0.),
  fTotalEnergy(0.),
  fIsCaptured(0),
  fEntryEnergy(0.),
  fCanStore(true)
{
  const PrimaryGeneratorAction* generatorAction                       
   = static_cast<const PrimaryGeneratorAction*>                       
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  fSourceParticle = generatorAction->GetParticleGun()
                                    ->GetParticleDefinition()
                                    ->GetParticleName();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
  fCanStore = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{   

  // Fill histograms
  fAnalysisManager->FillHisto(0, fEdep);

  // Fill ntuple
  fAnalysisManager->FillTotalEdepNtuple(fEdep);

  fEventID = event->GetEventID();

  /*
  if (fTotalEnergy.size() != fParticleID.size())
  {
    G4ExceptionDescription msg;                                
    msg << "The size of the vector, TotalEnergy, does not\n";        
    msg << "equal to the rest.\n";
    msg << "Size of TotalEnergy: ";
    msg << fTotalEnergy.size();
    msg << "\nSize of ParticleID: ";
    msg << fParticleID.size();
    G4Exception("EventAction::EndOfEventAction()", 
     "MyCode0002",JustWarning,msg); 
  }
  */

  G4cout << "Event ID " << fEventID << " finished." << G4endl;

  fAnalysisManager->FillParticleInfoNtuple(fEventID, 
                                           fParticleID, 
                                           fStoredEdep, 
                                           fTotalEnergy,
                                           fIsCaptured,
                                           fEntryEnergy);

  fParticleID.clear();
  fStoredEdep.clear();
  fTotalEnergy.clear();
  fIsCaptured.clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
