#ifndef demoConstructor_h
#define demoConstructor_h 1

#include "DD4hep/DetFactoryHelper.h"
#include "DD4hep/OpticalSurfaces.h"
#include "DD4hep/Printout.h"
#include "DD4hep/Detector.h"

#include "DDSegmentation/CartesianGridXY.h"

namespace ddG4Demo {
  class demoConstructor {
  public:
    demoConstructor(dd4hep::Detector* description, xml_det_t& x_det, dd4hep::SensitiveDetector* sensDet, dd4hep::Assembly* expHall);
    virtual ~demoConstructor() {};

    void construct();

  private:
    void level1();
    void level2(dd4hep::Volume& moduleLogical);

    dd4hep::Detector* pDescription;
    xml_det_t mX_det;
    xml_comp_t mX_module;
    xml_comp_t mX_wafer;
    xml_comp_t mX_endmodule;
    dd4hep::SensitiveDetector* pSensDet;
    dd4hep::DDSegmentation::CartesianGridXY* pSegmentation;
    dd4hep::Assembly* pExpHall;
  };
}

#endif
