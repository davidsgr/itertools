//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/tests/tstRange.cc
 * \brief  Tests for class Range.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle,
 * LLC.
 */
//---------------------------------------------------------------------------//

#include "../Range.hh"

#include <gtest/gtest.h>

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST(RangeTest, tests)
{
    // Loop from 0 to 6
    auto j = 0;
    for (auto i : itertools::range(6))
    {
        j += i;
    }
    EXPECT_EQ(0 + 1 + 2 + 3 + 4 + 5, j);

    // Loop from 2 to 7
    j = 0;
    for (auto i : itertools::range(2, 7))
    {
        j += i;
    }
    EXPECT_EQ(2 + 3 + 4 + 5 + 6, j);

    // Loop from 8 to -2 by 2
    j = 0;
    for (auto i : itertools::range(8, -2, -2))
    {
        j += i;
    }
    EXPECT_EQ(8 + 6 + 4 + 2 + 0, j);
}

//---------------------------------------------------------------------------//
// end of src/range/tests/tstRange.cc
//---------------------------------------------------------------------------//
