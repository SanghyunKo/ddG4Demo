#include "DemoRunAction.h"

#include "G4RunManager.hh"
#include "G4Run.hh"

DemoRunAction::DemoRunAction()
: G4UserRunAction() {}

DemoRunAction::~DemoRunAction() {}

void DemoRunAction::BeginOfRunAction(const G4Run* run) {}

void DemoRunAction::EndOfRunAction(const G4Run* run) {}
