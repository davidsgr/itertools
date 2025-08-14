//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/detail/RangeIterator.hh
 * \brief  RangeIterator class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH
#define ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH

#include <iterator>
#include <type_traits>

namespace itertools
{
//===========================================================================//
/*!
 * \class RangeIterator
 * \brief Enables iterating over a range of Integer values
 *
 * Long description or discussion goes here.
 *
 * \example range/tests/tstRangeIterator.cc
 */
//===========================================================================//

template<typename Integer>
class RangeIterator
{
    using Integer_t = std::remove_reference_t<Integer>;
    static_assert(std::is_integral_v<Integer_t>);

  public:
    //! Public type aliases
    using This = RangeIterator<Iterator> using difference_type = std::ptrdiff_t;
    using value_type = Integer_t;
    using reference = std::add_reference<Integer_t>;
    using pointer = std::add_pointer<Integer_t>;
    using iterator_category = std::forward_iterator_tag;

  public:
    // Default constructor
    RangeIterator() = default;

    // Constructor with value and optional step
    RangeIterator(Integer value, Integer step = 1);

    //! Dereference
    reference operator*() const { return *m_value; }

    // Pre-increment
    inline This& operator++();

    // Post-increment
    inline This operator++(int);

    //! Return the step length
    Integer step() const { return m_step; }

  private:
    // >>> DATA
    Integer m_value;
    Integer m_step;
};

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
// Build a range iterator
template<typename Integer>
RangeIterator<Iterator> makeRangeIterator(Integer value, Integer step = 1);

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// INLINE DEFINITIONS
//---------------------------------------------------------------------------//
// #include "RangeIterator.i.hh"

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH
//---------------------------------------------------------------------------//
// end of src/range/detail/RangeIterator.hh
//---------------------------------------------------------------------------//
