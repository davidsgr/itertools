//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/Range.hh
 * \brief  Range class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_RANGE_RANGE_HH
#define ITERTOOLS_SRC_RANGE_RANGE_HH

#include <type_traits>

#include "range/detail/RangeIterator.hh"

namespace itertools
{
//===========================================================================//
/*!
 * \class Range
 * \brief Range class for iterating over a range of integers
 *
 * This class provides a counting range, and should be used this way
 * \code{.cpp}
 *   // Loop 6 times
 *   for (auto i : itertools::range(6))
 *   {
 *     // Do stuff
 *   }
 * \endcode
 * To loop over a specific range, do this:
 * \code{.cpp}
 *   // Loop from 2 to 7
 *   for (auto i : itertools::range(2, 7))
 *   {
 *     // Do stuff
 *   }
 * \endcode
 * You can also loop over a specific step length
 * \code{.cpp}
 *   // Loop from 8 to -2 counting down by 2
 *   for (auto i : itertools::range(8, -2, -2))
 *   {
 *     // Do stuff
 *   }
 * \endcode
 *
 * \tparam Integer  The type of the integer to use as a counter
 *
 * \example range/tests/tstRange.cc
 */
//===========================================================================//

template<typename IntegralType>
class Range
{
    using IntegralType_t = std::remove_reference_t<IntegralType>;
    static_assert(std::is_integral_v<IntegralType_t>);

  public:
    //@{
    //! Public type aliases
    using iterator = detail::RangeIterator<IntegralType>;
    using const_iterator = detail::RangeIterator<IntegralType>;
    //@}

  public:
    // Construct with an ending only (beginning is zero)
    inline Range(IntegralType end);

    // Construct with a beginning/ending and optional step length
    inline Range(IntegralType begin, IntegralType end, IntegralType step = 1);

    //! Return beginning iterator
    iterator begin() { return this->cbegin(); }

    //! Return const beginning iterator
    const_iterator begin() const { return this->cbegin(); }

    // Return const beginning iterator
    inline const_iterator cbegin() const;

    //! Return ending iterator
    iterator end() { return this->cend(); }

    //! Return const ending iterator
    const_iterator end() const { return this->cend(); }

    // Return const ending iterator
    const_iterator cend() const;

    //! Return size of range
    IntegralType_t size() const { return (m_end - m_begin) / m_step; }

    //! Access begin value
    IntegralType_t beginValue() const { return m_begin; }

    //! Access end value
    IntegralType_t endValue() const { return m_end; }

    //! Access step value
    IntegralType_t step() const { return m_step; }

  private:
    // >>> DATA
    IntegralType_t m_begin;
    IntegralType_t m_end;
    IntegralType_t m_step;
};

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
// Create a range spanning 0...end
template<typename IntegralType>
inline Range<IntegralType> range(IntegralType end);

// Create a range spanning begin...end with an optional step length
template<typename IntegralType>
inline Range<IntegralType>
range(IntegralType begin, IntegralType end, IntegralType step = 1);

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// INLINE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------//
#include "Range.i.hh"

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_RANGE_RANGE_HH
//---------------------------------------------------------------------------//
// end of src/range/Range.hh
//---------------------------------------------------------------------------//
