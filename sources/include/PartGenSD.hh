// Sensitive Detector class 
// - Defines what happens event-by-event for the target using the PartGenHit class  

#ifndef PART_GEN_SD_HH
#define PART_GEN_SD_HH

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "PartGenHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class PartGenSD : public G4VSensitiveDetector
{
  public:
    PartGenSD(const G4String& name,
                   const G4String& hitsCollectionName);
    virtual ~PartGenSD();

    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    PartGenHitsCollection* fHitsCollection;
};

#endif
