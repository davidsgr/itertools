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
Exception::Exception(const std::string& msg,
                     const std::string& filename,
                     unsigned long line_number)
    : Base(), m_msg(msg), m_filename(filename), m_line_number(line_number)
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
 * \param[in] test_type    The type of DBC test that failed
 * \param[in] filename     The filename where the failed DBC test occurred
 * \param[in] line_number  The line number where the failed DBC test occurred
 */
DBCException::DBCException(const std::string& test_string,
                           const std::string& test_type,
                           const std::string& filename,
                           unsigned long line_number)
    : Base(buildErrorMessage(test_string, test_type, filename, line_number),
           filename,
           line_number)
    , m_test_string(test_string)
    , m_test_type(test_type)
{
    /* * */
}

//---------------------------------------------------------------------------//
// PRIVATE FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Build an error message for the failed DBC test.
 *
 * \param[in] test_string  A string representing the test that failed
 * \param[in] test_type    The type of DBC check that failed
 * \param[in] filename     The name of the file where the failure occurred
 * \param[in] line_number  The line number where the failure occurred
 *
 * \return An error message describing the failed DBC test.
 */
std::string DBCException::buildErrorMessage(const std::string& test_string,
                                            const std::string& test_type,
                                            const std::string& filename,
                                            unsigned long line_number)
{
    return test_string + " failed " + test_type + " DBC test in " + filename
           + ":" + std::to_string(line_number);
}

//===========================================================================//
// NotImplementedException IMPLEMENTATION
//===========================================================================//

//---------------------------------------------------------------------------//
// CONSTRUCTOR
//---------------------------------------------------------------------------//
/*!
 * \brief Constructor
 *
 * \param[in] msg          A message describing the code not implemented
 * \param[in] filename     The filename where the unimplemented code was
 *                         encountered
 * \param[in] line_number  The line number where the unimplemented code was
 *                         encountered
 */
NotImplementedException::NotImplementedException(const std::string& msg,
                                                 const std::string& filename,
                                                 unsigned long line_number)
    : Base(NotImplementedException::buildErrorMessage(
               msg, filename, line_number),
           filename,
           line_number)
    , m_msg(msg)
{
    /* * */
}

//---------------------------------------------------------------------------//
// PRIVATE FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Construct an informative error message
 *
 * \param[in] msg          A message describing the code not implemented
 * \param[in] filename     The filename where the unimplemented code was
 *                         encountered
 * \param[in] line_number  The line number where the unimplemented code was
 *                         encountered
 *
 * \return A descriptive message describing the unimplemented capability
 */
std::string
NotImplementedException::buildErrorMessage(const std::string& msg,
                                           const std::string& filename,
                                           unsigned long line_number)
{
    return msg + " not implemented at " + filename + ":"
           + std::to_string(line_number);
}

//===========================================================================//
// NotReachableException IMPLEMENTATION
//===========================================================================//

//---------------------------------------------------------------------------//
// CONSTRUCTOR
//---------------------------------------------------------------------------//
/*!
 * \brief Constructor
 *
 * \param[in] filename     The filename where the unreachable code was reached
 * \param[in] line_number  The line number where the unreachable code was
 *                         reached
 */
NotReachableException::NotReachableException(const std::string& filename,
                                             unsigned long line_number)
    : Base(NotReachableException::buildErrorMessage(filename, line_number),
           filename,
           line_number)
{
    /* * */
}

//---------------------------------------------------------------------------//
// PUBLIC FUNCTIONS
//---------------------------------------------------------------------------//
/*!
 * \brief Construct the error message
 *
 * \param[in] filename     The filename where the unreachable code was reached
 * \param[in] line_number  The line number where the unreachable code was
 *                         reached
 */
std::string
NotReachableException::buildErrorMessage(const std::string& filename,
                                         unsigned long line_number)
{
    return "Logically unreachable code block reached at " + filename + ":"
           + std::to_string(line_number);
}

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
// end of src/core/Exception.cc
//---------------------------------------------------------------------------//
