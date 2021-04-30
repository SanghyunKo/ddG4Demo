#include "DemoPrimaryGeneratorAction.h"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

DemoPrimaryGeneratorAction::DemoPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  pParticleGun(nullptr) {
  pParticleGun = std::make_unique<G4ParticleGun>(1);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* electron = particleTable->FindParticle("e-");
  G4ParticleDefinition* pion = particleTable->FindParticle("pi-");
  pParticleGun->SetParticleDefinition(electron);
  pParticleGun->SetParticleDefinition(pion);
  pParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  pParticleGun->SetParticleEnergy(1.*CLHEP::GeV);
}

DemoPrimaryGeneratorAction::~DemoPrimaryGeneratorAction() {}

void DemoPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  pParticleGun->GeneratePrimaryVertex(anEvent);
}
