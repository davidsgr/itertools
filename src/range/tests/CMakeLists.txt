##--------------------------------------------------------------------------##
## src/core/tests/CMakeLists.txt
## Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
##--------------------------------------------------------------------------##

include_guard()

# Define tests
set(UNIT_TESTS
  tstRange
  )

include(ItertoolsAddTests)
itertools_add_tests(UNIT_TESTS)

##--------------------------------------------------------------------------##
## end of src/core/tests/CMakeLists.txt
##--------------------------------------------------------------------------##

