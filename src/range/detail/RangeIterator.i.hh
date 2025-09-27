//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/detail/RangeIterator.i.hh
 * \brief  RangeIterator inline method definitions.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_I_HH
#define ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_I_HH

#include <cmath>
#include <limits>

#include "core/DBC.hh"

namespace
{
//---------------------------------------------------------------------------//
// ANONYMOUS HELPER FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Implements the sign function
 *
 * This function returns -1 for negative numbers and +1 for positive numbers.
 * This is taken from
 * https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
 */
template<typename T>
inline constexpr int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

//---------------------------------------------------------------------------//
}  // anonymous namespace

namespace itertools
{
namespace detail
{

//---------------------------------------------------------------------------//
// CONSTRUCTORS
//---------------------------------------------------------------------------//
/*!
 * \brief Default constructor.
 *
 * Default values value and step are zero and one, respectively
 */
template<typename Integer>
RangeIterator<Integer>::RangeIterator()
    : RangeIterator<Integer>(Integer(0), Integer(1))
{
    /* * */
}

//---------------------------------------------------------------------------//
/*!
 * \brief Construct the range iterator with the given value and optional step
 *        length
 *
 * \param[in] value  The value to initialize the range iterator with
 * \param[in] step   The amount to change the value with each increment or
 *                   decrement
 */
template<typename Integer>
RangeIterator<Integer>::RangeIterator(Integer value, Integer step)
    : m_value(value), m_step(step)
{
    IT_REQUIRE(std::isfinite(value));
    IT_REQUIRE(std::isfinite(step));
    IT_REQUIRE(m_step != 0);
}

//---------------------------------------------------------------------------//
// INCREMENT
//---------------------------------------------------------------------------//
/*!
 * \brief Pre-increment the iterator
 *
 * \return A reference to this iterator after the increment
 */
template<typename Integer>
auto RangeIterator<Integer>::operator++() -> This&
{
    IT_REQUIRE(m_value <= std::numeric_limits<Integer>::max()
                              - sign(m_step) * (m_step + 1));

    m_value += m_step;
    return *this;
}

//---------------------------------------------------------------------------//
/*!
 * \brief Post-increment the iterator
 *
 * \return A copy of this iterator prior to the increment
 */
template<typename Integer>
auto RangeIterator<Integer>::operator++(int) -> This
{
    IT_REQUIRE(m_value <= std::numeric_limits<Integer>::max()
                              - sign(m_step) * (m_step + 1));

    This copy = *this;
    ++(*this);
    return copy;
}

//---------------------------------------------------------------------------//
// DECREMENT
//---------------------------------------------------------------------------//
/*!
 * \brief Pre-decrement the iterator
 *
 * \return A reference to this iterator after the decrement
 */
template<typename Integer>
auto RangeIterator<Integer>::operator--() -> This&
{
    IT_REQUIRE(m_value >= std::numeric_limits<Integer>::lowest()
                              + sign(m_step) * m_step);

    m_value -= m_step;
    return *this;
}

//---------------------------------------------------------------------------//
/*!
 * \brief Post-decrement the iterator
 *
 * \return A copy of this iterator prior to the decrement
 */
template<typename Integer>
auto RangeIterator<Integer>::operator--(int) -> This
{
    IT_REQUIRE(m_value >= std::numeric_limits<Integer>::lowest()
                              + sign(m_step) * m_step);

    This copy = *this;
    --(*this);
    return copy;
}

//---------------------------------------------------------------------------//
// COMPOUND ARITHMETIC
//---------------------------------------------------------------------------//
/*!
 * \brief Compound addition-assignment operator
 *
 * \param[in] n  The amount to add to the iterator
 *
 * \return A reference to this iterator
 */
template<typename Integer>
auto RangeIterator<Integer>::operator+=(difference_type n) -> This&
{
    IT_REQUIRE(std::isfinite(n));
    IT_REQUIRE(m_value <= std::numeric_limits<Integer>::max()
                              - sign(m_step) * (n * m_step - 1));

    m_value += n * m_step;
    return *this;
}

//---------------------------------------------------------------------------//
/*!
 * \brief Compound subtraction-assignment operator
 *
 * \param[in] n The amoutn to subtract from the iterator
 *
 * \return A reference to this iterator
 */
template<typename Integer>
auto RangeIterator<Integer>::operator-=(difference_type n) -> This&
{
    IT_REQUIRE(std::isfinite(n));
    IT_REQUIRE(m_value >= std::numeric_limits<Integer>::lowest()
                              + sign(m_step) * n * m_step);

    m_value -= n * m_step;
    return *this;
}

//---------------------------------------------------------------------------//
// ARITHMETIC OPERATORS
//---------------------------------------------------------------------------//
/*!
 * \brief Add a distance \p n to iterator \p iter and return the result
 *
 * \tparam Integer1  The integral type for RangeIterator \p iter
 * \tparam Integer2  The integral type of the distance to add
 *
 * \param[in] iter  The integer to add to
 * \param[in] n     The distance to add to \p iter
 *
 * \return A new iterator pointing \p n distance from \p iter
 */
template<typename Integer1, typename Integer2>
auto operator+(const RangeIterator<Integer1>& iter, Integer2 n)
    -> RangeIterator<std::common_type_t<Integer1, Integer2>>
{
    static_assert(std::is_integral_v<Integer2>);
    IT_REQUIRE(std::isfinite(n));
    IT_REQUIRE(iter.value() <= std::numeric_limits<Integer1>::max()
                                   - sign(iter.step()) * (n * iter.step() - 1));

    using IT_t = std::common_type_t<Integer1, Integer2>;

    return RangeIterator<IT_t>(
        static_cast<IT_t>(iter.value()) + n * iter.step(), iter.step());
}

//---------------------------------------------------------------------------//
/*!
 * \brief Add a distance \p n to iterator \p iter and return the result
 *
 * \tparam Integer1  The integral type for RangeIterator \p iter
 * \tparam Integer2  The integral type of the distance to add
 *
 * \param[in] iter  The integer to add to
 * \param[in] n     The distance to add to \p iter
 *
 * \return A new iterator pointing \p n distance from \p iter
 */
template<typename Integer1, typename Integer2>
auto operator+(Integer1 n, const RangeIterator<Integer2>& iter)
    -> RangeIterator<std::common_type_t<Integer1, Integer2>>
{
    static_assert(std::is_integral_v<Integer1>);
    IT_REQUIRE(std::isfinite(n));
    IT_REQUIRE(iter.value() <= std::numeric_limits<Integer1>::max()
                                   - sign(iter.step()) * (n * iter.step() - 1));

    using IT_t = std::common_type_t<Integer1, Integer2>;

    return RangeIterator<IT_t>(
        static_cast<IT_t>(iter.value()) + n * iter.step(), iter.step());
}

//---------------------------------------------------------------------------//
/*!
 * \brief Produce the sum of two iterators
 *
 * \warning This operation is undefined if \p iter1 and \p iter2 do not have
 *          the same step length
 *
 * \tparam Integer1  The integral type of the first range iterator
 * \tparam Integer2  The integral type of the second range iterator
 *
 * \param[in] iter1  The first range iterator to sum
 * \param[in] iter2  The second range iterator to sum
 *
 * \return A sum of \p iter1 and \p iter2
 */
template<typename Integer1, typename Integer2>
auto operator+(const RangeIterator<Integer1>& iter1,
               const RangeIterator<Integer2>& iter2)
    -> RangeIterator<std::common_type_t<Integer1, Integer2>>
{
    IT_REQUIRE(iter1.step() == iter2.step());
    using IT_t = std::common_type_t<Integer1, Integer2>;
    IT_REQUIRE(iter1.value() <= std::numeric_limits<IT_t>::max()
                                    - sign(iter1.step()) * iter2.value());

    return RangeIterator<IT_t>(iter1.value() + iter2.value(), iter1.step());
}

//---------------------------------------------------------------------------//
/*!
 * \brief Produce an iterator subtracted \p n distance from \p iter
 *
 * \tparam Integer1  The integral type of the range iterator
 * \tparam Integer2  The distance type to subtract from \p iter
 *
 * \param[in] iter  The range iterator to subtract from
 * \param[in] n     The distance to subtract
 *
 * \return A new range iterator \p n distance subtracted from \p iter
 */
template<typename Integer1, typename Integer2>
auto operator-(const RangeIterator<Integer1>& iter, Integer2 n)
    -> RangeIterator<std::common_type_t<Integer1, Integer2>>
{
    static_assert(std::is_integral_v<Integer2>);
    using IT_t = std::common_type_t<Integer1, Integer2>;
    IT_REQUIRE(std::isfinite(n));
    IT_REQUIRE(iter.value() >= std::numeric_limits<IT_t>::lowest()
                                   + sign(iter.step()) * n * iter.step());

    return RangeIterator<IT_t>(iter.value() - n * iter.step(), iter.step());
}

//---------------------------------------------------------------------------//
/*!
 * \brief Compute the distance between \p iter1 and \p iter2
 *
 * \warning This operation is undefined if \p iter1 and \p iter2 do not have
 *          an equal step length
 *
 * \tparam Integer1  The integral type of the first range iterator
 * \tparam Integer2  The integral type of the second range iterator
 *
 * \param[in] iter1  The first range iterator to subtract from
 * \param[in] iter2  The second range iterator to subtract
 *
 * \return The distance between \p iter1 and \p iter2
 */
template<typename Integer1, typename Integer2>
typename RangeIterator<Integer1>::difference_type
operator-(const RangeIterator<Integer1>& iter1,
          const RangeIterator<Integer2>& iter2)
{
    IT_REQUIRE(iter1.step() == iter2.step());
    using diff_t = typename RangeIterator<Integer1>::difference_type;

    diff_t diff = static_cast<diff_t>(iter1.value())
                  - static_cast<diff_t>(iter2.value());
    return diff / iter1.step();
}

//---------------------------------------------------------------------------//
// BOOLEAN OPERATORS
//---------------------------------------------------------------------------//
/*!
 * \brief Returns whether \p iter1 and \p iter2 are equal
 *
 * Two range iterators are considered equal if their values are equal
 *
 * \warning It is the responsibility of the caller to ensure that the two
 *          range iterators being compared have the same step size
 *
 * \tparam Integer1  The integral type for the first range iterator
 * \tparam Integer2  The integral type for the second range iterator
 *
 * \param[in] iter1  The first range iterator to test
 * \param[in] iter2  The second range iterator to test
 *
 * \return True if the two iterators are equal; false otherwise
 */
template<typename Integer1, typename Integer2>
bool operator==(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2)
{
    IT_REQUIRE(iter1.step() == iter2.step());

    return iter1.value() == iter2.value();
}

//---------------------------------------------------------------------------//
/*!
 * \brief Return whether \p iter1 and \p iter2 are not equal
 *
 * \tparam Integer1  The integral type for the first range iterator
 * \tparam Integer2  The integral type for the second range iterator
 *
 * \param[in] iter1  The first range iterator to test
 * \param[in] iter2  The second range iterator to test
 *
 * \return True if the two iterators are not equal; false otherwise
 */
template<typename Integer1, typename Integer2>
bool operator!=(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2)
{
    return !operator==(iter1, iter2);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Return whether \p iter1 is less than \p iter2
 *
 * \warning This comparison is only valid if the step lengths of the two
 *          iterators are equal
 *
 * \tparam Integer1  The integral type for the first range iterator
 * \tparam Integer2  The integral type for the second range iterator
 *
 * \param[in] iter1  The first range iterator to test
 * \param[in] iter2  The second range iterator to test
 *
 * \return True if \p iter1 is less than \p iter2
 */
template<typename Integer1, typename Integer2>
bool operator<(const RangeIterator<Integer1>& iter1,
               const RangeIterator<Integer2>& iter2)
{
    IT_REQUIRE(iter1.step() == iter2.step());

    return sign(iter1.step()) * iter1.value()
           < sign(iter1.step()) * iter2.value();
}

//---------------------------------------------------------------------------//
/*!
 * \brief Return whether \p iter1 is less-than or equal to \p iter2
 *
 * \warning This comparison is only valid if the step lengths of the two
 *          iterators are equal
 *
 * \tparam Integer1  The integral type for the first range iterator
 * \tparam Integer2  The integral type for the second range iterator
 *
 * \param[in] iter1  The first range iterator to test
 * \param[in] iter2  The second range iterator to test
 *
 * \return True if \p iter1 is less than \p iter2
 */
template<typename Integer1, typename Integer2>
bool operator<=(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2)
{
    IT_REQUIRE(iter1.step() == iter2.step());

    return sign(iter1.step()) * iter1.value()
           <= sign(iter1.step()) * iter2.value();
}

//---------------------------------------------------------------------------//
/*!
 * \brief Return whether \p iter1 is greater than \p iter2
 *
 * \warning This comparison is only valid if the step lengths of the two
 *          iterators are equal
 *
 * \tparam Integer1  The integral type for the first range iterator
 * \tparam Integer2  The integral type for the second range iterator
 *
 * \param[in] iter1  The first range iterator to test
 * \param[in] iter2  The second range iterator to test
 *
 * \return True if \p iter1 is greater than \p iter2
 */
template<typename Integer1, typename Integer2>
bool operator>(const RangeIterator<Integer1>& iter1,
               const RangeIterator<Integer2>& iter2)
{
    IT_REQUIRE(iter1.step() == iter2.step());

    return !operator<=(iter1, iter2);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Return whether \p iter1 is greater-than or equal to \p iter2
 *
 * \warning This comparison is only valid if the step lengths of the two
 *          iterators are equal
 *
 * \tparam Integer1  The integral type for the first range iterator
 * \tparam Integer2  The integral type for the second range iterator
 *
 * \param[in] iter1  The first range iterator to test
 * \param[in] iter2  The second range iterator to test
 *
 * \return True if \p iter1 is greater-than or equal \p iter2
 */
template<typename Integer1, typename Integer2>
bool operator>=(const RangeIterator<Integer1>& iter1,
                const RangeIterator<Integer2>& iter2)
{
    IT_REQUIRE(iter1.step() == iter2.step());

    return !operator<(iter1, iter2);
}

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Create and return a range iterator
 *
 * \tparam Integer  An integral type
 *
 * \param[in] value  The value of the iterator
 * \param[in] step   The step length for the iterator
 *
 * \return The constructed range iterator
 */
template<typename Integer>
RangeIterator<Integer> makeRangeIterator(Integer value, Integer step)
{
    static_assert(std::is_integral_v<Integer>);

    return RangeIterator<Integer>(value, step);
}

//---------------------------------------------------------------------------//
}  // namespace detail
}  // namespace itertools

#endif  // ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_I_HH

//---------------------------------------------------------------------------//
// end of src/range/detail/RangeIterator.i.hh
//---------------------------------------------------------------------------//
