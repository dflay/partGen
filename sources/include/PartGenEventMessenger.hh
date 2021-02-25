// Messenger class for the detector construction class

#ifndef PartGenEventMessenger_HH
#define PartGenEventMessenger_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

#include "PartGenEventAction.hh"

class PartGenEventAction; 

class PartGenEventMessenger: public G4UImessenger { 

   public: 
      PartGenEventMessenger(PartGenEventAction *ea);
      ~PartGenEventMessenger();

      void SetNewValue(G4UIcommand *cmd,G4String newValue);

   private: 
      PartGenEventAction *fEvAct;

      G4UIdirectory *msgDir;

      G4UIcmdWithAnInteger *verbCmd;

};   

#endif 
