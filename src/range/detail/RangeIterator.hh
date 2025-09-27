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
namespace detail
{
//===========================================================================//
/*!
 * \class RangeIterator
 * \brief Enables iterating over a range of Integer values
 *
 * This iterator implements a "counting" iterator.  It stores an integral
 * count, and it counts by \p step increment from its initial \p value.
 *
 * It is the duty of the caller to ensure that a RangeIterator constructed
 * with an unsigned type does not attempt to cross zero.
 *
 * \example range/tests/tstRangeIterator.cc
 */
//===========================================================================//

template<typename Integer = int>
class RangeIterator
{
    using Integer_t = std::remove_reference_t<Integer>;
    static_assert(std::is_integral_v<Integer_t>);

  public:
    //! Public type aliases
    using This = RangeIterator<Integer>;
    using difference_type = std::ptrdiff_t;
    using value_type = Integer_t;
    using reference = std::add_lvalue_reference_t<Integer_t>;
    using const_reference = std::add_lvalue_reference_t<const Integer_t>;
    using pointer = std::add_pointer_t<Integer_t>;
    using const_pointer = std::add_pointer_t<const Integer_t>;
    using iterator_category = std::forward_iterator_tag;

  public:
    //! Default constructor
    RangeIterator();

    // Constructor with value and optional step
    inline RangeIterator(Integer value, Integer step = 1);

    // >>> INCREMENT
    // Pre-increment
    inline This& operator++();

    // Post-increment
    inline This operator++(int);

    // >>> DECREMENT
    // Pre-decrement
    inline This& operator--();

    // Post-decrement
    inline This operator--(int);

    // >>> DEREFERENCE, POINTER, INDEXING
    //@{
    //! Dereference
    reference operator*() { return m_value; }
    const_reference operator*() const { return m_value; }
    //@}

    //@{
    //! Pointer
    pointer operator->() { return &m_value; }
    const_pointer operator->() const { return &m_value; }
    //@}

    //! Indexing
    value_type operator[](difference_type n) const
    {
        return m_value + m_step * n;
    }

    // >>> COMPOUND ARITHMETIC
    // Compound arithmetic operators
    This& operator+=(difference_type n);
    This& operator-=(difference_type n);

    // >>> ACCESSORS
    //! Return the current value
    value_type value() const { return m_value; }

    //! Return the step length
    Integer step() const { return m_step; }

  private:
    // >>> DATA
    //! Stores the integral value of the iterator
    value_type m_value;

    //! Stores the distance to travel each iteration
    value_type m_step;
};

//---------------------------------------------------------------------------//
// ARITHMETIC OPERATORS
//---------------------------------------------------------------------------//
// Sum between a range iterator and an integral value
template<typename Integer1, typename Integer2>
RangeIterator<std::common_type_t<Integer1, Integer2>>
operator+(const RangeIterator<Integer1>& iter, Integer2 n);

// Sum between a range iterator and an integral value
template<typename Integer1, typename Integer2>
RangeIterator<std::common_type_t<Integer1, Integer2>>
operator+(Integer1 n, const RangeIterator<Integer2>& iter);

// Sum two range iterators
template<typename Integer1, typename Integer2>
RangeIterator<std::common_type_t<Integer1, Integer2>>
operator+(const RangeIterator<Integer1>& iter1,
          const RangeIterator<Integer2>& iter2);

// Difference between a range iterator and an integral value
template<typename Integer1, typename Integer2>
RangeIterator<std::common_type_t<Integer1, Integer2>>
operator-(const RangeIterator<Integer1>& iter, Integer2 n);

// Difference between two range iterators
template<typename Integer1, typename Integer2>
typename RangeIterator<Integer1>::difference_type
operator-(const RangeIterator<Integer1>& iter1,
          const RangeIterator<Integer2>& iter2);

//---------------------------------------------------------------------------//
// BOOLEAN OPERATORS
//---------------------------------------------------------------------------//
// Equality operator
template<typename Integer1, typename Integer2>
bool operator==(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2);

// Inequality operator
template<typename Integer1, typename Integer2>
bool operator!=(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2);

// Less-than operator
template<typename Integer1, typename Integer2>
bool operator<(const RangeIterator<Integer1>& iter1,
               const RangeIterator<Integer2>& iter2);

// Less-than or equal operator
template<typename Integer1, typename Integer2>
bool operator<=(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2);

// Greater-than operator
template<typename Integer1, typename Integer2>
bool operator>(const RangeIterator<Integer1>& iter1,
               const RangeIterator<Integer2>& iter2);

// Greater-than or equal operator
template<typename Integer1, typename Integer2>
bool operator>=(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2);

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
// Build a range iterator
template<typename Integer>
inline RangeIterator<Integer>
makeRangeIterator(Integer value, Integer step = 1);

//---------------------------------------------------------------------------//
}  // namespace detail
}  // namespace itertools

//---------------------------------------------------------------------------//
// INLINE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------//
#include "RangeIterator.i.hh"

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH
//---------------------------------------------------------------------------//
// end of src/range/detail/RangeIterator.hh
//---------------------------------------------------------------------------//
