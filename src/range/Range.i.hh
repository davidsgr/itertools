//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/Range.i.hh
 * \brief  Range inline method definitions.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_RANGE_RANGE_I_HH
#define ITERTOOLS_SRC_RANGE_RANGE_I_HH

namespace itertools
{

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
    using SignedIntegralType_t = std::make_signed_t<IntegralType_t>;
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
    return itertools::detail::makeRangeIterator(m_begin, m_step);
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
    return itertools::detail::makeRangeIterator(m_end, m_step);
}

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Create a range spanning 0...end with a step size of 1
 *
 * \tparam IntegralType  The integral type of the range
 *
 * \param[in] end  The ending value of the range
 *
 * \return An iterable range spanning 0 ... \p end with step size 1
 */
template<typename IntegralType>
Range<IntegralType> range(IntegralType end)
{
    return Range<IntegralType>(end);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Create a range spanning begin...end with an optional step size
 *
 * \tparam IntegralType  The integral type of the range
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

#endif  // ITERTOOLS_SRC_RANGE_RANGE_I_HH

//---------------------------------------------------------------------------//
// end of src/range/Range.i.hh
//---------------------------------------------------------------------------//
