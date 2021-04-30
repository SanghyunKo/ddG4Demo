#ifndef DemoPrimaryGeneratorAction_h
#define DemoPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class DemoPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  DemoPrimaryGeneratorAction();
  virtual ~DemoPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

  const G4ParticleGun* GetParticleGun() const { return pParticleGun.get(); }

private:
  std::unique_ptr<G4ParticleGun> pParticleGun; // pointer a to G4 gun class
};

#endif
