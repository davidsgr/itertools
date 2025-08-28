//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/zip/detail/ZipIterator.hh
 * \brief  ZipIterator class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_ZIP_DETAIL_ZIPITERATOR_HH
#define ITERTOOLS_SRC_ZIP_DETAIL_ZIPITERATOR_HH

#include "ZipIteratorTraits.hh"

namespace itertools
{
//===========================================================================//
/*!
 * \class ZipIterator
 * \brief <++>
 *
 * Long description or discussion goes here.
 *
 * \example zip/tests/tstZipIterator.cc
 */
//===========================================================================//

template<typename Iterator1, typename... Iterators>
class ZipIterator
{
  public:
    //! Public type aliases
    using difference_type =
        typename ZipIteratorTraits<Iterator1, Iterators...>::difference_type;
    using reference =
        typename ZipIteratorTraits<Iterator1, Iterators...>::reference;
    using pointer =
        typename ZipIteratorTraits<Iterator1, Iterators...>::pointer;
    using value_type =
        typename ZipIteratorsTraits<Iterator1, Iterators...>::value_type;
    using iterator_category =
        typename ZipIteratorTraits<Iterator1, Iterators...>::iterator_category;
    using This = ZipIterator<Iterator1, Iterators...>;
    using Storage_t = std::tuple<Iterator1&&, Iterators&&...>;

  public:
    // Default constructor
    ZipIterator() = default;

    // Construct with multiple iterators
    template<typename OtherIterator1, typename... OtherIterators>
    ZipIterator(OtherIterator1&& other_iter1, OtherIterators...&& other_iters);

    // Copy operator taking iterators
    template<typename OtherIterator1, typename... OtherIterators>
    This&
    operator=(OtherIterator1&& other_iter1, OtherIterators...&& other_iters);

    // >>> INCREMENT
    // Pre-increment operator
    inline This& operator++();

    // Post-increment operator
    inline This operator++(int);

    // >>> DECREMENT
    // Pre-decrement operator
    inline This& operator--();

    // Post-decrement operator
    inline This operator--(int);

    // >>> DEREFERENCE, POINTER, INDEX
    // Dereference the pointer
    inline reference operator*();

    // Access underlying pointers
    inline pointer operator->();

    // Index operation
    inline reference operator[](difference_type n);

    // >>> COMPOUND ARITHMETIC
    // Compound addition-assignment operator
    inline This& operator+=(difference_type n);

    // Compound subtraction-assignment operator
    inline This& operator-=(difference_type n);

    // >>> ACCESSORS
    // Access a particular underlying iterator
    template<std::size_t I>
    std::tuple_element_t<I, Storage_t> get();

    // Access a particular underlying iterator
    template<std::size_t I>
    std::tuple_element_t<I, Storage_t> get() const;

    //! Get the entire tuple of iterators
    Storage_t& getIters() { return m_iterators; }

    //! Get the entire tuple of iterators
    const Storage_t& getIters() const { return m_iterators; }

