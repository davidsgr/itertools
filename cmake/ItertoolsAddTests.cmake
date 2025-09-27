##--------------------------------------------------------------------------##
## cmake/ItertoolsAddTests.txt
## Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
##--------------------------------------------------------------------------##

include_guard()

function(itertools_add_tests TEST_FILENAMES)

    # Create tests
    foreach (_TEST ${UNIT_TESTS})
    add_executable(${_TEST} ${_TEST}.cc)
    target_include_directories(
        ${_TEST}
        PRIVATE IterToolsCore
        )
    target_link_libraries(
        ${_TEST}
        PRIVATE IterToolsCore GTest::gtest GTest::gtest_main
        )

    include(GoogleTest)
    gtest_discover_tests(
        ${_TEST} 
        XML_OUTPUT_DIR "${PROJECT_BINARY_DIR}/Testing/Temporary"
        PROPERTIES DISCOVERY_TIMEOUT 1200
        )
    endforeach ()
endfunction()

##--------------------------------------------------------------------------##
## end of cmake/ItertoolsAddTests.txt
##--------------------------------------------------------------------------##
