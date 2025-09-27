//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/detail/tests/tstRangeIterator.cc
 * \brief  Tests for class RangeIterator.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle,
 * LLC.
 */
//---------------------------------------------------------------------------//

#include "../RangeIterator.hh"

#include <gtest/gtest.h>

using itertools::detail::RangeIterator;

//---------------------------------------------------------------------------//
// TESTS
//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, construction)
{
    // Test default construction
    RangeIterator<int> iter1;
    EXPECT_EQ(0, iter1.value());
    EXPECT_EQ(1, iter1.step());

    // Test regular constructor
    RangeIterator<unsigned int> iter2(3, 2);
    EXPECT_EQ(3, iter2.value());
    EXPECT_EQ(2, iter2.step());
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, increment)
{
    // Test pre-increment
    RangeIterator<int> iter1(3, 1);
    auto result1 = ++iter1;
    EXPECT_EQ(4, result1.value());
    EXPECT_EQ(4, iter1.value());

    RangeIterator<int> iter2(4, 2);
    auto result2 = ++iter2;
    EXPECT_EQ(6, result2.value());
    EXPECT_EQ(6, iter2.value());

    // Test post-increment
    RangeIterator<int> iter3(3, 1);
    auto result3 = iter3++;
    EXPECT_EQ(3, result3.value());
    EXPECT_EQ(4, iter3.value());

    RangeIterator<int> iter4(4, 2);
    auto result4 = iter4++;
    EXPECT_EQ(4, result4.value());
    EXPECT_EQ(6, iter4.value());
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, decrement)
{
    // Test pre-decrement
    RangeIterator<int> iter1(3, 1);
    auto result1 = --iter1;
    EXPECT_EQ(2, result1.value());
    EXPECT_EQ(2, iter1.value());

    RangeIterator<int> iter2(4, 2);
    auto result2 = --iter2;
    EXPECT_EQ(2, result2.value());
    EXPECT_EQ(2, iter2.value());

    // Test post-decrement
    RangeIterator<int> iter3(3, 1);
    auto result3 = iter3--;
    EXPECT_EQ(3, result3.value());
    EXPECT_EQ(2, iter3.value());

    RangeIterator<int> iter4(4, 2);
    auto result4 = iter4--;
    EXPECT_EQ(4, result4.value());
    EXPECT_EQ(2, iter4.value());
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, dereference)
{
    // Test dereference
    RangeIterator<unsigned int> iter1(6, 2);
    EXPECT_EQ(6, *iter1);

    const RangeIterator<unsigned int> iter2 = iter1;
    EXPECT_EQ(6, *iter2);

    // Test indexing
    EXPECT_EQ(10, iter1[2]);
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, compound_arithmetic)
{
    // Test compound-addition
    RangeIterator<unsigned int> iter1(6, 2);
    iter1 += 6;
    EXPECT_EQ(6 + 2 * 6, iter1.value());

    // Test compound-subtraction
    RangeIterator<unsigned int> iter2(6, 2);
    iter2 -= 2;
    EXPECT_EQ(6 - 2 * 2, iter2.value());
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, addition)
{
    // Sum with integer on right
    RangeIterator<unsigned int> iter1(6, 2);
    auto result1 = iter1 + 2;
    EXPECT_EQ(6 + 2 * 2, result1.value());
    EXPECT_EQ(2, result1.step());

    // Sum with integer on left
    auto result2 = 2 + result1;
    EXPECT_EQ(6 + 4 * 2, result2.value());
    EXPECT_EQ(2, result2.step());

    // Sum two range iterators
    auto result3 = result1 + result2;
    EXPECT_EQ(result1.value() + result2.value(), result3.value());
    EXPECT_EQ(2, result3.step());
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, subtraction)
{
    // Test difference with an integer
    RangeIterator<int> iter1(6, 2);
    auto result1 = iter1 - 2;
    EXPECT_EQ(6 - 2 * 2, result1.value());
    EXPECT_EQ(2, result1.step());

    // Test difference between two range iterators
    EXPECT_EQ(2, iter1 - result1);
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, equality)
{
    RangeIterator<int> iter1(6, 2);
    RangeIterator<unsigned int> iter2(6, 2);
    RangeIterator<unsigned int> iter3(4, 2);

    EXPECT_TRUE(iter1 == iter1);
    EXPECT_TRUE(iter1 == iter2);
    EXPECT_FALSE(iter1 == iter3);

    EXPECT_TRUE(iter1 != iter3);
    EXPECT_FALSE(iter1 != iter1);
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, comparison)
{
    RangeIterator<int> iter1(6, 2);
    RangeIterator<unsigned int> iter2(8, 2);
    RangeIterator<int> iter3(4, 2);

    EXPECT_TRUE(iter1 < iter2);
    EXPECT_TRUE(iter1 <= iter1);
    EXPECT_TRUE(iter2 > iter3);
    EXPECT_TRUE(iter2 >= iter3);
    EXPECT_TRUE(iter3 >= iter3);
    EXPECT_FALSE(iter1 > iter2);
    EXPECT_FALSE(iter2 < iter3);
}

//---------------------------------------------------------------------------//

TEST(RangeIteratorTest, make_range_iterator)
{
    auto iter = itertools::detail::makeRangeIterator(4, 2);
    EXPECT_EQ(4, iter.value());
    EXPECT_EQ(2, iter.step());
}

//---------------------------------------------------------------------------//
// end of src/range/detail/tests/tstRangeIterator.cc
//---------------------------------------------------------------------------//