  private:
    // >>> DATA
    //! Stores the underlying iterators
    Storage_t m_iterators;
};

//---------------------------------------------------------------------------//
// ARITHMETIC OPERATORS
//---------------------------------------------------------------------------//
// Sum an iterator and an integral value
template<typename Iterator1, typename... Iterators>
inline ZipIterator<Iterator1, Iterators...>
operator+(const ZipIterator<Iterator1, Iterators...>& zip_iter,
          typename ZipIterator<Iterator1, Iterators...>::difference_type n);

// Sum an integral value and an iterator
template<typename Iterator1, typename... Iterators>
inline ZipIterator<Iterator1, Iterators...>
operator+(typename ZipIterator<Iterator1, Iterators...>::difference_type n,
          const ZipIterator<Iterator1, Iterators...>& zip_iter);

// Subtract an integral value from an iterator
template<typename Iterator1, typename... Iterators>
inline ZipIterator<Iterator1, Iterators...>
operator-(const ZipIterator<Iterator1, Iterators...>& zip_iter,
          typename ZipIterator<Iterator1, Iterators...>::difference_type n);

// Subtract two zip iterators
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
std::common_type_t<
    typename ZipIterator<Iterator1, Iterators...>::difference_type,
    typename ZipIterator<OtherIterator1, OtherIterators...>::difference_type>
operator-(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
          const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

//---------------------------------------------------------------------------//
// BOOLEAN OPERATORS
//---------------------------------------------------------------------------//
// Test equality between two zip iterators
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
inline bool
operator==(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
           const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

// Test inequality between two zip iterators
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
inline bool
operator!=(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
           const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

// Test if zip_iter1 is less than zip_iter2
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
inline bool
operator<(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
          const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

// Test if zip_iter1 is less-than or equal to zip_iter2
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
inline bool
operator<=(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
           const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

// Test if zip_iter1 is greater than zip_iter2
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
inline bool
operator>(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
          const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

// Test if zip_iter1 is greater-than or equal to zip_iter2
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
inline bool
operator>=(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
           const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2);

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
ZipIterator<Iterator1, Iterators...>
makeZipIter(Iterator1&& iter1, Iterators...&& iters);

//===========================================================================//
// INLINE IMPLEMENTATION
//===========================================================================//

namespace
{
//---------------------------------------------------------------------------//
template<ckass ZipIterator, typename Op, std::size_t I...>
void forEach(ZipIterator& zip_iter, Op&& op, std::index_sequence<I...>)
{
    static_assert(std::tuple_size<Tup> == sizeof...(I));

    (op(zip_iter.get<I>)...);
}

template<typename ZipIterator, typename Op, std::size_t I...>
decltype(auto)
generate(ZipIterator& zip_iter, Op&& op, std::index_sequence<I...>)
{
    static_assert(std::tuple_size<Tup> == sizeof...(I));

    return std::make_tuple((op(zip_iter.std::get<I>())...));
}

template<typename Tuple1, typename Tuple2, typename Op, std::size_t I>
bool allOf_impl(const Tuple1& tup1, const Tuple2& tup2, Op&& op)
{
    static_assert(std::tuple_size_v<Tuple1> == std::tuple_size_v<Tuple2>);
    if constexpr (I == std::tuple_size_v<Tuple1>)
    {
        return true;
    }
    else
    {
        return op(std::get<I>(tup1), std::get<I>(tup2))
               && allOf_impl<I + 1>(tup1, tup2, std::forward<Op>(op));
    }
}

template<typename Tuple1, typename Tuple2, typename Op>
bool allOf(const Tuple1& tup1, const Tuple2& tup2, Op&& op)
{
    static_assert(std::tuple_size_v<Tuple1> == std::tuple_size_v<Tuple2>);

    // Get result for first element
    bool result = op(std::get<0>(tup1), std::get<0>(tup2));
    return result && allOf_impl<1>(tup1, tup2, std::forward<Op>(op), result);
}

//---------------------------------------------------------------------------//
}  // namespace

//---------------------------------------------------------------------------//
// CONSTRUCTOR
//---------------------------------------------------------------------------//
/*!
 * \brief Construct with multiple iterators
 *
 * \tparam OtherIterator1  An iterator type convertible to Iterator1
 * \tparam OtherIterators  Parameter pack containing iterators convertible to
 *                         Iterators
 *
 * \param[in] other_iter1  The first iterator to use for construction
 * \param[in] other_iters  The remaining iterators to use for construction
 */
template<typename Iterator, typename... Iterators>
template<typename OtherIterator1, typename... OtherIterators>
ZipIterator<Iterator1, Iterators...>::ZipIterator(
    OtherIterator1&& other_iter1, OtherIterators...&& other_iters)
    : m_iterators(std::forward<OtherIterator1>(other_iter1),
                  std::forward<OtherIterators...>(other_iters...))
{
    /* * */
}

//---------------------------------------------------------------------------//
// COPY OPERATOR
//---------------------------------------------------------------------------//
/*!
 * \brief Copy from multiple iterators
 *
 * \tparam OtherIterator1  An iterator type convertible to Iterator1
 * \tparam OtherIterators  Parameter pack containing iterators convertible to
 *                         Iterators
 *
 * \param[in] other_iter1  The first iterator to copy
 * \param[in] other_iters  The remaining iterators to copy
 *
 * \return A reference to this ZipIterator
 */
template<typename Iterator, typename... Iterators>
template<typename OtherIterator1, typename... OtherIterators>
auto ZipIterator<Iterator, Iterators...>::operator=(
    OtherIterator1&& other_iter1, OtherIterators...&& other_iters) -> This&
{
    m_iterators = {std::forward<OtherIterator1>(other_iter1),
                   std::forward<OtherIterators...>(other_iters)};
    return *this;
}

//---------------------------------------------------------------------------//
// INCREMENT
//---------------------------------------------------------------------------//
/*!
 * \brief Pre-increment operator incrementing all of the underlying iterators
 *
 * \return A reference to this ZipIterator after the increment is performed
 */
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator++() -> This&
{
    forEach(
        m_iterators,
        [](auto& v) { ++v; },
        std::index_sequence_for<Iterator1, Iterators...>());
    return *this;
}

//---------------------------------------------------------------------------//
/*!
 * \brief Post-increment operator incrementing all of the underlying iterators
 *
 * \return A copy of this ZipIterator before the increment is performed
 */
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator++(int) -> This
{
    This copy = *this;
    ++(*this);
    return copy;
}

//---------------------------------------------------------------------------//
// DECREMENT
//---------------------------------------------------------------------------//
/*!
 * \brief Pre-decrement operator decrementing all of the underlying iterators
 *
 * \return A reference to this ZipIterator after the decrement is performed
 */
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator--() -> This&
{
    static_assert(itertools::detail::is_bidir_zip_iter_v<This>);

    forEach(
        m_iterators,
        [](auto& v) { --v; },
        std::index_sequence_for<Iterator1, Iterators...>());
    return *this;
}

//---------------------------------------------------------------------------//
/*!
 * \brief Post-decrement operator decrementing all of the underlying iterators
 *
 * \return A copy of this ZipIterator before the decrement is performed
 */
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator--(int) -> This
{
    static_assert(itertools::detail::is_bidir_zip_iter_v<This>);

    This copy = *this;
    --(*this);
    return copy;
}

//---------------------------------------------------------------------------//
// DEREFERENCE, POINTER, INDEX
//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator*() -> reference
{
    return apply(
        m_iterators,
        [](auto& v) { return *v; },
        std::index_sequence_for<Iterator1, Iterators...>());
}

//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator->() -> pointer
{
    return apply(
        m_iterators,
        [](auto& v) { return &(*v); },
        std::index_sequence_for<Iterator1, Iterators...>());
}

//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator[](difference_type n)
    -> reference
{
    static_assert(itertools::detail::is_random_access_zip_iter_v<This>);

    return apply(
        m_iterators,
        [n](auto& v) { return v[n] l },
        std::index_sequence_for<Iterator1, Iterators...>());
}

//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator+=(difference_type n)
    -> This&
{
    static_assert(is_random_access_zip_iter_v<This>);

    forEach(
        m_iterators,
        [n](auto& v) { v += n },
        std::index_sequence_for<Iterator1, Iterators...>());
    return *this;
}

//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
auto ZipIterator<Iterator1, Iterators...>::operator-=(difference_type n)
    -> This&
{
    static_assert(
        std::is_base_of_v<std::random_access_iterator_tag, iterator_category>);

    auto op = [n](auto& v) { v -= n; };
    forEach(m_iterators,
            std::move(op),
            std::index_sequence_for<Iterator1, Iterators...>());
    return *this;
}

//---------------------------------------------------------------------------//
// ARITHMETIC OPERATORS
//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
ZipIterator<Iterator1, Iterators...>
operator+(const ZipIterator<Iterator1, Iterators...>& zip_iter,
          typename ZipIterator<Iterator1, Iterators...>::difference_type n)
{
    static_assert(
        std::is_base_of_v<
            std::random_access_iterator_tag,
            typename ZipIterator<Iterator1, Iterators...>::iterator_category>);

    auto op = [n](auto& v) { return v + n; };
    return ZipIterator(
        apply(zip_iter,
              std::move(op),
              std::index_sequence_for<Iterator1, Iterators...>()));
}

//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
ZipIterator<Iterator1, Iterators...>
operator+(typename ZipIterator<Iterator1, Iterators...>::difference_type n,
          const ZipIterator<Iterator1, Iterators...>& zip_iter)
{
    static_assert(
        std::is_base_of_v<
            std::random_access_iterator_tag,
            typename ZipIterator<Iterator1, Iterators...>::iterator_category>);

    return zip_iter + n;
}

//---------------------------------------------------------------------------//
template<typename Iterator1, typename... Iterators>
ZipIterator<Iterator1, Iterators...>
operator-(const ZipIterator<Iterator1, Iterators...>& zip_iter,
          typename ZipIterator<Iterator1, Iterators...>::difference_type n)
{
    static_assert(
        std::is_base_of_v<
            std::random_access_iterator_tag,
            typename ZipIterator<Iterator1, Iterators...>::iterator_category>);

    return zip_iter + (-n);
}

//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
auto operator-(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
               const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
    -> std::common_type_t<
        typename ZipIterator<Iterator1, Iterators...>::difference_type,
        typename zipIterator<OtherIterator1, OtherIterators...>::difference_type>
{
    static_assert(
        std::is_base_of_v<
            std::random_access_iterator_tag,
            typename ZipIterator<Iterator1, Iterators...>::iterator_category>);

    return zip_iter1.get<0>() - zip_iter2.get<0>();
}

//---------------------------------------------------------------------------//
// BOOLEAN OPERATORS
//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
bool operator==(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
                const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
{
    static_assert(sizeof...(Iterator1, Iterators...)
                  == sizeof...(OtherIterator1, OtherIterators...));

    bool result = (zip_iter1.get<0>() == zip_iter2.get<0>());
    IM_ENSURE(result == allOf(zip_iter1, zip_iter2, [](auto v, auto w) {
                  return v == w;
              }));
    return result;
}

//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
bool operator!=(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
                const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
{
    return !operator==(zip_iter1, zip_iter2);
}

//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
bool operator<(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
               const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
{
    static_assert(sizeof...(Iterator1, Iterators...)
                  == sizeof...(OtherIterator1, OtherIterators...));

    bool result = (zip_iter1.get<0>() < zip_iter2.get<0>());
    IM_ENSURE(result == allOf(zip_iter1, zip_iter2, [](auto v, auto w) {
                  return v < w;
              }));
    return result;
}

//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
bool operator<=(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
                const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
{
    static_assert(sizeof...(Iterator1, Iterators...)
                  == sizeof...(OtherIterator1, OtherIterators...));
    return zip_iter1 < zip_iter2 || zip_iter1 == zip_iter2;
}

//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
bool operator>(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
               const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
{
    static_assert(sizeof...(Iterator1, Iterators...)
                  == sizeof...(OtherIterator1, OtherIterators...));
    return !(zip_iter1 <= zip_iter2);
}

//---------------------------------------------------------------------------//
template<typename Iterator1,
         typename OtherIterator1,
         typename... Iterators,
         typename... OtherIterators>
bool operator>=(const ZipIterator<Iterator1, Iterators...>& zip_iter1,
                const ZipIterator<OtherIterator1, OtherIterators...>& zip_iter2)
{
    static_assert(sizeof...(Iterator1, Iterators...)
                  == sizeof...(OtherIterator1, OtherIterators...));
    return !(zip_iter1 < zip_iter2);
}

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_ZIP_DETAIL_ZIPITERATOR_HH
//---------------------------------------------------------------------------//
// end of src/zip/detail/ZipIterator.hh
//---------------------------------------------------------------------------//
