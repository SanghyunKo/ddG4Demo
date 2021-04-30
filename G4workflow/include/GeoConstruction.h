#ifndef GEOCONSTRUCTION_H
#define GEOCONSTRUCTION_H 1

// DD4hep
#include "DDG4/Geant4GeometryInfo.h"

// Geant4
#include "G4VUserDetectorConstruction.hh"

namespace dd4hep {
class Detector;
}

namespace det {
class GeoConstruction : public G4VUserDetectorConstruction {
public:
  /// Constructor
  GeoConstruction(dd4hep::Detector& lcdd);
  /// Default destructor
  virtual ~GeoConstruction();
  /// Geometry construction callback: Invoke the conversion to Geant4
  /// All volumes (including world) are deleted in ~G4PhysicalVolumeStore()
  virtual G4VPhysicalVolume* Construct() final;
  /// Construct SD
  virtual void ConstructSDandField() final;

private:
  /// Reference to geometry object
  dd4hep::Detector& m_lcdd;
};
}
#endif
