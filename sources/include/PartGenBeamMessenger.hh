// Messenger class for the detector construction class

#ifndef PartGenBeamMessenger_HH
#define PartGenBeamMessenger_HH

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include "PartGenPrimaryGeneratorAction.hh"

class PartGenPrimaryGeneratorAction; 

class PartGenBeamMessenger: public G4UImessenger { 

   public: 
      PartGenBeamMessenger(PartGenPrimaryGeneratorAction *pg);
      ~PartGenBeamMessenger();

      void SetNewValue(G4UIcommand *cmd,G4String newValue);

   private: 
      PartGenPrimaryGeneratorAction *fPriGen;

      G4UIdirectory *msgDir;

      G4UIcmdWithADoubleAndUnit *beamMomentumCmd;

};   

#endif 
