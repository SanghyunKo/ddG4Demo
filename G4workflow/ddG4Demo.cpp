#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "GeoSvc.h"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "FTFP_BERT.hh"
#include "G4UImanager.hh"

#include "DemoActionInitialization.h"

int main(int argc, char** argv) {
  // Construct the default run manager
  #ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  #else
  G4RunManager* runManager = new G4RunManager;
  #endif

  std::string filename(argv[1]);
  std::vector<std::string> compacts{filename};

  // Mandatory user initialization classes
  auto geoSvc = new GeoSvc(compacts); // deleted by G4RunManager

  runManager->SetUserInitialization(geoSvc->getGeant4Geo());

  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new DemoActionInitialization());

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/run/initialize");

  sleep(10);

  delete runManager;

  return 0;
}
