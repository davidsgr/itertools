##--------------------------------------------------------------------------##
## CMakeLists.txt
## Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
##--------------------------------------------------------------------------##

include_guard()

# Define list of packages
set(IT_PACKAGES
  core
  range
  )

# Loop over all subpackages and build them
foreach (package IN LISTS IT_PACKAGES)
  add_subdirectory(${package})
endforeach ()

##--------------------------------------------------------------------------##
## end of packages/CMakeLists.txt
##--------------------------------------------------------------------------##
