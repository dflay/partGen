#include "PartGenBeamMessenger.hh"
//______________________________________________________________________________
PartGenBeamMessenger::PartGenBeamMessenger(PartGenPrimaryGeneratorAction *pg)
   :G4UImessenger(),
   fPriGen(pg),
   msgDir(0),
   beamMomentumCmd(0)   
{

  msgDir = new G4UIdirectory("/partGen/beam/");
  msgDir->SetGuidance("Setup commands"); 

  beamMomentumCmd = new G4UIcmdWithADoubleAndUnit("/partGen/beam/momentum",this);
  beamMomentumCmd->SetGuidance("Beam momentum (GeV)");
  beamMomentumCmd->SetParameterName("momentum",true); // second argument = omittable? 

}
//______________________________________________________________________________
PartGenBeamMessenger::~PartGenBeamMessenger(){
  if(beamMomentumCmd) delete beamMomentumCmd;
  if(msgDir)          delete msgDir; 
}
//______________________________________________________________________________
void PartGenBeamMessenger::SetNewValue(G4UIcommand *cmd,G4String newValue){

   if( cmd==beamMomentumCmd ){
      G4double p = beamMomentumCmd->GetNewDoubleValue(newValue);
      fPriGen->SetBeamMomentum(p);   
   }

}

