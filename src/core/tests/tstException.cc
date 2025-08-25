//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/core/tests/tstException.cc
 * \brief  Tests for class Exception.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle,
 * LLC.
 */
//---------------------------------------------------------------------------//

#include "../Exception.hh"

#include <gtest/gtest.h>

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST(ExceptionTest, DBCException)
{
    itertools::DBCException e("test_string", "precondition", "filename", 99);

    EXPECT_EQ("filename", e.filename());
    EXPECT_EQ(99, e.lineNumber());
    EXPECT_EQ("test_string", e.testString());
    EXPECT_EQ("precondition", e.testType());

    EXPECT_EQ("test_string failed precondition DBC test in filename:99",
              e.what());
}

//---------------------------------------------------------------------------//

TEST(ExceptionTest, NotImplementedException)
{
    itertools::NotImplementedException e("message", "filename", 99);
    EXPECT_EQ("filename", e.filename());
    EXPECT_EQ(99, e.lineNumber());
    EXPECT_EQ("message", e.message());

    EXPECT_EQ("message not implemeted at filename:99", e.what());
}

//---------------------------------------------------------------------------//

TEST(ExceptionTest, NotReachableException)
{
    itertools::NotReachableException e("filename", 99);

    EXPECT_EQ("filename", e.filename());
    EXPECT_EQ(99, e.lineNumber());
    EXPECT_EQ("Logically unreachable code block reached at filename:99",
              e.what());
}

//---------------------------------------------------------------------------//
// end of src/core/tests/tstException.cc
//---------------------------------------------------------------------------//
