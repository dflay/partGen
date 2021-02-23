#include "PartGenDetectorConstruction.hh"
//______________________________________________________________________________
PartGenDetectorConstruction::PartGenDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0),fDebug(false),fCheckOverlaps(true)
{ 
 
}
//______________________________________________________________________________
PartGenDetectorConstruction::~PartGenDetectorConstruction()
{ 

}
//______________________________________________________________________________
G4VPhysicalVolume* PartGenDetectorConstruction::Construct()
{  

  // build materials 
  if( fMaterialsMap.empty() ) ConstructMaterials();

  // World
  G4double world_sizeXY = 5*m;
  G4double world_sizeZ  = 10*m;
  G4Material* world_mat = GetMaterial("G4air"); 
  
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

   G4double x_len = 5*cm; // length along horizontal axis 
   G4double y_len = 5*cm; // length along vertical axis 
   G4double z_len = 5*mm; // length along beam axis 

   G4Box *tgtShape = new G4Box("tgtShape",x_len/2.,y_len/2.,z_len/2.);

   G4VisAttributes *vis = new G4VisAttributes(); 
   vis->SetColour( G4Colour::White() );

   G4LogicalVolume *logicTgt = new G4LogicalVolume(tgtShape,GetMaterial("Copper"),"logicTarget"); 
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
   
}
//______________________________________________________________________________
void PartGenDetectorConstruction::BuildDetector(G4LogicalVolume *logicMother){
   // build the target 

   G4double x_len = 15*cm; // length along horizontal axis 
   G4double y_len = 15*cm; // length along vertical axis 
   G4double z_len = 1*mm; // length along beam axis 

   G4Box *detShape = new G4Box("detShape",x_len/2.,y_len/2.,z_len/2.);

   G4VisAttributes *vis = new G4VisAttributes(); 
   vis->SetColour( G4Colour::Magenta() );

   G4LogicalVolume *logicDet = new G4LogicalVolume(detShape,GetMaterial("G4air"),"logicDet"); 
   logicDet->SetVisAttributes(vis);

   bool checkOverlaps = true;  

   // location of our detector plane 
   G4double x = 0; 
   G4double y = 0; 
   G4double z = 5*cm; 

   new G4PVPlacement(0,                    // rotation relative to mother         
	             G4ThreeVector(x,y,z), // position relative to mother           
                     logicDet,             // logical object     
                     "physDet",            // name of physical placement     
                     logicMother,          // logical mother       
                     false,                // boolean object? (true or false)    
                     0,                    // copy number   
                     checkOverlaps);       // check overlaps       

   // make it a sensitive detector  
   PartGenSD *mySD = new PartGenSD("det","detHitsCollection");
   G4SDManager::GetSDMpointer()->AddNewDetector(mySD); 
   logicDet->SetSensitiveDetector(mySD);  

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
   fMaterialsMap["G4air"] = G4Air; 

   // Define elements, compounds here that we'll need 
   // We don't need to supply the molar mass, because G4NistManager does it for us!
   G4int Z,N,ncomponents,nel; 
   G4double abundance;

   G4Isotope *iso_3He = new G4Isotope( "He3", Z=2, N=3 );

   G4Element *el3He = new G4Element("Helium3","3He",ncomponents=1); //Define isotopically pure Helium-3 
   el3He->AddIsotope( iso_3He, abundance=100.0*perCent );

   G4Element *elH  = nist->FindOrBuildElement("H"); 
   G4Element *elO  = nist->FindOrBuildElement("O");
   G4Element *elC  = nist->FindOrBuildElement("C");
   G4Element *elAl = nist->FindOrBuildElement("Al");
   G4Element *elSi = nist->FindOrBuildElement("Si");
   G4Element *elCa = nist->FindOrBuildElement("Ca");
   G4Element *elSr = nist->FindOrBuildElement("Sr");
   G4Element *elBa = nist->FindOrBuildElement("Ba");
   G4Element *elCu = nist->FindOrBuildElement("Cu");
   G4Element *elMn = nist->FindOrBuildElement("Mn"); 
   G4Element *elFe = nist->FindOrBuildElement("Fe"); 
   G4Element *elS  = nist->FindOrBuildElement("S"); 
   G4Element *elP  = nist->FindOrBuildElement("P"); 

   // Cu
   G4Material *Cu = new G4Material("Copper",8.96*g/cm3,1.); 
   Cu->AddElement(elCu,1);  
   fMaterialsMap["Copper"] = Cu;

   // Al 
   G4Material *Al = new G4Material("Aluminum",2.7*g/cm3,1.); 
   Al->AddElement(elAl,1); 
   fMaterialsMap["Aluminum"] = Al; 

   G4Material* NEMAG10 = new G4Material("NEMAG10",1.70*g/cm3,nel=4);
   NEMAG10->AddElement(elSi, 1);
   NEMAG10->AddElement(elO , 2);
   NEMAG10->AddElement(elC , 3);
   NEMAG10->AddElement(elH , 3);
   fMaterialsMap["NEMAG10"] = NEMAG10; 

   // GE180   
   G4double bigden = 1e9*g/cm3; // why so big? To make these materials not weigh as much in the physics?  
   // gather necessary molecules and compounds  
   // SiO2 60.3%
   G4Material* SiO2 = new G4Material("GE180_SiO2", 2.2*g/cm3, 2 );
   SiO2->AddElement(elSi, 1);
   SiO2->AddElement(elO, 2);
   fMaterialsMap["GE180_SiO2"] = SiO2;
   // BaO  18.2%
   G4Material* BaO = new G4Material("GE180_BaO", bigden, 2 );
   BaO->AddElement(elBa, 1);
   BaO->AddElement(elO, 1);
   fMaterialsMap["GE180_BaO"] = BaO;
   // Al2O3 14.3%
   G4Material* Al2O3 = new G4Material("GE180_Al2O3", bigden, 2 );
   Al2O3->AddElement(elAl, 2);
   Al2O3->AddElement(elO, 3);
   fMaterialsMap["GE180_Al2O3"] = Al2O3;
   // CaO   6.5%
   G4Material* CaO = new G4Material("GE180_CaO", bigden, 2 );
   CaO->AddElement(elCa, 1);
   CaO->AddElement(elO, 1);
   fMaterialsMap["GE180_CaO"] = CaO;
   // SrO   0.25%
   G4Material* SrO = new G4Material("GE180_SrO", bigden, 2 );
   SrO->AddElement(elSr, 1);
   SrO->AddElement(elO, 1);
   fMaterialsMap["GE180_SrO"] = SrO;

   // Density 2.76 g/cm^3
   // Index of Refraction 1.536
   G4Material* GE180 = new G4Material("GE180", 2.76*g/cm3, 5);
   GE180->AddMaterial(SiO2 , 0.6039);
   GE180->AddMaterial(BaO  , 0.1829);
   GE180->AddMaterial(Al2O3, 0.1439);
   GE180->AddMaterial(CaO  , 0.0659);
   GE180->AddMaterial(SrO  , 0.0034);
   fMaterialsMap["GE180"] = GE180;

   //---- polarized 3He ----
   G4double gasden = 10.77*atmosphere*(3.016*g/Avogadro)/(300*kelvin*k_Boltzmann);
   G4Material *pol3He = new G4Material("pol3He", gasden, 1 );
   pol3He->AddElement(el3He, 1);
   fMaterialsMap["He3"] = pol3He;  

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

   return 0;
}
