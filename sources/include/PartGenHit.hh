#ifndef PART_GEN_HIT_HH
#define PART_GEN_HIT_HH

// a class for keeping track of hits  

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>
#include <fstream> 

class PartGenHit : public G4VHit
{
  public:
    PartGenHit();
    PartGenHit(const PartGenHit&);
    virtual ~PartGenHit();

    // operators
    const PartGenHit& operator=(const PartGenHit&);
    G4bool operator==(const PartGenHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw() {}
    virtual void Print();
    
    void PrintToFile(bool v=true)      { fPrintToCSV = v; }
    void PrintToCSV();  

    // setter methods 
    void Add(G4double de, G4double dl);
    void SetTotalEnergy(G4double E);
    void SetEdep(G4double edep);
    void SetBeta(G4double beta);
    void SetHitTime(G4double time);
    void SetTrackLength(G4double len);
    void SetMomentumMag(G4double pmag); 

    void SetTrackID(G4int trackID);
    void SetPID(G4int pid);
    void SetMID(G4int mid);

    void SetPos(G4ThreeVector v);
    void SetLabPos(G4ThreeVector v);
    void SetMomentum(G4ThreeVector m);

    // getter methods
    G4double GetEdep()        const;
    G4double GetTrackLength() const;
    G4double GetTotalEnergy() const;
    G4double GetMomentumMag() const;
    G4double GetHitTime()     const;
    G4double GetBeta()        const;

    G4int GetTrackID() const;
    G4int GetPID()     const;
    G4int GetMID()     const;

    G4ThreeVector GetPos()      const;
    G4ThreeVector GetLabPos()   const;
    G4ThreeVector GetMomentum() const;

  private:
    G4double fEdep;        // Energy deposit in the sensitive volume
    G4double fTrackLength; // Track length in the sensitive volume
    G4double fEtot;        // Total energy (at pre-step)
    G4double fBeta;        // Particle speed 
    G4double fHitTime;     // Time of hit 
    G4double fPmag;        // momentum magnitude  

    G4int fTrackID;        // Track number 
    G4int fPID;            // Particle type 
    G4int fMID;            // Material type 

    G4ThreeVector fPos;    // Local hit coordinate 
    G4ThreeVector fLabPos; // Global hit coordinate 
    G4ThreeVector fMom;    // Momentum

    bool fPrintToCSV;      // print data to csv? 
    unsigned long fCntr;   // a counter  

};

using PartGenHitsCollection = G4THitsCollection<PartGenHit>;
extern G4ThreadLocal G4Allocator<PartGenHit>* PartGenHitAllocator;

//______________________________________________________________________________
inline void* PartGenHit::operator new(size_t)
{
  if (!PartGenHitAllocator) {
    PartGenHitAllocator = new G4Allocator<PartGenHit>;
  }
  void *hit;
  hit = (void *) PartGenHitAllocator->MallocSingle();
  return hit;
}
//______________________________________________________________________________
inline void PartGenHit::operator delete(void *hit)
{
  if (!PartGenHitAllocator) {
    PartGenHitAllocator = new G4Allocator<PartGenHit>;
  }
  PartGenHitAllocator->FreeSingle((PartGenHit*) hit);
}
//______________________________________________________________________________
inline void PartGenHit::SetTrackID(G4int trackID){
   fTrackID = trackID;
}
//______________________________________________________________________________
inline void PartGenHit::Add(G4double de, G4double dl) {
  fEdep        += de;
  fTrackLength += dl;
}
//______________________________________________________________________________
inline void PartGenHit::SetTrackLength(G4double len){
   fTrackLength = len;
}
//______________________________________________________________________________
inline void PartGenHit::SetEdep(G4double edep){
   fEdep = edep;
}
//______________________________________________________________________________
inline void PartGenHit::SetTotalEnergy(G4double E){
   fEtot = E;
}
//______________________________________________________________________________
inline void PartGenHit::SetBeta(G4double beta){
   fBeta = beta;
}
//______________________________________________________________________________
inline void PartGenHit::SetHitTime(G4double time){
   fHitTime = time;
}
//______________________________________________________________________________
inline void PartGenHit::SetMomentumMag(G4double pmag){
   fPmag = pmag; 
}
//______________________________________________________________________________
inline void PartGenHit::SetPos(G4ThreeVector v){
   fPos = v;
}
//______________________________________________________________________________
inline void PartGenHit::SetLabPos(G4ThreeVector v){
   fLabPos = v;
}
//______________________________________________________________________________
inline void PartGenHit::SetMomentum(G4ThreeVector m){
   fMom = m;
}
//______________________________________________________________________________
inline void PartGenHit::SetPID(G4int pid){
   fPID = pid;
}
//______________________________________________________________________________
inline void PartGenHit::SetMID(G4int mid){
   fMID = mid;
}
//______________________________________________________________________________
inline G4double PartGenHit::GetEdep() const {
  return fEdep;
}
//______________________________________________________________________________
inline G4double PartGenHit::GetTrackLength() const {
  return fTrackLength;
}
//______________________________________________________________________________
inline G4double PartGenHit::GetTotalEnergy() const{
   return fEtot;
}
//______________________________________________________________________________
inline G4double PartGenHit::GetBeta() const{
   return fBeta;
}
//______________________________________________________________________________
inline G4double PartGenHit::GetHitTime() const{
   return fHitTime;
}
//______________________________________________________________________________
inline G4ThreeVector PartGenHit::GetPos() const{
   return fPos;
}
//______________________________________________________________________________
inline G4ThreeVector PartGenHit::GetLabPos() const{
   return fLabPos;
}
//______________________________________________________________________________
inline G4ThreeVector PartGenHit::GetMomentum() const{
   return fMom;
}
//______________________________________________________________________________
inline G4double PartGenHit::GetMomentumMag() const{
   return fPmag;
}
//______________________________________________________________________________
inline G4int PartGenHit::GetPID() const{
   return fPID;
}
//______________________________________________________________________________
inline G4int PartGenHit::GetMID() const{
   return fMID;
}
//______________________________________________________________________________
inline G4int PartGenHit::GetTrackID() const{
   return fTrackID;
}

#endif 
