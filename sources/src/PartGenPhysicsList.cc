#include "PartGenPhysicsList.hh"
//______________________________________________________________________________
PartGenPhysicsList::PartGenPhysicsList()
   : G4VModularPhysicsList()
{
  // copying the G4SBS physics list 

  G4LossTableManager::Instance();

  G4int verb = 0;
  SetVerboseLevel(verb);

  RegisterPhysics( new G4DecayPhysics(verb)           );
  RegisterPhysics( new G4EmStandardPhysics(verb)      );
  RegisterPhysics( new G4EmExtraPhysics(verb)         );
  RegisterPhysics( new G4HadronElasticPhysics(verb)   );
  RegisterPhysics( new G4IonPhysics(verb)             );
  RegisterPhysics( new G4NeutronTrackingCut(verb)     );
  RegisterPhysics( new G4HadronPhysicsFTFP_BERT(verb) );
  RegisterPhysics( new G4StoppingPhysics(verb)        );
  RegisterPhysics( new G4StepLimiterPhysics(verb)     );

  cutGamma    = 0;
  cutElectron = 0;
  cutPositron = 0;
  cutProton   = 0;

  // Geant4 default 
  defaultCutValue = 1.0*CLHEP::mm;

  fMessenger = new PartGenPhysMessenger(this); 

  // std::cout << "[PartGenPhysicsList]: Default cut value is " << defaultCutValue/mm << " mm" << std::endl;
 
  G4Transportation::EnableUseMagneticMoment(true);

}
//______________________________________________________________________________
PartGenPhysicsList::~PartGenPhysicsList(){
   delete fMessenger;
}
//______________________________________________________________________________
void PartGenPhysicsList::SetCuts(){
  // SetParticleCuts( cutGamma, G4Gamma::Gamma() );
  // SetParticleCuts( cutElectron, G4Electron::Electron() );
  // SetParticleCuts( cutPositron, G4Positron::Positron() );
  // SetParticleCuts( cutProton, G4Proton::Proton() );
  std::cout << "[PartGenPhysicsList::SetCuts]: Cut value is " << defaultCutValue/mm << " mm" << std::endl;
  SetCutsWithDefault();
}

