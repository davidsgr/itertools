//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/range/detail/RangeIterator.hh
 * \brief  RangeIterator class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH
#define ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH

#include <cmath>
#include <iterator>
#include <type_traits>

#include "core/DBC.hh"

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
    using This = RangeIterator<Iterator>;
    using difference_type = std::ptrdiff_t;
    using value_type = Integer_t;
    using reference = std::add_reference<Integer_t>;
    using pointer = std::add_pointer<Integer_t>;
    using iterator_category = std::forward_iterator_tag;

  public:
    // Default constructor
    RangeIterator() = default;

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
    //! Dereference
    reference operator*() { return m_value; }

    //! Pointer
    pointer operator->() { return &m_value; }

    //! Indexing
    reference operator[](difference_type n) { return m_value + m_step * n; }

    // >>> COMPOUND ARITHMETIC
    // Compound arithmetic operators
    This& operator+=(difference_type n);
    This& operator-=(difference_type n);

    // >>> ACCESSORS
    //! Return the current value
    const reference value() const { return m_value; }

    //! Return the step length
    Integer step() const { return m_step; }

  private:
    // >>> DATA
    //! Stores the integral value of the iterator
    Integer m_value;

    //! Stores the distance to travel each iteration
    Integer m_step;
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
operator+(Integer2 n, const RangeIterator<Integer1>& iter);

// Sum two range iterators
template<typename Integer1, typename Integer2>
RangeIterator<std::common_type_t<Integer1, Integer2>>
operator+(const RangeIterator<Integer1>& iter1,
          const RangeIterator<Integer2>& iter2);

// Difference between a range iterator and an integral value
template<typename Integer1, typename Integer2>
RangeIterator<Integer1>
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

//===========================================================================//
// INLINE FUNCTION IMPLEMENTATION
//===========================================================================//

//---------------------------------------------------------------------------//
// CONSTRUCTORS
//---------------------------------------------------------------------------//
/*!
 * \brief Construct the range iterator with the given value and optional step
 *        length
 *
 * \param[in] value  The value to initialize the range iterator with
 * \param[in] step   The step size
 */
template<typename Integer>
RangeIterator<Iterator>::RangeIterator(Iterator value, Iterator step)
    : m_value(value), m_step(step)
{
    IM_REQUIRE(std::isfinite(value));
    IM_REQUIRE(std::isfinite(step));
    IM_REQUIRE(m_step != 0);
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
auto RangeIterator<Iterator>::operator++() -> This&
{
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
auto RangeIterator<Iterator>::operator++(int) -> This
{
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
auto RangeIterator<Iterator>::operator--() -> This&
{
    IM_REQUIRE(std::is_signed_v<Integer> || m_value >= m_step);

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
auto RangeIterator<Iterator>::operator--(int) -> This
{
    IM_REQUIRE(std::is_signed_v<Integer> || m_value > 0);

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
auto RangeIterator<Iterator>::operator+=(difference_type n) -> This&
{
    IM_REQUIRE(std::isfinite(n));

    m_value += n * step;
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
    IM_REQUIRE(std::is_signed_v<Integer> || m_value > 0);
    IM_REQUIRE(std::finite(n));

    m_value -= n * step;
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
    static_assert(std::is_integral_v<Integer2>());
    IM_REQUIRE(std::isfinite(n));

    using IT_t = std::common_type_t<Integer1, Integer2>;

    return RangeIterator<IT_t>(iter.value() + n * iter.step(), iter.step());
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
    -> RnageIterator<std::common_type_t<Integer1, Integer2>>
{
    static_assert(std::is_integral_v<Integer1>());
    IM_REQUIRE(std::isfinite(n));

    using IT_t = std::common_type_t<Integer1, Integer2>;

    return RangeIterator<IT_t>(iter.value() + n * iter.step(), iter.step());
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
    -> RnageIterator<std::common_type_t<Integer1, Integer2>>
{
    IM_REQUIRE(iter1.step() == iter2.step());
    using IT_t = std::common_type_t<Integer1, Integer2>;

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
    static_assert(std::is_integral_v<Integer2>());

    using IT_t = std::common_type_t<Integer1, Integer2>;
    IM_REQUIRE(std::issigned_v<IT_t> || iter1.value() >= n * iter1.step());
    IM_REQUIRE(std::isfinite(n));

    return RangeIterator<Integer1>(iter1.value() - n * iter1.step(),
                                   iter1.step());
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
    IM_REQUIRE(iter1.step() == iter2.step());
    using diff_t = RangeIterator<Integer1>::difference_type;

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
 * Two range iterators are considered equal if both the value and their step
 * size are equal
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
    return iter1.value() == iter2.value() && iter1.step() == iter2.step();
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
bool operator<(const RnageIterator<Integer1>& iter1,
               const RangeIterator<Integer2>& iter2)
{
    IM_REQUIRE(iter1.step() == iter2.step());

    return iter1.value() < iter2.value();
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
    IM_REQUIRE(iter1.step() == iter2.step());

    return iter1.value() <= iter2.value();
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
    IM_REQUIRE(iter1.step() == iter2.step());

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
    IM_REQUIRE(iter1.step() == iter2.step());

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
RangeIterator<Iterator> makeRangeIterator(Integer value, Integer step = 1)
{
    static_assert(std::is_integral_v<Integer_t>);

    return RangeIterator<Integer>(value, step);
}

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_RANGE_DETAIL_RANGEITERATOR_HH
//---------------------------------------------------------------------------//
// end of src/range/detail/RangeIterator.hh
//---------------------------------------------------------------------------//
