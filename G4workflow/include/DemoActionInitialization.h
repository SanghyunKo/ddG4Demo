#ifndef DemoActionInitialization_h
#define DemoActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class DemoActionInitialization : public G4VUserActionInitialization
{
  public:
    DemoActionInitialization();
    virtual ~DemoActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
