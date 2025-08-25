##--------------------------------------------------------------------------##
## src/range/CMakeLists.txt
## Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
##--------------------------------------------------------------------------##

# Add headers
set(HEADERS
  Range.hh
  detail/RangeIterator.hh
  )

set(SOURCES
  )


# Add library
#set(_LIBRARY "IterToolsCore")
#add_library(IterToolsCore ${SOURCES})
#set_target_properties(${_LIBRARY}
#  PROPERTIES POSITOIN_INDEPENDENT_CODE ON
#  )

# Install the library
#install(TARGETS ${_LIBRARY} LIBRARY)

# Install the headers
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/range)

# Add tests if testing is enabled
#if (ITERTOOLS_ENABLE_TESTS)
#  add_subdirectory(tests)
#endif ()
