project(Detector)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB headers
  ${PROJECT_SOURCE_DIR}/include/*.h
)

dd4hep_add_plugin(Detector SOURCES src/*.cpp USES
  DD4hep::DDCore
  DD4hep::DDCond
  ROOT::Core
  ROOT::Geom
  ROOT::GenVector
  ROOT::MathCore
)

set_target_properties(Detector PROPERTIES PUBLIC_HEADER "${headers}")

install(TARGETS Detector
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY compact DESTINATION bin)

dd4hep_configure_scripts( Detector DEFAULT_SETUP WITH_TESTS )
