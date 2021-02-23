#include "PartGenMessenger.hh"
//______________________________________________________________________________
PartGenMessenger::PartGenMessenger(){

  beamEnergyCmd = new G4UIcmdWithADoubleAndUnit("/partGen/beamE",this);
  beamEnergyCmd->SetGuidance("Beam energy");
  beamEnergyCmd->SetParameterName("beamE",true); // second argument = omittable? 

  tgtXsizeCmd = new G4UIcmdWithADoubleAndUnit("/partGen/tgtXsize",this);
  tgtXsizeCmd->SetGuidance("Target x size");
  tgtXsizeCmd->SetParameterName("tgtXsize",true); // second argument = omittable? 

  tgtYsizeCmd = new G4UIcmdWithADoubleAndUnit("/partGen/tgtYsize",this);
  tgtYsizeCmd->SetGuidance("Target y size");
  tgtYsizeCmd->SetParameterName("tgtYsize",true); // second argument = omittable? 

  tgtZsizeCmd = new G4UIcmdWithADoubleAndUnit("/partGen/tgtZsize",this);
  tgtZsizeCmd->SetGuidance("Target z size");
  tgtZsizeCmd->SetParameterName("tgtZsize",true); // second argument = omittable? 

  detXsizeCmd = new G4UIcmdWithADoubleAndUnit("/partGen/detXsize",this);
  detXsizeCmd->SetGuidance("Detector x size");
  detXsizeCmd->SetParameterName("detXsize",true); // second argument = omittable? 

  detYsizeCmd = new G4UIcmdWithADoubleAndUnit("/partGen/detYsize",this);
  detYsizeCmd->SetGuidance("Detector y size");
  detYsizeCmd->SetParameterName("detYsize",true); // second argument = omittable? 

  detZsizeCmd = new G4UIcmdWithADoubleAndUnit("/partGen/detZsize",this);
  detZsizeCmd->SetGuidance("Detector z size");
  detZsizeCmd->SetParameterName("detZsize",true); // second argument = omittable? 

  detXposCmd = new G4UIcmdWithADoubleAndUnit("/partGen/detX",this);
  detXposCmd->SetGuidance("Detector x position");
  detXposCmd->SetParameterName("detX",true); // second argument = omittable? 

  detYposCmd = new G4UIcmdWithADoubleAndUnit("/partGen/detY",this);
  detYposCmd->SetGuidance("Detector y position");
  detYposCmd->SetParameterName("detY",true); // second argument = omittable? 

  detZposCmd = new G4UIcmdWithADoubleAndUnit("/partGen/detZ",this);
  detZposCmd->SetGuidance("Detector z position");
  detZposCmd->SetParameterName("detZ",true); // second argument = omittable? 

}
//______________________________________________________________________________
PartGenMessenger::~PartGenMessenger(){

}
//______________________________________________________________________________
void PartGenMessenger::SetNewValue(G4UIcommand *cmd,G4String newValue){

   if( cmd==beamEnergyCmd ){
      G4double be = beamEnergyCmd->GetNewDoubleValue(newValue);
      fPriGen->SetBeamEnergy(be);   
   }

   if( cmd==tgtXsizeCmd ){
      G4double xt_s = tgtXsizeCmd->GetNewDoubleValue(newValue);
      fDetCon->SetTgtXSize(xt_s);   
   }
   if( cmd==tgtYsizeCmd ){
      G4double yt_s = tgtYsizeCmd->GetNewDoubleValue(newValue);
      fDetCon->SetTgtYSize(yt_s);   
   }
   if( cmd==tgtZsizeCmd ){
      G4double zt_s = tgtZsizeCmd->GetNewDoubleValue(newValue);
      fDetCon->SetTgtZSize(zt_s);   
   }

   if( cmd==detXsizeCmd ){
      G4double xd_s = detXsizeCmd->GetNewDoubleValue(newValue);
      fDetCon->SetDetXSize(xd_s);   
   }
   if( cmd==detYsizeCmd ){
      G4double yd_s = detYsizeCmd->GetNewDoubleValue(newValue);
      fDetCon->SetDetYSize(yd_s);   
   }
   if( cmd==detZsizeCmd ){
      G4double zd_s = detZsizeCmd->GetNewDoubleValue(newValue);
      fDetCon->SetDetZSize(zd_s);   
   }

   if( cmd==detXposCmd ){
      G4double xd_p = detXposCmd->GetNewDoubleValue(newValue);
      fDetCon->SetDetX(xd_p);   
   }
   if( cmd==detYposCmd ){
      G4double yd_p = detYposCmd->GetNewDoubleValue(newValue);
      fDetCon->SetDetY(yd_p);   
   }
   if( cmd==detZposCmd ){
      G4double zd_p = detZposCmd->GetNewDoubleValue(newValue);
      fDetCon->SetDetZ(zd_p);   
   }

}

