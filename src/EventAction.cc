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

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4DynamicParticle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction, AnalysisManager* analysis)
: G4UserEventAction(),
  fRunAction(runAction),
  fAnalysisManager(analysis),
  fEdep(0.),
  fEventID(0),
  fParticleID(0), 
  fStoredEdep(0.) 
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{   
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep); 

  // Fill histograms
  fAnalysisManager->FillHisto(0, fEdep);

  // Fill ntuple
  fAnalysisManager->FillTotalEdepNtuple(fEdep);

  fEventID = event->GetEventID();

  //G4int size = 0, size1 = fParticleID.size(), size2 = fStoredEdep.size();

  //if ( size1  ==  size2 ) size = size1;
  //else
  //  {
  //    G4ExceptionDescription msg;                                
  //    msg << "The sizes of the two vectors, ParticleID\n";        
  //    msg << "and particleEdep, do not equal.\n";             
  //    msg << "The size will default to the size of the\n";
  //    msg << "longer one.\n";
  //    G4Exception("EventAction::EndOfEventAction()", 
  //     "MyCode0002",JustWarning,msg); 
  //    
  //    if ( size1 > size2 ) size = size1;
  //    else size = size2;
  //  }

  fAnalysisManager->FillParticleInfoNtuple(fEventID, fParticleID, fStoredEdep);

  fParticleID.clear();
  fStoredEdep.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
