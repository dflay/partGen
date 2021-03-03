// Messenger class for the detector construction class

#ifndef PartGenPhysMessenger_HH
#define PartGenPhysMessenger_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include "PartGenPhysicsList.hh"

class PartGenPhysicsList; 

class PartGenPhysMessenger: public G4UImessenger { 

   public: 
      PartGenPhysMessenger(PartGenPhysicsList *pl);
      ~PartGenPhysMessenger();

      void SetNewValue(G4UIcommand *cmd,G4String newValue);

   private: 
      PartGenPhysicsList *fPhysList;

      G4UIdirectory *msgDir;

      G4UIcmdWithADoubleAndUnit *cutCmd;

};   

#endif 
