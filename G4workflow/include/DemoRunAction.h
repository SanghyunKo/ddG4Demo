#ifndef DemoRunAction_h
#define DemoRunAction_h 1

#include "G4UserRunAction.hh"

class G4Run;

class DemoRunAction : public G4UserRunAction {
public:
  DemoRunAction();
  virtual ~DemoRunAction();

  // virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
};

#endif
