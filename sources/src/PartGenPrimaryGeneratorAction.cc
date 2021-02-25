//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file PartGenPrimaryGeneratorAction.cc
/// \brief Implementation of the PartGenPrimaryGeneratorAction class

#include "PartGenPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PartGenPrimaryGeneratorAction::PartGenPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fParticleKinEnergy(1.*GeV),
  fParticleMomentum(0),
  fParticleMass(0), 
  fMessenger(0) 
  // fEnvelopeBox(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  fMessenger = new PartGenBeamMessenger(this);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fParticleMass = particle->GetPDGMass();

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(fParticleKinEnergy); // NB: Kinetic energy!
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PartGenPrimaryGeneratorAction::~PartGenPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PartGenPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.
  
  // G4double envSizeXY = 0;
  // G4double envSizeZ = 0;

  // if (!fEnvelopeBox)
  // {
  //   G4LogicalVolume* envLV
  //     = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
  //   if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  // }

  // if ( fEnvelopeBox ) {
  //   envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
  //   envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  // }  
  // else  {
  //   G4ExceptionDescription msg;
  //   msg << "Envelope volume of box shape not found.\n"; 
  //   msg << "Perhaps you have changed geometry.\n";
  //   msg << "The gun will be place at the center.";
  //   G4Exception("PartGenPrimaryGeneratorAction::GeneratePrimaries()",
  //    "MyCode0002",JustWarning,msg);
  // }

  // G4double size = 0.8; 
  // G4double x0 = size * envSizeXY * (G4UniformRand()-0.5);
  // G4double y0 = size * envSizeXY * (G4UniformRand()-0.5);
  // G4double z0 = -0.5 * envSizeZ;

  G4double worldZHalfLength = 0.;
  auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

  // Check that the world volume has box shape
  G4Box* worldBox = nullptr;
  if (  worldLV ) {
    worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  }

  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box shape not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("BDPrimaryGeneratorAction::GeneratePrimaries()",
      "MyCode0002", JustWarning, msg);
  }

  G4double x0 = 0; 
  G4double y0 = 0; 
  G4double z0 = -worldZHalfLength; 

  // compute particle kinetic energy 
  // Note: T^2 + 2mT = p^2 => T = sqrt(p^2 + m^2) - m (other root is negative)  
  fParticleKinEnergy = sqrt( pow(fParticleMomentum,2.) + pow(fParticleMass,2.) ) - fParticleMass;

  char msg[200];
  sprintf(msg,"**** Particle details: p = %.7lf GeV, T = %.7lf GeV",fParticleMomentum/GeV,fParticleKinEnergy/GeV);
  std::cout << msg << std::endl;

  // N.B: set *kinetic* energy 
  fParticleGun->SetParticleEnergy(fParticleKinEnergy); 
  // set position
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  // generate vertex 
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

