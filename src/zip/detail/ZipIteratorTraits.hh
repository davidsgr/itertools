//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/zip/detail/ZipIteratorTraits.hh
 * \brief  ZipIteratorTraits class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_ZIP_DETAIL_ZIPITERATORTRAITS_HH
#define ITERTOOLS_SRC_ZIP_DETAIL_ZIPITERATORTRAITS_HH

#include <iterator>
#include <tuple>

namespace itertools
{
namespace detail
{

template<typename...>
struct ZipIteratorTraits
{
    /* not used */
};

template<typename Iterator>
struct ZipIteratorTraits
{
    using difference_type =
        typename std::iterator_traits<Iterator>::difference_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using iterator_category =
        typename std::iterator_traits<Iterator>::iterator_category
};

template<typename Iterator1, typename Iterator2>
struct ZipIteratorTraits
{
    using difference_type = std::common_type_t<
        typename std::iterator_traits<Iterator1>::difference_type,
        typename std::iterator_traits<Iterator2>::difference_type>;
    using reference
        = std::tuple<typename std::iterator_traits<Iterator1>::reference,
                     typename std::iterator_traits<Iterator2>::reference>;
    using pointer
        = std::tuple<typename std::iterator_traits<Iterator1>::pointer,
                     typename std::iterator_traits<Iterator2>::pointer>;
    using value_type
        = std::tuple<typename std::iterator_traits<Iterator1>::value_type,
                     typename std::iterator_traits<Iterator2>::value_type>;
    using iterator_category = std::common_type_t<
        typename std::iterator_traits<Iterator1>::iterator_category,
        typename std::iterator_traits<Iterator2>::iterator_category>;
};

template<typename Iterator1, typename... Iterators>
struct ZipIteratorTraits
{
  private:
    using ref1
        = std::tuple<typename std::iterator_traits<Iterator1>::reference>;
    using refs = typename ZipIteratorTraits<Iterators...>::reference;
    using ptr1 = std::tuple<typename std::iterator_traits<Iterator1>::pointer>;
    using ptrs = typename ZipIteratorTraits<Iterators...>::pointer;
    using vt1
        = std::tuple<typename std::iterator_traits<Iterator1>::value_type>;
    using vts = typename ZipIteratorTraits<Iterators...>::value_type;

  public:
    using difference_type = std::common_type_t<
        typename std::iterator_traits<Iterator1>::difference_type,
        typename ZipIteratorTraits<Iterators...>::difference_type>;
    using reference
        = decltype(std::tuple_cat(declval<ref1>(), declval<refs>()));
    using pointer = decltype(std::tuple_cat(declval<ptr1>(), declval<ptrs>());
    using value_type = decltype(std::tuple_cat(declval<vt1>(), declval<vts>()));
    using iterator_category = std::common_type_t<typename std::iterator_traits<Iterator1>::iterator_category,
    typename ZipIteratorTraits<Iterators...>::iterator_category>;
};

template<class ZipIterator>
struct is_bidir_zip_iter
    : public std::is_base_of<std::bidirectional_iterator_tag,
                             typename ZipIterator::iterator_category>
{
};
template<class ZipIterator>
constexpr bool is_bidir_zip_iter_v = is_bidir_zip_iter<ZipIterator>::value;

template<class ZipIterator>
struct is_random_access_zip_iter
    : public std::is_base_of<std::random_access_iterator_tag,
                             typename ZipIterator::iterator_category>
{
};
template<class ZipIterator>
constexpr bool is_random_access_zip_iter_v
    = is_random_access_zip_iter<ZipIterator>::value;

//---------------------------------------------------------------------------//
}  // namespace detail
}  // namespace itertools

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_ZIP_DETAIL_ZIPITERATORTRAITS_HH
//---------------------------------------------------------------------------//
// end of src/zip/detail/ZipIteratorTraits.hh
//---------------------------------------------------------------------------//
