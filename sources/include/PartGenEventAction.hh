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
/// \file PartGenEventAction.hh
/// \brief Definition of the PartGenEventAction class

#ifndef PartGenEventAction_h
#define PartGenEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "PartGenHit.hh"
#include "PartGenEventMessenger.hh"

// class PartGenRunAction;
class PartGenEventMessenger; 

/// Event action class

class PartGenEventAction : public G4UserEventAction
{
  public:
    PartGenEventAction();
    virtual ~PartGenEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void Cntr(G4int i) { fCntr = i; } 

    // void AddEdep(G4double edep)   { fEdep  += edep;  }
    // void AddTrLen(G4double trLen) { fTrLen += trLen; }
    // void SetMomentum(G4ThreeVector P) { fPx = P.x(); fPy = P.y(); fPz = P.z(); } 
    // void SetPosition(G4ThreeVector Q) { fx  = Q.x(); fy  = Q.y(); fz  = Q.z(); } 

    void SetVerbosity(G4int v) { fVerbosity = v; } 

  private:
    // PartGenRunAction* fRunAction;
    // G4double fEdep;
    // G4double fTrLen;
    // G4double fPx,fPy,fPz;
    // G4double fx,fy,fz;
    G4int fCntr;
    G4int fVerbosity;

    PartGenEventMessenger *fMessenger;  

    PartGenHitsCollection *GetHitsCollection(G4int hcID,const G4Event *event) const;

};

#endif

    
