#ifndef PartGenPhysicsList_h 
#define PartGenPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4LossTableManager.hh"
//#include "G4PhysListFactory.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
//#include "HadronPhysicsQGSP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4ProcessManager.hh"
//#include "G4DataQuestionaire.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4Transportation.hh"
#include "G4PhysicsListHelper.hh"

#include "PartGenPhysMessenger.hh"

#include <vector>

// copying the G4SBS physics list 
class PartGenPhysMessenger; 

class PartGenPhysicsList : public G4VModularPhysicsList
{
   public:
      PartGenPhysicsList();
      virtual ~PartGenPhysicsList();

      void SetCutThr(double thr) { std::cout << "**** Setting default cut to " << thr/mm << " mm" << std::endl; defaultCutValue = thr; } 

      void SetCuts();
      // void ConstructOptical();
      // void SetOpticalPhysicsProcessActive( G4int, G4bool );
      // inline G4VPhysicsConstructor *GetOpticalPhysics() const { return PartGenOpticalPhysics; }
      // void SetOpticalPhysics( G4VPhysicsConstructor *c ){ PartGenOpticalPhysics = c; }
      // void ToggleCerenkov(G4bool);
      // void ToggleScintillation(G4bool);

   private:

      //G4bool UseOptical;

      G4double cutGamma;
      G4double cutElectron;
      G4double cutPositron;
      G4double cutProton;
      PartGenPhysMessenger *fMessenger;

      // G4VPhysicsConstructor *PartGenOpticalPhysics;
      // G4VPhysicsConstructor *PartGenEMPhysics;
      // G4VPhysicsConstructor *PartGenParticleList;
      // vector<G4VPhysicsConstructor*> PartGenHadronicPhysics;
      // G4VPhysicsConstructor *PartGenOpticalPhysics;

      // void ConstructParticle();
      // virtual void ConstructProcess();

};

#endif

