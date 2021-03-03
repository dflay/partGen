#include "PartGenPhysMessenger.hh"
//______________________________________________________________________________
PartGenPhysMessenger::PartGenPhysMessenger(PartGenPhysicsList *pl)
   :G4UImessenger(),
   fPhysList(pl),
   msgDir(0),
   cutCmd(0)   
{

  msgDir = new G4UIdirectory("/partGen/phys/");
  msgDir->SetGuidance("Setup commands"); 

  cutCmd = new G4UIcmdWithADoubleAndUnit("/partGen/phys/cutThreshold",this);
  cutCmd->SetGuidance("Cut threshold");
  cutCmd->SetParameterName("cutThreshold",true); // second argument = omittable? 

}
//______________________________________________________________________________
PartGenPhysMessenger::~PartGenPhysMessenger(){
  if(cutCmd) delete cutCmd;
  if(msgDir) delete msgDir; 
}
//______________________________________________________________________________
void PartGenPhysMessenger::SetNewValue(G4UIcommand *cmd,G4String newValue){

   if( cmd==cutCmd ){
      G4double p = cutCmd->GetNewDoubleValue(newValue);
      fPhysList->SetCutThr(p);   
   }

}

