//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/core/DBC.cc
 * \brief  DBC function definitions.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include "DBC.hh"

#include "Exception.hh"

namespace itertools
{
//---------------------------------------------------------------------------//
/*!
 * \brief Throw a DBC error exception class
 *
 * \param[in] condition  The test condition that failed
 * \param[in] condition_type  The type of test condition that failed
 * \param[in] filename        The name of the file where the DBC test failed
 * \param[in] line_number     The line number where the DBC test failed
 */
void throwDBCException(const std::string& condition,
                       const std::string& condition_type,
                       const std::string& filename,
                       unsigned long line_number)
{
    throw itertools::DBCException(
        condition, condition_type, filename, linenumber);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Throw a NotImplementedException class
 *
 * \param[in] msg         An informative message about the missing
 *                        functionality
 * \param[in] filename    The filename where the error occurred
 * \param[in] line_number The line number where the error occurred
 */
void throwNotImplementedException(const std::string& msg,
                                  const std::string& filename,
                                  unsigned long line_number)
{
    throw itertools::NotImplementedException(msg, filename, line_number);
}

//---------------------------------------------------------------------------//
/*!
 * \brief Throw a NotReachableException class
 *
 * \param[in] filename    The filename where the unreachable code point
 *                        occurred
 * \param[in] line_number The line number where the unreachable code point
 *                        occurred
 */
void throwNotReachableException(const std::string& filename,
                                unsigned long line_number)
{
    throw itertools::NotReachableException(filename, line_number);
}

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// end of src/core/DBC.cc
//---------------------------------------------------------------------------//
