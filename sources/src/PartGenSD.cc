#include "PartGenSD.hh"
//______________________________________________________________________________
PartGenSD::PartGenSD(
                            const G4String& name,
                            const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr)
{
  collectionName.insert(hitsCollectionName);
}
//______________________________________________________________________________
PartGenSD::~PartGenSD()
{

}
//______________________________________________________________________________
void PartGenSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection = new PartGenHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );

}
//______________________________________________________________________________
G4bool PartGenSD::ProcessHits(G4Step* step,G4TouchableHistory*)
{

  // energy deposit
  auto edep = step->GetTotalEnergyDeposit();

  // step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }

  if ( edep==0. && stepLength == 0. ) return false;

  // create a hit 
  PartGenHit *hit = new PartGenHit();

  // auto touchable = (step->GetPreStepPoint()->GetTouchable());

  if(!hit){
    G4ExceptionDescription msg;
    msg << "Cannot access hit! ";
    G4Exception("PartGenSD::ProcessHits()","MyCode0004", FatalException, msg);
  }

  // grab info from step 
  G4ThreeVector mom = step->GetPreStepPoint()->GetMomentum();
  G4double E        = step->GetPreStepPoint()->GetTotalEnergy();    // total enegy of the track (= T + m) 
  G4double pMag     = step->GetPreStepPoint()->GetMomentum().mag(); // Momentum of particle that caused hit prior to the step

  G4int trackID     = step->GetTrack()->GetTrackID();
  G4int pid         = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
  G4int mid         = step->GetTrack()->GetParentID();

  G4double beta     = step->GetPreStepPoint()->GetBeta();       // v/c of particle *prior* to step 
  G4double hitTime  = step->GetPreStepPoint()->GetGlobalTime(); // time right before the current step   

  // set hit details
  hit->SetPID(pid);
  hit->SetMID(mid);
  hit->SetTrackID(trackID);
  hit->SetMomentum(mom); 
  hit->SetMomentumMag(pMag); 
  hit->SetEdep(edep);
  hit->SetTrackLength(stepLength);
  hit->SetTotalEnergy(E);
  hit->SetBeta(beta);
  hit->SetHitTime(hitTime);

  // extra stuff 
  // Used to retrieve coordinate transformations relevant to spectrometer coordinate system:
  G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();     // in the lab coordinates
  hit->SetPos(pos);
  // transform position into local coordinates of detector 
  G4TouchableHistory* hist = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
  G4AffineTransform aTrans = hist->GetHistory()->GetTopTransform();
  pos = aTrans.TransformPoint(pos);
  hit->SetLabPos(pos);

  // now append to vector 
  fHitsCollection->insert(hit);

  return true;
}
//______________________________________________________________________________
void PartGenSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) {
     auto nofHits = fHitsCollection->entries();
     G4cout
       << G4endl
       << "-------->Hits Collection: in this event they are " << nofHits
       << " hits in the tracker chambers: " << G4endl;
     for ( std::size_t i=0; i<nofHits; ++i ) (*fHitsCollection)[i]->Print();
  }
}

