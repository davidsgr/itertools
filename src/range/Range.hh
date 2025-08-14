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

namespace itertools
{
//===========================================================================//
/*!
 * \class Range
 * \brief <++>
 *
 * Long description or discussion goes here.
 *
 * \tparam Integer  The type of the
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
range(IntegralType begin, IntegralType end, IntegralType step);

//===========================================================================//
// INLINE IMPLEMENTATIONS
//===========================================================================//

//---------------------------------------------------------------------------//
// CONSTRUCTORS
//---------------------------------------------------------------------------//
/*!
 * \brief Construct an iterable range with a specific ending
 *
 * With this constructor, the beginning of the range is implicitly zero
 *
 * \param[in] end  The ending value of the range
 */
template<typename IntegralType>
Range<IntegralType>::Range(IntegralType end) : Range(0, end)
{
    /* * */
}

//---------------------------------------------------------------------------//
/*!
 * \brief Construct an iterable range with a specific beginning and ending and
 *        optional step length
 *
 * \param[in] begin  The beginning value of the range
 * \param[in] end    The ending value of the range
 * \param[in] step   The size of the step for each iteration
 */
template<typename IntegralType>
Range<IntegralType>::Range(IntegralType begin,
                           IntegralType end,
                           IntegralType step)
    : m_begin(begin), m_end(end), m_step(step)
{
    using SignedIntegralType_t = std::add_signed_t<IntegralType_T>;
    IT_REQUIRE(std::signbit(SignedIntegralType_t(m_end)
                            - SignedIntegralType_t(m_begin))
               == std::signbit(m_step));
}

//---------------------------------------------------------------------------//
// PUBLIC FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Return a const iterator to the beginning of the range
 *
 * \return A const iterator pointing to the beginning of the range
 */
template<typename IntegralType>
auto Range<IntegralType>::cbegin() const -> const_iterator
{
    return detail::makeRangeIterator(m_begin, m_step);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Return a const iterator to the ending of the range
 *
 * \return A const iterator pointing to the ending of the range
 */
template<typename IntegralType>
auto Range<IntegralType>::cend() const -> const_iterator
{
    return detail::makeRangeIterator(m_end, m_step);
}

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Create a range spanning 0...end with a step size of 1
 *
 * \param[in] end  The ending value of the range
 *
 * \return An iterable range spanning 0 ... \p end with step size 1
 */
template<typename IntegralType>
Range<IntegralType>::range(IntegralType end)
{
    return Range<IntegralType>(end);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Create a range spanning begin...end with an optional step size
 *
 * \param[in] begin  The beginning value of the range
 * \param[in] end    The ending value of the range
 * \param[in] step   The size of the step for each iteration
 *
 * \return An iterable range spanning \p begin ... \p end with step size
 *         \p step
 */
template<typename IntegralType>
Range<IntegralType>
range(IntegralType begin, IntegralType end, IntegralType step)
{
    return Range<IntegralType>(begin, end, step);
}

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_RANGE_RANGE_HH
//---------------------------------------------------------------------------//
// end of src/range/Range.hh
//---------------------------------------------------------------------------//
