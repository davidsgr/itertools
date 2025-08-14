//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/core/DBC.hh
 * \brief  DBC class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_CORE_DBC_HH
#define ITERTOOLS_SRC_CORE_DBC_HH

#include <string>

#ifndef ITERTOOLS_DBC
#define ITERTOOLS_DBC true
#endif

// Defines IT_REQUIRE
#define ITERTOOLS_ASSERT_(COND, COND_TYPE)             \
    do                                                 \
    {                                                  \
        if (ITERTOOLS_UNLIKELY(!(COND)))               \
        {                                              \
            ::itertools::throwDBCException(            \
                #COND, COND_TYPE, __FILE__, __LINE__); \
        }                                              \
    } while (false)
#define ITERTOOLS_NO_ASSERT_(COND, COND_TYPE) \
    do                                        \
    {                                         \
        if (false && (COND)) {}               \
    } while (false)

#if ITERTOOLS_DBC
#define IT_REQUIRE(COND) ITERTOOLS_ASSERT_(COND, "precondition")
#define IT_CHECK(COND) ITERTOOLS_ASSERT_(COND, "intermediate")
#define IT_ENSURE(COND) ITERTOOLS_ASSERT_(COND, "postcondition")
#define IT_REMEMBER(COND) COND
#else
#define IT_REQUIRE(COND) ITERTOOLS_NO_ASSERT_(COND, "precondition")
#define IT_CHECK(COND) ITERTOOLS_NO_ASSERT_(COND, "intermediate")
#define IT_ENSURE(COND) ITERTOOLS_NO_ASSERT_(COND, "postcondition")
#define IT_REMEMBER(COND)
#endif

#define IT_NOT_IMPLEMENTED(MSG) \
    throwNotImplementedException(MSG, __FILE__, __LINE__)

#define IT_NOT_REACHABLE() throwNotReachableException(__FILE__, __LINE__)

namespace itertools
{
// Throw a DBC exception
[[no_return]] void throwDBCException(const std::string& condition,
                                     const std::string& condition_type,
                                     const std::string& filename,
                                     unsigned long line_number);

// Throw a NotImplementedException
[[no_return]] void throwNotImplementedException(const std::string& msg,
                                                const std::string& filename,
                                                unsigned long line_number);

// Throw a NotReachableException
[[no_return]] void throwNotReachableException(const std::string& filename,
                                              unsigned long line_number);

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// INLINE DEFINITIONS
//---------------------------------------------------------------------------//
// #include "DBC.i.hh"

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_CORE_DBC_HH
//---------------------------------------------------------------------------//
// end of src/core/DBC.hh
//---------------------------------------------------------------------------//
