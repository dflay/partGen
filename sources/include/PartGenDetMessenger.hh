// Messenger class for the detector construction class

#ifndef PartGenDetMessenger_HH
#define PartGenDetMessenger_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include "PartGenDetectorConstruction.hh"

class PartGenDetectorConstruction; 

class PartGenDetMessenger: public G4UImessenger { 

   public: 
      PartGenDetMessenger(PartGenDetectorConstruction *dc);
      ~PartGenDetMessenger();

      void SetNewValue(G4UIcommand *cmd,G4String newValue);

   private: 
      PartGenDetectorConstruction *fDetCon;

      G4UIdirectory *msgDir;

      G4UIcmdWithAString *tgtMaterialCmd; 

      // target commands
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
