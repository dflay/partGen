//===================================================
// PartGenElegantInterface
// Implementation for class 
//===================================================

#include "G4Event.hh"
#include "G4Types.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "PartGenElegantInterface.hh"

PartGenElegantInterface::PartGenElegantInterface(char * fname)
{
  inputFile.open(fname);
  if(inputFile){
    filename=fname;
  } 
  else{
    G4Exception("G4ElegantInterface::G4ElegantInterface","Event0201",FatalException,
	        "G4ElegantInterface:: cannot open file.");
  }
  G4ThreeVector zero;
  particle_position=zero;
  particle_time=0.0;
}
PartGenElegantInterface::PartGenElegantInterface(G4String fname)
{
  const char* fn = fname.data();
  inputFile.open((char*)fn);
  if (inputFile) {
   filename = fname;
  }
  else {
   G4Exception("G4ElegantInterface::G4ElegantInterface","Event0201",FatalException,
	       "G4ElegantInterface:: cannot open file.");
  }
  G4ThreeVector zero;
  particle_position=zero;
  particle_time=0.0;
}
PartGenElegantInterface::~PartGenElegantInterface() {;}

void PartGenElegantInterface::GeneratePrimaryVertex(G4Event *evt)
{
  G4int NHEP;
  inputFile >>NHEP;
  if( inputFile.eof() ) 
    {
      G4Exception("G4HEPEvtInterface::GeneratePrimaryVertex","Event0202",
		  JustWarning,"End-Of-File : HEPEvt input file");
      return;
    }
 
  for( G4int IHEP=0; IHEP<NHEP; IHEP++ )
    {
      G4int ISTHEP;   // status code
      G4int IDHEP;    // PDG code
      G4int JDAHEP1;  // first daughter
      G4int JDAHEP2;  // last daughter
      G4double PHEP1; // px in GeV
      G4double PHEP2; // py in GeV
      G4double PHEP3; // pz in GeV
      G4double PHEP5; // mass in GeV
      G4double VHEP1; // x position
      G4double VHEP2; // y position
      G4double VHEP3; // z position
     
      //note that for ELEGANT, we will always have  first and last daughter at zero
      //the position will represent the location within the bunch.
      //
      inputFile >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
		>> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5
		>> VHEP1>> VHEP2 >> VHEP3;

      // create G4PrimaryParticle object
      G4PrimaryParticle* particle 
        = new G4PrimaryParticle( IDHEP );
      particle->SetMass( PHEP5*GeV );
      particle->SetMomentum(PHEP1*GeV, PHEP2*GeV, PHEP3*GeV );
      particle_position=G4ThreeVector(VHEP1*mm,VHEP2*mm,VHEP3*mm);

      // create G4PrimaryVertex object
      G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position,particle_time);
      vertex->SetPrimary(particle);
      evt->AddPrimaryVertex(vertex);
    }
}
