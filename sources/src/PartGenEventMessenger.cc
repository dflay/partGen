#include "PartGenEventMessenger.hh"
//______________________________________________________________________________
PartGenEventMessenger::PartGenEventMessenger(PartGenEventAction *ea)
   :G4UImessenger(),
   fEvAct(ea),
   msgDir(0),
   verbCmd(0)   
{

  msgDir = new G4UIdirectory("/partGen/eventAction/");
  msgDir->SetGuidance("Setup commands"); 

  verbCmd = new G4UIcmdWithAnInteger("/partGen/eventAction/verbosity",this);
  verbCmd->SetGuidance("Verbosity");
  verbCmd->SetParameterName("verbosity",true); // second argument = omittable? 

}
//______________________________________________________________________________
PartGenEventMessenger::~PartGenEventMessenger(){
  if(verbCmd) delete verbCmd;
  if(msgDir)  delete msgDir; 
}
//______________________________________________________________________________
void PartGenEventMessenger::SetNewValue(G4UIcommand *cmd,G4String newValue){

   if( cmd==verbCmd ){
      G4int v = verbCmd->GetNewIntValue(newValue);
      fEvAct->SetVerbosity(v);   
   }

}

