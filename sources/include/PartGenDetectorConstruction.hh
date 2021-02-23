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

/// Detector construction class to define materials and geometry.

class PartGenDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    PartGenDetectorConstruction();
    virtual ~PartGenDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;

  private:
   // data members 
   bool fDebug,fCheckOverlaps;

   // lists
   std::map<G4String,G4Material *> fMaterialsMap;  

   // methods 
   G4Material *GetMaterial(G4String name);

   void BuildBeamRef(G4LogicalVolume *logicMother);  // reference incoming beam path (for debugging only) 
   void BuildTarget(G4LogicalVolume *logicMother);    
   void BuildDetector(G4LogicalVolume *logicMother);    

   int ConstructMaterials(); 

};

#endif

