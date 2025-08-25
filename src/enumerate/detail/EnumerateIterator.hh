//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/enumerate/detail/EnumerateIterator.hh
 * \brief  EnumerateIterator class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_ENUMERATE_DETAIL_ENUMERATEITERATOR_HH
#define ITERTOOLS_SRC_ENUMERATE_DETAIL_ENUMERATEITERATOR_HH

#include <iterator>
#include <tuple>

namespace itertools
{
//===========================================================================//
/*!
 * \class EnumerateIterator
 * \brief <++>
 *
 * Long description or discussion goes here.
 *
 * \example enumerate/tests/tstEnumerateIterator.cc
 */
//===========================================================================//

template<typename IntegerType, typename IteratorType>
class EnumerateIterator
{
  public:
    //! Public type aliases
    using IntegerType_t = std::remove_reference_t<IntegerType>;
    using IteratorType_t = std::remove_reference_t<IteratorType>;
    using value_type
        = std::tuple<IntegerType_t,
                     std::iterator_traits<IteratorType_t>::value_type>;
    using reference
        = std::tuple<IntegerType_t,
                     std::iterator_traits<IteratorType_t>::reference>;
    using pointer = std::tuple<IntegerType_T,
                               std::iterator_traits<IteratorType_t>::pointer>;
    using difference_type
        = std::iterator_traits<IteratorType_t>::difference_type;
    using iterator_category
        = std::iterator_traits<IteratorType_t>::iterator_category;
    using This = EnumerateIterator<IntegerType, IteratorType>;

  public:
    // Default constructor
    EnumerateIterator() = default;

    // Constructor
    inline EnumerateIterator(IntegerType count, IteratorType iter);

    // Copy constructible from convertible parameters
    template<typename OtherIntegerType, typename OtherIteratorType>
    inline EnumerateIterator(
        const EnumerateIterator<OtherIntegerType, OtherIteratorType>& other_iter);

    // Copy assignment
    template<typename OtherIntegerType, typename OtherIteratorType>
    inline This&
    operator=(const EnumerateIterator<OtherIntegerType, OtherIteratorType>&
                  other_iter);

    // >>> INCREMENT
    // Pre-increment operator
    This& operator++();

    // Post-increment operator
    This operator++(int);

    // >>> DECREMENT
    // Pre-decrement operator
    This& operator--();

    // Post-decrement operator
    This operator--();

    // >>> DEREFERENCE AND POINTER
    // Dereference
    reference operator*();

    // Pointer
    pointer operator->();

  private:
    // >>> DATA
};

//---------------------------------------------------------------------------//
// HELPER FUNCTIONS
//---------------------------------------------------------------------------//

template<typename IntegerType, typename OtherIntegerType, typename IteratorType>
EnumerateIterator<IntegerType, IteratorType>
operator+(const EnumerateIterator<IntegerType, IteratorType>& iter,
          OtherIntegerType n);

template<typename IntegerType, typename OtherIntegerType, typename IteratorType>
EnumerateIterator<IntegerType, IteratorType>
operator+(OtherIntegerType n,
          const EnumerateIterator<IntegerType, IteratorType>& iter);

template<typename IntegerType, typename OtherIntegerType, typename IteratorType>
EnumerateIterator<IntegerType, IteratorType>
operator-(const EnumerateIterator<IntegerType, IteratorType>& iter,
          OtherIntegerType n);

template<typename IntegerType1,
         typename IntegerType2,
         typename IteratorType1,
         typename IteratorType2>
         typename 

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// INLINE DEFINITIONS
//---------------------------------------------------------------------------//
// #include "EnumerateIterator.i.hh"

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_ENUMERATE_DETAIL_ENUMERATEITERATOR_HH
//---------------------------------------------------------------------------//
// end of src/enumerate/detail/EnumerateIterator.hh
//---------------------------------------------------------------------------//
