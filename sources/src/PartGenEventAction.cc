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
/// \file PartGenEventAction.cc
/// \brief Implementation of the PartGenEventAction class

#include "PartGenEventAction.hh"
#include "PartGenRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//______________________________________________________________________________
PartGenEventAction::PartGenEventAction()
: G4UserEventAction()
  // fEdep(0.),fTrLen(0),fPx(0),fPy(0),fPz(0),fx(0),fy(0),fz(0)
{

} 
//______________________________________________________________________________
PartGenEventAction::~PartGenEventAction()
{

}
//______________________________________________________________________________
PartGenHitsCollection* PartGenEventAction::GetHitsCollection(G4int hcID, const G4Event *event) const {

   auto hitsCollection = static_cast<PartGenHitsCollection*>( event->GetHCofThisEvent()->GetHC(hcID) );

   if ( ! hitsCollection ) {
      G4ExceptionDescription msg;
      msg << "Cannot access hitsCollection ID " << hcID;
      G4Exception("BDEventAction::GetHitsCollection()",
	    "MyCode0003", FatalException, msg);
   }

   return hitsCollection;  
}
//______________________________________________________________________________
void PartGenEventAction::BeginOfEventAction(const G4Event* event)
{ 
  // fEdep=0; 
  // fTrLen=0;
  // fPx = 0; fPy = 0; fPz = 0;
  // fx = 0; fy = 0; fz = 0;
}
//______________________________________________________________________________
void PartGenEventAction::EndOfEventAction(const G4Event* event)
{   
   // accumulate statistics in run action
   // fRunAction->AddEdep(fEdep);

   // get analysis manager
   // auto analysisManager = G4AnalysisManager::Instance();
  
   // analysisManager->FillH1(0,fEdep);
   // analysisManager->FillH1(1,fTrLen);

   // analysisManager->FillNtupleDColumn(0,fEdep);
   // analysisManager->FillNtupleDColumn(1,fTrLen);
   // analysisManager->FillNtupleDColumn(2,fPx);
   // analysisManager->FillNtupleDColumn(3,fPy);
   // analysisManager->FillNtupleDColumn(4,fPz);

   // analysisManager->AddNtupleRow();

   auto eventID = event->GetEventID();

   // Get hits collections IDs (only once)
   int fHCID = G4SDManager::GetSDMpointer()->GetCollectionID("detHitsCollection");
   // std::cout << "HitsCollection ID = " << fHCID << std::endl;

   // Get hits collections
   auto HC = GetHitsCollection(fHCID,event);

   int NHits = HC->entries();
   if(NHits==0){
      // std::cout << "WARNING: NO HITS!" << std::endl;
      return;
   }

   // get analysis manager
   auto analysisManager = G4AnalysisManager::Instance();

   G4double EDEP=0,ETOT=0,TLEN=0;
   G4double EDEP_sum=0,ETOT_sum=0,TLEN_sum=0,pmag_sum=0;
   G4double x=0,y=0,z=0;
   G4double lx=0,ly=0,lz=0;
   G4double px=0,py=0,pz=0,pmag=0;

   // loop over all hits
   if(NHits>0) std::cout << "**** Found " << NHits << " hits" << std::endl;
   for(int i=0;i<NHits;i++){
      auto theHit = (*HC)[i];   // get the hit  
      // sum over hits 
      EDEP = theHit->GetEdep()/CLHEP::GeV;
      ETOT = theHit->GetTotalEnergy()/CLHEP::GeV;
      TLEN = theHit->GetTrackLength()/CLHEP::mm;
      pmag = theHit->GetMomentumMag()/(CLHEP::GeV/CLHEP::c_light);

      G4ThreeVector pos = theHit->GetPos();
      x = pos.getX()/CLHEP::mm;
      y = pos.getY()/CLHEP::mm;
      z = pos.getZ()/CLHEP::mm;

      G4ThreeVector labPos = theHit->GetLabPos();
      lx = labPos.getX()/CLHEP::mm;
      ly = labPos.getY()/CLHEP::mm;
      lz = labPos.getZ()/CLHEP::mm;

      G4ThreeVector mom = theHit->GetMomentum();
      px = mom.getX()/(CLHEP::GeV/CLHEP::c_light);
      py = mom.getY()/(CLHEP::GeV/CLHEP::c_light);
      pz = mom.getZ()/(CLHEP::GeV/CLHEP::c_light);

      std::cout << "[PartGenEventAction::EndOfEventAction]: Event " << eventID << std::endl;
      std::cout << "hit = " << i << std::endl;
      std::cout << "Edep = " << EDEP << " GeV" << std::endl;
      std::cout << "x_lab = " << lx << " mm, y_lab = " << ly << " mm, z_lab = " << lz << " mm" << std::endl;
      std::cout << "px = " << px << " GeV/c, py = " << py << " GeV/c, pz = " << pz << " GeV/c, |p| = " << pmag << " GeV/c" << std::endl;
      std::cout << "----" << std::endl;

      // analysisManager->FillNtupleDColumn(0 ,EDEP );
      // analysisManager->FillNtupleDColumn(1 ,TLEN );
      // analysisManager->FillNtupleDColumn(2 ,ETOT );
      analysisManager->FillNtupleDColumn(3 ,x    );
      analysisManager->FillNtupleDColumn(4 ,y    );
      analysisManager->FillNtupleDColumn(5 ,z    );
      analysisManager->FillNtupleDColumn(6 ,lx   );
      analysisManager->FillNtupleDColumn(7 ,ly   );
      analysisManager->FillNtupleDColumn(8 ,lz   );
      analysisManager->FillNtupleDColumn(9 ,px   );
      analysisManager->FillNtupleDColumn(10,py   );
      analysisManager->FillNtupleDColumn(11,pz   );
      // analysisManager->FillNtupleDColumn(12,pmag);

      EDEP_sum += EDEP;
      ETOT_sum += ETOT;
      TLEN_sum += TLEN;
      // pmag_sum += pmag;
      if(i==0) pmag_sum = pmag; // keep the initial momentum here... 
   }

   std::cout << "Edep sum = " << EDEP_sum << " GeV" << std::endl;
   std::cout << "===== End of event" << std::endl;

   // fill histograms
   analysisManager->FillH1(0,EDEP_sum);
   analysisManager->FillH1(1,TLEN_sum);

   // fill ntuple
   analysisManager->FillNtupleDColumn(0 ,EDEP_sum );
   analysisManager->FillNtupleDColumn(1 ,TLEN_sum );
   analysisManager->FillNtupleDColumn(2 ,ETOT_sum );
   analysisManager->FillNtupleDColumn(12,pmag_sum );
   analysisManager->AddNtupleRow();

}

