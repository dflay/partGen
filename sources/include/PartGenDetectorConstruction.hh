#ifndef PartGenDetectorConstruction_h
#define PartGenDetectorConstruction_h 1

#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <map>  

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "PartParameters.hh"
#include "PartGenEnumerate.hh"
#include "PartGenSD.hh"
#include "PartGenDetMessenger.hh"

#include "G4Transform3D.hh"
#include "G4PhysicalConstants.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4AssemblyVolume.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnionSolid.hh"
#include "G4SDManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4String.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class PartGenDetMessenger; 

/// Detector construction class to define materials and geometry.

class PartGenDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    PartGenDetectorConstruction();
    virtual ~PartGenDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    void SetTgtMaterial(G4String name) { fTgtMaterialName = name; } 
    void SetTgtXSize(G4double x) { fTgtXSize = x; } 
    void SetTgtYSize(G4double y) { fTgtYSize = y; } 
    void SetTgtZSize(G4double z) { fTgtZSize = z; }
 
    void SetDetMaterial(G4String name) { fDetMaterialName = name; } 
    void SetDetXSize(G4double x) { fDetXSize = x; } 
    void SetDetYSize(G4double y) { fDetYSize = y; } 
    void SetDetZSize(G4double z) { fDetZSize = z; } 
 
    void SetDetX(G4double x)     { fDetX     = x; } 
    void SetDetY(G4double y)     { fDetY     = y; } 
    void SetDetZ(G4double z)     { fDetZ     = z; } 


  protected:
    G4LogicalVolume*  fScoringVolume;

  private:
   // data members 
   PartGenDetMessenger *fMessenger; 

   bool fDebug,fCheckOverlaps;

   // lists
   std::map<G4String,G4Material *> fMaterialsMap;
 
   G4double fTgtXSize,fTgtYSize,fTgtZSize;
   G4double fDetXSize,fDetYSize,fDetZSize;
   G4double fDetX,fDetY,fDetZ;

   G4String fTgtMaterialName;
   G4String fDetMaterialName;
 
   // methods 
   G4Material *GetMaterial(G4String name);

   void BuildBeamRef(G4LogicalVolume *logicMother);  // reference incoming beam path (for debugging only) 
   void BuildTarget(G4LogicalVolume *logicMother);    
   void BuildDetector(G4LogicalVolume *logicMother);    

   int ConstructMaterials();

   G4VPhysicalVolume *ConstructGeometries();  

};

#endif

