#include "DemoActionInitialization.h"
#include "DemoPrimaryGeneratorAction.h"
#include "DemoRunAction.h"

DemoActionInitialization::DemoActionInitialization()
: G4VUserActionInitialization() {}

DemoActionInitialization::~DemoActionInitialization() {}

void DemoActionInitialization::BuildForMaster() const {
  DemoRunAction* runAction = new DemoRunAction;
  SetUserAction(runAction);
}

void DemoActionInitialization::Build() const {
  SetUserAction(new DemoPrimaryGeneratorAction);

  DemoRunAction* runAction = new DemoRunAction;
  SetUserAction(runAction);
}
