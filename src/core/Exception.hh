//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   src/core/Exception.hh
 * \brief  Exception class declaration.
 * \note   Copyright (c) 2025 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
#ifndef ITERTOOLS_SRC_CORE_EXCEPTION_HH
#define ITERTOOLS_SRC_CORE_EXCEPTION_HH

#include <exception>
#include <string>

namespace itertools
{
//===========================================================================//
/*!
 * \class Exception
 * \brief Base class for all exceptions emitted by the IterTools library
 */
//===========================================================================//

class Exception : public std::exception
{
    using Base = std::exception;

  public:
    // Constructor
    Exception(const std::string& msg,
              const std::string& filename,
              unsigned long line_number);

    //! Return the filename where the error occurred
    const std::string& filename() const { return m_filename; }

    //! Return the line number where the error occurred
    unsigned long lineNumber() const { return m_line_number; }

    // Return the what() message
    const char* what() const noexcept final { return m_msg; }

  private:
    //! Holds the error message
    std::string m_msg;

    //! Holds the filename where the error occurred
    std::string m_filename;

    //! Holds the line number where the error occurred
    unsigned long m_line_number;
};

//===========================================================================//
/*!
 * \class DBCException
 * \brief Exception class thrown by all failed DBC checks
 */
//===========================================================================//

class DBCException : public Exception
{
    using Base = Exception;

  public:
    // Constructor
    DBCException(const std::string& test_string,
                 const std::string& test_type,
                 const std::string& filename,
                 unsigned long line_number);

    //! Return the test message
    const std::string& testString() const { return m_test_string; }

    //! Return the test type
    const std::string& testType() const { return m_test_type; }

  private:
    static std::string buildErrorMessage(const std::string& test_string,
                                         const std::string& test_type,
                                         const std::string& filename,
                                         unsigned long line_number);

    //! Holds the test that failed
    std::string m_test_string;

    //! Holds the type of test that failed
    std::string m_test_type;
};

//===========================================================================//
/*!
 * \class NotImplementedException
 * \brief Exception class thrown when a given code section is not implemented
 */
//===========================================================================//

class NotImplementedException : public Exception
{
    using Base = Exception;

  public:
    // Constructor
    NotImplementedException(const std::string& msg,
                            const std::string& filename,
                            unsigned long line_number);

    //! Retrieve the message
    const std::string& message() const { return m_msg; }

  private:
    // Construct the error message
    static std::string buildErrorMessage(const std::string& msg,
                                         const std::string& filename,
                                         unsigned long line_number);

    //! Holds the message
    std::string m_msg;
};

//===========================================================================//
/*!
 * \class NotReachableException
 * \brief Exception class thrown when an unreachable code point is reached
 */
//===========================================================================//

class NotReachableException : public Exception
{
    using Base = Exception;

  public:
    // Constructor
    NotReachableException(const std::string& filename,
                          unsigned long line_number);

  private:
    // Construct the error messageß
    static std::string
    buildErrorMessage(const std::string& filename, unsigned long line_number);
};

//---------------------------------------------------------------------------//
}  // namespace itertools

//---------------------------------------------------------------------------//
#endif  // ITERTOOLS_SRC_CORE_EXCEPTION_HH
//---------------------------------------------------------------------------//
// end of src/core/Exception.hh
//---------------------------------------------------------------------------//
