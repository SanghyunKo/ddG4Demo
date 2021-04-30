#include "demoConstructor.h"

ddG4Demo::demoConstructor::demoConstructor(dd4hep::Detector* description, xml_det_t& x_det, dd4hep::SensitiveDetector* sensDet, dd4hep::Assembly* expHall)
: pDescription(description),
  mX_det(x_det),
  mX_module(x_det.child(_Unicode(module))),
  mX_wafer(x_det.child(_Unicode(wafer))),
  mX_endmodule(mX_module.child(_Unicode(end_module))),
  pSensDet(sensDet),
  pExpHall(expHall) {
  pSegmentation = dynamic_cast<dd4hep::DDSegmentation::CartesianGridXY*>( sensDet->readout().segmentation().segmentation() );
}

void ddG4Demo::demoConstructor::construct() { level1(); }

void ddG4Demo::demoConstructor::level1() {
  double moduleSize = mX_module.moduleWidth();
  double moduleHeight = mX_module.moduleHeight();
  double readoutHeight = mX_wafer.thickness();

  dd4hep::Box envelopSolid(moduleSize/2., moduleSize/2., (moduleHeight+readoutHeight)/2.);

  dd4hep::Box moduleSolid(moduleSize/2., moduleSize/2., moduleHeight/2.);
  dd4hep::Volume moduleLogical("module", moduleSolid, pDescription->material(mX_module.materialStr()));
  moduleLogical.setVisAttributes(*pDescription, mX_module.visStr());

  dd4hep::Box readoutSolid(moduleSize/2., moduleSize/2., readoutHeight/2.);
  dd4hep::Volume readoutLogical("readout", readoutSolid, pDescription->material(mX_wafer.materialStr()));
  readoutLogical.setVisAttributes(*pDescription, mX_wafer.visStr());

  level2(moduleLogical);

  if (mX_wafer.isSensitive()) {
    readoutLogical.setSensitiveDetector(*pSensDet);
  }

  int nModule = mX_module.nmodules();

  for (int i_x = 0; i_x < nModule; i_x++) {
    for (int i_y = 0; i_y < nModule; i_y++) {
      dd4hep::Volume envelopLogical("envelop", envelopSolid, pDescription->material("Air"));
      pExpHall->placeVolume(envelopLogical, dd4hep::Position(moduleSize*static_cast<double>(i_x), moduleSize*static_cast<double>(i_y), 0.));

      envelopLogical.placeVolume(moduleLogical, dd4hep::Position(0., 0., -readoutHeight/2.));

      dd4hep::PlacedVolume readoutPhysics = envelopLogical.placeVolume(readoutLogical, dd4hep::Position(0., 0., moduleHeight/2.));
      readoutPhysics.addPhysVolID("x0",i_x);
      readoutPhysics.addPhysVolID("y0",i_y);
    }
  }
}

void ddG4Demo::demoConstructor::level2(dd4hep::Volume& moduleLogical) {
  double gridSize = pSegmentation->gridSizeX(); // assume same grid size for x and y
  double moduleSize = mX_module.moduleWidth();
  double moduleHeight = mX_module.moduleHeight();
  double endModuleSize = mX_endmodule.moduleWidth();

  int numx = static_cast<int>( std::floor( ( moduleSize - endModuleSize )/gridSize ) ) + 1; // number of sub-module along x direction in a single module

  if ( numx%2==0 ) {
    pSegmentation->setOffsetX(gridSize/2.);
    pSegmentation->setOffsetY(gridSize/2.);
  }

  for (int i_x = 0; i_x < numx; i_x++) {
    for (int i_y = 0; i_y < numx; i_y++) {
      int binX = -(numx/2) + i_x;
      int binY = -(numx/2) + i_y;
      double ptX = gridSize*binX + ( numx%2==0 ? gridSize/2. : 0. );
      double ptY = gridSize*binY + ( numx%2==0 ? gridSize/2. : 0. );

      // assume extreme geometry conditions - where shape or materials can be parameterized
      dd4hep::Box endModuleSolid(endModuleSize/2., endModuleSize/2., moduleHeight/2.);
      dd4hep::Volume endModuleLogical("endmodule", endModuleSolid, pDescription->material(mX_endmodule.materialStr()));
      endModuleLogical.setVisAttributes(*pDescription, mX_endmodule.visStr());
      endModuleLogical.setRegion(*pDescription, mX_det.regionStr());

      moduleLogical.placeVolume(endModuleLogical, dd4hep::Position(ptX, ptY, 0.));
    }
  }

}
