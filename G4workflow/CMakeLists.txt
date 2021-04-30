project(G4workflow)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB sources
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)

file(GLOB headers
  ${PROJECT_SOURCE_DIR}/include/*.h
)

add_executable(ddG4Demo ddG4Demo.cpp ${sources} ${headers})

target_include_directories(ddG4Demo PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${DD4hep_DIR}/include
)

target_link_libraries(
  ddG4Demo
  DD4hep::DDCore
  DD4hep::DDG4
  Detector
)

set_target_properties(ddG4Demo PROPERTIES PUBLIC_HEADER "${headers}")

install(TARGETS ddG4Demo
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include
)
