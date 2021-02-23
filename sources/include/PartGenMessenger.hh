#ifndef PartGenMessenger_HH
#define PartGenMessenger_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "PartGenDetectorConstruction.hh"
#include "PartGenPrimaryGeneratorAction.hh"

// class PartGenDetectorConstruction;
// class PartGenPrimaryGeneratorAction; 

class PartGenMessenger: public G4UImessenger { 

   public: 
      PartGenMessenger();
      ~PartGenMessenger();

      void SetDetCon(PartGenDetectorConstruction *dc)    { fDetCon = dc;  } 
      void SetPriGen(PartGenPrimaryGeneratorAction *pga) { fPriGen = pga; } 

      void SetNewValue(G4UIcommand *cmd,G4String newValue);

   private: 
      PartGenDetectorConstruction *fDetCon;
      PartGenPrimaryGeneratorAction *fPriGen;

      // target commands
      G4UIcmdWithADoubleAndUnit *beamEnergyCmd;
      G4UIcmdWithADoubleAndUnit *tgtXsizeCmd;
      G4UIcmdWithADoubleAndUnit *tgtYsizeCmd;
      G4UIcmdWithADoubleAndUnit *tgtZsizeCmd;

      // detector commands
      G4UIcmdWithADoubleAndUnit *detXsizeCmd;
      G4UIcmdWithADoubleAndUnit *detYsizeCmd;
      G4UIcmdWithADoubleAndUnit *detZsizeCmd;

      G4UIcmdWithADoubleAndUnit *detXposCmd;
      G4UIcmdWithADoubleAndUnit *detYposCmd;
      G4UIcmdWithADoubleAndUnit *detZposCmd;

};   

#endif 
