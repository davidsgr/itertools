//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/core/Macros.hh
 * \brief  Macros class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_CORE_MACROS_HH
#define ITERTOOLS_SRC_CORE_MACROS_HH

namespace itertools
{

//---------------------------------------------------------------------------//
/*!
 * \def ITER_UNLIKELY
 * \brief Indicates that the following boolean condition is unlikely to
 *        evaluate to true.
 *
 * This macro indicates that the following boolean condition is unlikely to
 * evaluate to true, and therefore the following code should be moved to
 * "cold" storage (i.e., not in the instruction cache).
 *
 * In C++20, the [[unlikely]] attribute can be used, but with C++17 we are more
 * limited.
 *
 */
#if defined __GNUC__ || __clang__
#define ITERTOOLS_UNLIKELY(COND) __builtin_expect(!!(COND), 0)
#else
// Not supported on other compilers
#define ITERTOOLS_UNLIKELY(COND) COND
#endif

//---------------------------------------------------------------------------//
/*!
 * \def ITER_LIKELY
 * \brief Indicates that the following boolean condition is likely to
 *        evaluate to true.
 *
 * This macro indicates that the following boolean condition is likely to
 * evaluate to true, and therefore the following code should be moved to
 * "hot" storage (i.e., in the instruction cache).
 *
 * In C++20, the [[likely]] attribute can be used, but with C++17 we are more
 * limited.
 *
 */
#if defined __GNUC__ || __clang__
#define ITERTOOLS_LIKELY(COND) __builtin_expect(!!(COND), 1)
#else
// Not supported on other compilers
#define ITER_LIKELY(COND) COND
#endif

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// INLINE DEFINITIONS
//---------------------------------------------------------------------------//
// #include "Macros.i.hh"

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_CORE_MACROS_HH
//---------------------------------------------------------------------------//
// end of src/core/Macros.hh
//---------------------------------------------------------------------------//
