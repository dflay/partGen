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
/// \file PartGenRunAction.cc
/// \brief Implementation of the PartGenRunAction class

#include "PartGenRunAction.hh"
#include "PartGenPrimaryGeneratorAction.hh"
#include "PartGenDetectorConstruction.hh"
// #include "PartGenRun.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//______________________________________________________________________________
PartGenRunAction::PartGenRunAction()
: G4UserRunAction()
{

  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // set up output ROOT file
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "[PartGenRunAction]: Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple

  // Creating histograms
  analysisManager->CreateH1("Edep","Edep in tgt", 100, 0.,15.);     
  analysisManager->CreateH1("TrLen","Track Length in tgt", 100, 0.,50*cm);     

  // Creating ntuple
  analysisManager->CreateNtuple("partGen","Energy, momentum, and Position");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->CreateNtupleDColumn("TrLen");
  analysisManager->CreateNtupleDColumn("Etot");
  // position 
  analysisManager->CreateNtupleDColumn("xPos");
  analysisManager->CreateNtupleDColumn("yPos");
  analysisManager->CreateNtupleDColumn("zPos");
  // analysisManager->CreateNtupleDColumn("xLabPos");
  // analysisManager->CreateNtupleDColumn("yLabPos");
  // analysisManager->CreateNtupleDColumn("zLabPos");
  // momentum 
  analysisManager->CreateNtupleDColumn("Px");
  analysisManager->CreateNtupleDColumn("Py");
  analysisManager->CreateNtupleDColumn("Pz");
  analysisManager->CreateNtupleDColumn("P");
  // other useful info
  analysisManager->CreateNtupleDColumn("hit");
  analysisManager->CreateNtupleDColumn("pid");  
  analysisManager->CreateNtupleDColumn("evid");  

  analysisManager->FinishNtuple();

}
//______________________________________________________________________________
PartGenRunAction::~PartGenRunAction()
{
  delete G4AnalysisManager::Instance();
}
//______________________________________________________________________________
void PartGenRunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  // G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  analysisManager->OpenFile("outData");  // argument is the filename

}
//______________________________________________________________________________
void PartGenRunAction::EndOfRunAction(const G4Run*)
{

  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(0) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl;
    } 
    else {
      G4cout << "for the local thread " << G4endl << G4endl;
    } 
    G4cout << " Edep : mean = " 
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
  } 
  
  // save histograms & ntuple
  analysisManager->Write();
  analysisManager->CloseFile();

}
