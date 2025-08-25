##--------------------------------------------------------------------------##
## src/core/CMakeLists.txt
## Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
##--------------------------------------------------------------------------##

# Add headers
set(HEADERS
  DBC.hh
  Exception.hh
  Macros.hh
  )

set(SOURCES
  DBC.cc
  Exception.cc
  )


# Add library
set(_LIBRARY "IterToolsCore")
add_library(IterToolsCore ${SOURCES})
set_target_properties(${_LIBRARY}
  PROPERTIES POSITION_INDEPENDENT_CODE ON
  )

# Install the library
install(TARGETS ${_LIBRARY} LIBRARY)

# Install the headers
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core)

# Add tests if testing is enabled
if (ITERTOOLS_ENABLE_TESTS)
  add_subdirectory(tests)
endif ()
