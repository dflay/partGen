// ELEGANT Interface
// This is derived from G4VPrimaryGenerator
// it allows for reading an ascii file formatted using the 
// HEPEVT data convention to load in a particle bunch.
// Each particle in the bunch will be attached to a vertex.

#ifndef PART_GEN_ELEGANT_HH_
#define PART_GEN_ELEGANT_HH_ 1

#include <fstream>

#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4Event.hh"

class G4Event;
class G4PrimaryVertex;

class PartGenElegantInterface: public G4VPrimaryGenerator
{
public:
  PartGenElegantInterface(char *fname);
  PartGenElegantInterface(G4String fname);
  ~PartGenElegantInterface();

  //virtual redefined from base class
  void GeneratePrimaryVertex(G4Event* evt);
private:
  G4String filename;
  std::ifstream inputFile;
  
};
#endif
