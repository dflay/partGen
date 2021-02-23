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
/// \file PartGenSteppingAction.cc
/// \brief Implementation of the PartGenSteppingAction class

#include "PartGenSteppingAction.hh"
#include "PartGenEventAction.hh"
#include "PartGenDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

PartGenSteppingAction::PartGenSteppingAction(PartGenEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}
//______________________________________________________________________________
PartGenSteppingAction::~PartGenSteppingAction()
{

}
//______________________________________________________________________________
void PartGenSteppingAction::UserSteppingAction(const G4Step* step)
{

  if (!fScoringVolume) { 
    const PartGenDetectorConstruction* detectorConstruction
      = static_cast<const PartGenDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }
 
  // total energy deposit  
  G4double edepStep = step->GetTotalEnergyDeposit()/GeV;

  // step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength()/mm;
  }

  // momentum 
  G4ThreeVector mom = step->GetTrack()->GetMomentum(); 
  // G4ThreeVector mom = step->GetTrack()->GetMomentum(); 

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if(volume==fScoringVolume){

  }else{
     // collect energy deposited and step length
     // note: these are accumulating  
     // fEventAction->AddEdep(edepStep); 
     // fEventAction->AddTrLen(stepLength);
     // fEventAction->SetMomentum(mom); 
  } 
 
  return;

}

