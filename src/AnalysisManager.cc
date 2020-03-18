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
/// \file analysis/AnaEx02/src/HistoManager.cc
/// \brief Implementation of the AnalysisManager class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "AnalysisManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AnalysisManager::AnalysisManager()
: fRootFile(0), 
  fTEdepNtuple(0), 
  fParticleInfoNtuple(0), 
  fTEdep(0.),
  fEventID(0),
  fSize(0),
  fParticleID(0),
  fEdep(0.)
{
      
  // histograms
  for (G4int k=0; k<kMaxHisto; k++) fHisto[k] = 0;
    
  // ntuple
  fTEdepNtuple = 0;
  fParticleInfoNtuple = 0;
  fSize = 0;

  fInitialised = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AnalysisManager::~AnalysisManager()
{
  if (fRootFile) delete fRootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AnalysisManager::Initialise()
{ 
  // Creating a tree container to handle histograms and ntuples.
  // This tree is associated to an output file.
  //
  G4String fileName = "ProtonAnalysis.root";
  fRootFile = new TFile(fileName,"RECREATE");
  if (! fRootFile) {
    G4cout << " AnalysisManager::Initialise :" 
           << " problem creating the ROOT TFile "
           << G4endl;
    return;
  }
  
  // id = 0
  fHisto[0] = new TH1D("TotalEdep", "Total Energy Deposited in Water (GeV)",
                        100, 0., 1000*CLHEP::GeV);

  for ( G4int i=0; i<kMaxHisto; ++i ) {
    if (! fHisto[i]) G4cout << "\n can't create histo " << i << G4endl;
  }  

  // create 1st ntuple
  fTEdepNtuple = new TTree("TotalEdep", "Total Energy Deposited in Water");
  fTEdepNtuple->Branch("TotalEdep", &fTEdep, "TotalEdep/D");

  // create 2nd ntuple 
  fParticleInfoNtuple = new TTree("ParticleInfo", 
                        "Information about Particles that Reached the Water");
  fParticleInfoNtuple->Branch("EventID", &fEventID, "EventID/I"); 
  //fParticleInfoNtuple->Branch("ParticleID", fParticleID, "ParticleID[fSize]/I");
  //fParticleInfoNtuple->Branch("Edep", fEdep, "Edep[fSize]/D");
 
  G4cout << "\n----> Output file is open in " << fileName << G4endl;

  fInitialised = true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AnalysisManager::Save()
{ 
  if (! fRootFile) return;
  
  if (fInitialised)
  {
    fRootFile->Write();       // Writing the histograms to the file   
    fRootFile->Close();       // and closing the tree (and the file)  
                                                                      
    G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl; 

    fInitialised = false;
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AnalysisManager::FillHisto(G4int ih, G4double xvalue, G4double weight)
{
  if (ih >= kMaxHisto) {
    G4cerr << "---> warning from AnalysisManager::FillHisto() : histo " << ih
           << " does not exist. (xbin=" << xvalue << " weight=" << weight << ")"
           << G4endl;
    return;
  }
  if  (fHisto[ih]) { fHisto[ih]->Fill(xvalue, weight); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AnalysisManager::FillTotalEdepNtuple(G4double totalEnergyAbs)
{
  fTEdep = totalEnergyAbs;
  G4cout << "Storing total energy deposition, value: " << fTEdep << G4endl;
  //if (fTEdepNtuple) 
  fTEdepNtuple->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AnalysisManager::FillParticleInfoNtuple(G4int eventID)
                                          //, G4int size, 
                                          //std::vector<int> particleID,
                                          //std::vector<double> edep)
{                                                                                
  fEventID = eventID;
  //fSize = size;
  //fParticleID = particleID;
  //fEdep = edep;

  if (fParticleInfoNtuple) fParticleInfoNtuple->Fill();                          
}                                                                                
                                                                                 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

