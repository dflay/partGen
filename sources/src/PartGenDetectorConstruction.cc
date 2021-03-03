#include "PartGenDetectorConstruction.hh"
//______________________________________________________________________________
PartGenDetectorConstruction::PartGenDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0),fMessenger(0),fDebug(false),fCheckOverlaps(true)
{ 

   fTgtXSize = 5.*cm;
   fTgtYSize = 5.*cm;
   fTgtZSize = 5.*mm;

   fDetXSize = 15.*cm;
   fDetYSize = 15.*cm;
   fDetZSize = 1.*mm;

   fDetX     = 0.*cm;
   fDetY     = 0.*cm;
   fDetZ     = 5.*cm;

   fTgtMaterialName = "Aluminum"; 
   fDetMaterialName = "Air"; 

   fMessenger = new PartGenDetMessenger(this); 
 
}
//______________________________________________________________________________
PartGenDetectorConstruction::~PartGenDetectorConstruction()
{ 
   delete fMessenger;
}
//______________________________________________________________________________
G4VPhysicalVolume* PartGenDetectorConstruction::Construct()
{  
    
  // build materials 
  if( fMaterialsMap.empty() ) ConstructMaterials();

  return ConstructGeometries(); 
}
//______________________________________________________________________________
G4VPhysicalVolume *PartGenDetectorConstruction::ConstructGeometries(){

  // World
  G4double world_sizeXY = 5*m;
  G4double world_sizeZ  = 10*m;
  G4Material* world_mat = GetMaterial("Vacuum"); 
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);        //overlaps checking

  // build target  
  BuildTarget(logicWorld); 

  // build detector  
  BuildDetector(logicWorld); 

  // beam path (for reference only) 
  // BuildBeamRef(logicWorld);  

  // always return the physical World
  return physWorld;

}
//______________________________________________________________________________
void PartGenDetectorConstruction::BuildTarget(G4LogicalVolume *logicMother){
   // build the target 

   G4double x_len = fTgtXSize; // length along horizontal axis 
   G4double y_len = fTgtYSize; // length along vertical axis 
   G4double z_len = fTgtZSize; // length along beam axis 

   // std::cout << "****** TARGET MATERIAL: " << fTgtMaterialName << std::endl;
   // std::cout << "****** TARGET SIZE:     " << x_len/cm << " cm, " << y_len/cm << " cm, " << z_len/cm << " cm" << std::endl;

   G4Box *tgtShape = new G4Box("tgtShape",x_len/2.,y_len/2.,z_len/2.);

   G4VisAttributes *vis = new G4VisAttributes(); 
   vis->SetColour( G4Colour::White() );

   G4LogicalVolume *logicTgt = new G4LogicalVolume(tgtShape,GetMaterial(fTgtMaterialName),"logicTarget"); 
   logicTgt->SetVisAttributes(vis);

   bool checkOverlaps = true;  

   new G4PVPlacement(0,                    // rotation relative to mother         
	             G4ThreeVector(0,0,0), // position relative to mother           
                     logicTgt,             // logical object     
                     "physTarget",         // name of physical placement     
                     logicMother,          // logical mother       
                     false,                // boolean object? (true or false)    
                     0,                    // copy number   
                     checkOverlaps);       // check overlaps       

   // make it a sensitive detector  
   PartGenSD *mySD = new PartGenSD("det","detHitsCollection");
   G4SDManager::GetSDMpointer()->AddNewDetector(mySD); 
   logicTgt->SetSensitiveDetector(mySD);  
   
}
//______________________________________________________________________________
void PartGenDetectorConstruction::BuildDetector(G4LogicalVolume *logicMother){
   // build the target 

   G4double x_len = fDetXSize; // length along horizontal axis 
   G4double y_len = fDetYSize; // length along vertical axis 
   G4double z_len = fDetZSize; // length along beam axis

   // std::cout << "****** DETECTOR MATERIAL: " << fDetMaterialName << std::endl; 
   // std::cout << "****** DETECTOR SIZE:     " << x_len/cm << " cm, " << y_len/cm << " cm, " << z_len/cm << " cm" << std::endl;

   G4Box *detShape = new G4Box("detShape",x_len/2.,y_len/2.,z_len/2.);

   G4VisAttributes *vis = new G4VisAttributes(); 
   vis->SetColour( G4Colour::Magenta() );

   G4LogicalVolume *logicDet = new G4LogicalVolume(detShape,GetMaterial(fDetMaterialName),"logicDet"); 
   logicDet->SetVisAttributes(vis);

   bool checkOverlaps = true;  

   // location of our detector plane 
   G4double x = fDetX; 
   G4double y = fDetY; 
   G4double z = fDetZ; 

   new G4PVPlacement(0,                    // rotation relative to mother         
	             G4ThreeVector(x,y,z), // position relative to mother           
                     logicDet,             // logical object     
                     "physDet",            // name of physical placement     
                     logicMother,          // logical mother       
                     false,                // boolean object? (true or false)    
                     0,                    // copy number   
                     checkOverlaps);       // check overlaps       

   // // make it a sensitive detector  
   // PartGenSD *mySD = new PartGenSD("det","detHitsCollection");
   // G4SDManager::GetSDMpointer()->AddNewDetector(mySD); 
   // logicDet->SetSensitiveDetector(mySD);  

}
//______________________________________________________________________________
void PartGenDetectorConstruction::BuildBeamRef(G4LogicalVolume *logicMother){
   // build the nominal trajectory of the beam to use as a reference

   G4double r_min    = 0.*mm; 
   G4double r_max    = 2.*mm; 
   G4double length   = 5.*m;
   G4double dPhi     = 360.*deg;
   G4double startPhi = 0*deg; 

   G4Tubs *beamShape = new G4Tubs("beam",
                                  r_min    ,r_max,
                                  length/2.,
                                  startPhi ,dPhi); 
  
   G4VisAttributes *vis = new G4VisAttributes();
   vis->SetColour( G4Colour::Blue() ); 

   G4LogicalVolume *logicBeam = new G4LogicalVolume(beamShape,GetMaterial("G4air"),"logicBeam");
   logicBeam->SetVisAttributes(vis); 

   new G4PVPlacement(0,                     // rotation relative to mother         
                     G4ThreeVector(0,0,0),  // position relative to mother           
                     logicBeam,             // logical object     
                     "physBeam",            // name of physical placement     
                     logicMother,           // logical mother       
                     false,                 // boolean object? (true or false)    
                     0,                     // copy no   
                     fCheckOverlaps);       // check overlaps      

}
//______________________________________________________________________________
G4Material *PartGenDetectorConstruction::GetMaterial(G4String name){

  std::map<G4String, G4Material*>::iterator it = fMaterialsMap.find( name );

  if( it != fMaterialsMap.end() ){
    return fMaterialsMap[name];
  } else {
    std::cout << "[PartGenDetectorConstruction::GetMaterial]: ERROR Material " << name.data() 
              << " not found! " << std::endl;
    exit(1);
    return NULL;
  }

}
//______________________________________________________________________________
int PartGenDetectorConstruction::ConstructMaterials(){

   // Get nist material manager
   G4NistManager* nist = G4NistManager::Instance();

   // world material 
   G4Material *G4Air = nist->FindOrBuildMaterial("G4_AIR");
   fMaterialsMap["Air"] = G4Air; 

   // Define elements, compounds here that we'll need 
   // We don't need to supply the molar mass, because G4NistManager does it for us!
   G4int Z,A;
   // G4double N,A,ncomponents,nel,abundance;

   G4String name;

   // G4Element *elH  = nist->FindOrBuildElement("H"); 
   // G4Element *elO  = nist->FindOrBuildElement("O");
   G4Element *elC  = nist->FindOrBuildElement("C");
   G4Element *elAl = nist->FindOrBuildElement("Al");
   // G4Element *elSi = nist->FindOrBuildElement("Si");
   // G4Element *elCa = nist->FindOrBuildElement("Ca");
   // G4Element *elSr = nist->FindOrBuildElement("Sr");
   // G4Element *elBa = nist->FindOrBuildElement("Ba");
   G4Element *elCu = nist->FindOrBuildElement("Cu");
   G4Element *elMn = nist->FindOrBuildElement("Mn"); 
   G4Element *elFe = nist->FindOrBuildElement("Fe"); 
   G4Element *elS  = nist->FindOrBuildElement("S"); 
   G4Element *elP  = nist->FindOrBuildElement("P"); 
   G4Element *elW  = nist->FindOrBuildElement("W"); 

   // Cu
   G4Material *Cu = new G4Material("Copper",8.96*g/cm3,1.); 
   Cu->AddElement(elCu,1);  
   fMaterialsMap["Copper"] = Cu;

   // Al 
   G4Material *Al = new G4Material("Aluminum",2.7*g/cm3,1.); 
   Al->AddElement(elAl,1); 
   fMaterialsMap["Aluminum"] = Al;

   // Tungsten 
   G4Material *Tungsten = new G4Material("Tungsten",19.3*g/cm3,1.);
   Tungsten->AddElement(elW,1); 
   fMaterialsMap["Tungsten"] = Tungsten;  

   // for the support materials 
   G4Material *Steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
   fMaterialsMap["Stainless_Steel"] = Steel; 

   // AISI 1008 carbon steel
   // details from http://www.iron-foundry.com/AISI-1008-SAE-UNS-G10080-Carbon-Steel-Foundry.html
   // NOTE: will throw a warning because this doesn't add to 100% (adds to 99.8%)
   G4Material *Carbon_Steel_1008 = new G4Material("Carbon_Steel_1008",7.872*g/cm3,5); 
   Carbon_Steel_1008->AddElement(elFe,0.9931);   
   Carbon_Steel_1008->AddElement(elMn,0.0030);  
   Carbon_Steel_1008->AddElement(elC ,0.0010); 
   Carbon_Steel_1008->AddElement(elS ,0.0005); 
   Carbon_Steel_1008->AddElement(elP ,0.0004); 
   fMaterialsMap["Carbon_Steel_1008"] = Carbon_Steel_1008; 

   // print for confirmation
   if(fDebug){
      std::cout << "Constructed materials: " << std::endl; 
      for(auto it=fMaterialsMap.cbegin(); it!=fMaterialsMap.cend(); ++it){
	 std::cout << (*it).first << ": " << (*it).second << std::endl;
      }
   }

   // Vacuum
   G4double density; 
   G4Material *Vacuum = new G4Material(name="Vacuum", Z=1., A=1.0*g/mole, density=1e-9*g/cm3);
   fMaterialsMap["Vacuum"] = Vacuum;

   return 0;
}
