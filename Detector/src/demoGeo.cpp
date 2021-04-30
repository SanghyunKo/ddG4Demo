#include "DD4hep/DetFactoryHelper.h"
#include "DD4hep/OpticalSurfaces.h"
#include "DD4hep/Printout.h"
#include "DD4hep/Detector.h"
#include "DDSegmentation/WaferGridXY.h"

#include "demoConstructor.h"

namespace ddG4Demo {
  static dd4hep::Ref_t create_detector( dd4hep::Detector &description, xml_h xmlElement, dd4hep::SensitiveDetector sensDet ) {
    // Get the detector description from the xml-tree
    xml_det_t    x_det = xmlElement;
    std::string  name  = x_det.nameStr();
    // Create the detector element
    dd4hep::DetElement drDet( name, x_det.id() );
    // set the sensitive detector type to the DD4hep calorimeter
    dd4hep::xml::Dimension sensDetType = xmlElement.child(_Unicode(sensitive));
    sensDet.setType(sensDetType.typeStr());
    // Get the world volume
    dd4hep::Assembly experimentalHall("hall");

    auto constructor = demoConstructor(&description, x_det, &sensDet, &experimentalHall);
    constructor.construct();

    dd4hep::PlacedVolume hallPlace = description.pickMotherVolume(drDet).placeVolume(experimentalHall);
    hallPlace.addPhysVolID("system",x_det.id());
    // connect placed volume and physical volume
    drDet.setPlacement( hallPlace );

    return drDet;
  }
} // namespace detector
DECLARE_DETELEMENT(ddG4Demo, ddG4Demo::create_detector) // factory method
