//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/core/Exception.cc
 * \brief  Exception class definitions.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//

#include "Exception.hh"

namespace itertools
{

//===========================================================================//
// Exception IMPLEMENTATION
//===========================================================================//

//---------------------------------------------------------------------------//
// CONSTRUCTOR
//---------------------------------------------------------------------------//
/*!
 * \brief Construct a general IterTools exception class
 *
 * \param[in] msg  An informative error message
 */
Exception::Exception(const std::string& msg) : Base(msg)
{
    /* * */
}

//===========================================================================//
// DBCException IMPLEMENTATION
//===========================================================================//

//---------------------------------------------------------------------------//
// CONSTRUCTOR
//---------------------------------------------------------------------------//
/*!
 * \brief Construct a DBCException class
 *
 * \param[in] test_string  A string describing the test that failed
 * \param[in] filename     The filename where the failed DBC test occurred
 * \param[in] line_number  The line number where the failed DBC test occurred
 */
DBCException::DBCException(const std::string& test_string,
                           const std::string& filename,
                           unsigned long line_number)
    : Base(buildErrorMessage(test_string, filename, line_number))
    , m_test_string(test_string)
    , m_filename(filename)
    , m_line_number(line_number)
{
    /* * */
}

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// end of src/core/Exception.cc
//---------------------------------------------------------------------------//
