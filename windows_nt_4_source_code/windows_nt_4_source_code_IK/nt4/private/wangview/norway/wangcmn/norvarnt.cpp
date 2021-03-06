// norvarnt.cpp : implementation of the CVariantHandler class
//
// This class was written in order to standardize what VT_ value types
// (e.g., VT_I4, VT_BSTR, VT_R4) are valid for each possible 'C' data 
// type (e.g., long, short, string).

#include "stdafx.h"     // Gotta have it (precompile headers...)
#include <oleauto.h>    // Needed for VARIANT stuff...
#include "norvarnt.h"   // For this class...
#include "common.h"     // Publics for the Controls (for errors)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVariantHandler construction/destruction

_declspec (dllexport) CVariantHandler::CVariantHandler()
{
    // MUST use non-default constructor (or default constructor 
    // in conjunction with Setvariant(...) ), therefore 
    // Initialized is set to FALSE...
    m_Initialized = FALSE;
}

_declspec (dllexport) CVariantHandler::~CVariantHandler()
{
}

_declspec (dllexport) CVariantHandler::CVariantHandler(const VARIANT FAR& Variant)
{
    // Initialized is set to TRUE as the correct 
    // (i.e., non-default) constructor was used!!!
    m_Initialized = TRUE;

    // Copy the variant value in...
    m_Variant     = Variant;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetVariant(const VARIANT FAR& Variant)
//
//  Sets the Variant. 
//
// INPUT PARAMETERS:
//
//       VARIANT FAR& - reference to Variant data member to be accessed.
// 
// OUTPUT:
//
//      none
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) void CVariantHandler::SetVariant(const VARIANT FAR& Variant)
{
    // Initialized is set to TRUE as this function was called...
    m_Initialized = TRUE;

    // Copy the variant value in...
    m_Variant     = Variant;
}

///////////////////////////////////////////////////////////////////////////////
//
// long CVariantHandler::GetLong(      long &Value, 
//                               const long &Default,
//                               const BOOL  EmptyIsError)
//
//  Gets the long value of a Variant data item.
//
//  Currently allows values of type:
//                                      VT_I4
//                                      VT_I2
//
// INPUT PARAMETERS:
//
//       long &Value        - reference to long value to be returned
// 
//       long &Default      - reference to the Default value to be returned if 
//                            the EmptyIsError parameter is set to FALSE and the
//                            Variant is VT_EMPTY.
//  
//       BOOL  EmptyIsError - TRUE will cause a VT_EMPTY Variant to return a
//                            WI_INVALIDVARIANTTYPE error.
// 
//                            Note that this is the default such that a call
//                            of type GetLong(X) can simply be coded to allow
//                            no default case.
// 
//                            FALSE will cause a VT_Empty Variant to return
//                            the specified Default.
// 
//                            Note that as EmptyIsDefault is the last parameter
//                            in order to specify a value of FALSE a value for 
//                            the Default parameter MUST be specified.  
// 
// OUTPUT:
//
//      0                      - success.
//      WI_INVALIDVARIANTTYPE  - Invalid Variant Type.
//      WI_INVALIDEMPTYVARIANT - Invalid EMPTY variant
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) long CVariantHandler::GetLong(      long &Value, 
                                                    const long &Default,
                                                    const BOOL  EmptyIsError /* = TRUE */)
{
    // MUST use the non-default constructor...
    ASSERT(m_Initialized == TRUE);

    // Assume success...
    long RetVal = 0;

    // Get the Variant's type (once for efficiency!)
    VARTYPE Type = m_Variant.vt;

    // Get the value from the Variant...
    if ( Type == VT_ERROR )
    {
        // See if Empty is to be treated as an error or as 'use default'...
        if ( EmptyIsError )
            RetVal = WI_INVALIDEMPTYVARIANT;
        else
            Value = Default;
    }
    else if ( Type == VT_I4 )           //
        Value = m_Variant.lVal;         // Longs accept I4
    else if ( Type == VT_I2 )           //
        Value = m_Variant.iVal;         //          and I2
    else                                //
        RetVal = WI_INVALIDVARIANTTYPE; // Anything else is an error...

    return RetVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// long CVariantHandler::GetShort(     short &Value, 
//                               const short &Default,
//                               const BOOL   EmptyIsError)
//
//  Gets the short value of a Variant data item.
//
//  Currently allows values of type:
//                                      VT_I2
//
// INPUT PARAMETERS:
//
//       short &Value       - reference to short value to be returned
// 
//       short &Default     - reference to the Default value to be returned if 
//                            the EmptyIsError parameter is set to FALSE and the
//                            Variant is VT_EMPTY.
//  
//       BOOL  EmptyIsError - TRUE will cause a VT_EMPTY Variant to return a
//                            WI_INVALIDVARIANTTYPE error.
// 
//                            Note that this is the default such that a call
//                            of type GetLong(X) can simply be coded to allow
//                            no default case.
// 
//                            FALSE will cause a VT_Empty Variant to return
//                            the specified Default.
// 
//                            Note that as EmptyIsDefault is the last parameter
//                            in order to specify a value of FALSE a value for 
//                            the Default parameter MUST be specified.  
//
// OUTPUT:
//
//      0                      - success.
//      WI_INVALIDVARIANTTYPE  - Invalid Variant Type.
//      WI_INVALIDEMPTYVARIANT - Invalid EMPTY variant
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) long CVariantHandler::GetShort(      short &Value, 
                                                     const short &Default,
                                                     const BOOL   EmptyIsError /* = TRUE */)
{
    // MUST use the non-default constructor...
    ASSERT(m_Initialized == TRUE);

    // Assume success...
    long RetVal = 0;

    // Get the Variant's type (once for efficiency!)
    VARTYPE Type = m_Variant.vt;

    // Get the value from the Variant...
    if ( Type == VT_ERROR )
    {
        // See if Empty is to be treated as an error or as 'use default'...
        if ( EmptyIsError )
            RetVal = WI_INVALIDEMPTYVARIANT;
        else
            Value = Default;
    }
    else if ( Type == VT_I2 )           //
        Value = m_Variant.iVal;         // Shorts accept I2
    else                                //
        RetVal = WI_INVALIDVARIANTTYPE; // Anything else is an error...

    return RetVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// long CVariantHandler::GetCString(     CString &Value, 
//                                 const CString &Default,
//                                 const BOOL     EmptyIsError)
//
//  Gets the CString value of a Variant data item.
//
//  Currently allows values of type:
//                                      VT_BSTR
//
// INPUT PARAMETERS:
//
//       CString &Value     - reference to CString value to be returned
// 
//       CString &Default   - The Default value to be returned if the
//                            EmptyIsError parameter is set to FALSE and the
//                            Variant is VT_EMPTY.
//  
//       BOOL  EmptyIsError - TRUE will cause a VT_EMPTY Variant to return a
//                            WI_INVALIDVARIANTTYPE error.
// 
//                            Note that this is the default such that a call
//                            of type GetLong(X) can simply be coded to allow
//                            no default case.
// 
//                            FALSE will cause a VT_Empty Variant to return
//                            the specified Default.
// 
//                            Note that as EmptyIsDefault is the last parameter
//                            in order to specify a value of FALSE a value for 
//                            the Default parameter MUST be specified.  
//
// OUTPUT:
//
//      0                      - success.
//      WI_INVALIDVARIANTTYPE  - Invalid Variant Type.
//      WI_INVALIDEMPTYVARIANT - Invalid EMPTY variant
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) long CVariantHandler::GetCString(      CString &Value, 
                                                       const CString &Default,    
                                                       const BOOL     EmptyIsError /* = TRUE */)
{
    // MUST use the non-default constructor...
    ASSERT(m_Initialized == TRUE);

    // Assume success...
    long RetVal = 0;

    // Get the Variant's type (once for efficiency!)
    VARTYPE Type = m_Variant.vt;

    // Get the value from the Variant...
    if ( Type == VT_ERROR )
    {
        // See if Empty is to be treated as an error or as 'use default'...
        if ( EmptyIsError )
            RetVal = WI_INVALIDEMPTYVARIANT;
        else
            Value = Default;
    }
    else if ( Type == VT_BSTR )         //
        Value = m_Variant.bstrVal;      // CString accept BSTR
    else                                //
        RetVal = WI_INVALIDVARIANTTYPE; // Anything else is an error...

    return RetVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// long CVariantHandler::GetBool(      BOOL &Value, 
//                               const BOOL &Default,
//                               const BOOL  EmptyIsError)
//
//  Gets the boolean value of a Variant data item.
//
//  Currently allows values of type:
//                                      VT_BOOL
//
// INPUT PARAMETERS:
//
//       BOOL  &Value       - reference to boolean value to be returned
// 
//       BOOL &Default      - reference to the Default value to be returned if 
//                            the EmptyIsError parameter is set to FALSE and the
//                            Variant is VT_EMPTY.
//  
//       BOOL  EmptyIsError - TRUE will cause a VT_EMPTY Variant to return a
//                            WI_INVALIDVARIANTTYPE error.
// 
//                            Note that this is the default such that a call
//                            of type GetLong(X) can simply be coded to allow
//                            no default case.
// 
//                            FALSE will cause a VT_Empty Variant to return
//                            the specified Default.
// 
//                            Note that as EmptyIsDefault is the last parameter
//                            in order to specify a value of FALSE a value for 
//                            the Default parameter MUST be specified.  
//
// OUTPUT:
//
//      0                      - success.
//      WI_INVALIDVARIANTTYPE  - Invalid Variant Type.
//      WI_INVALIDEMPTYVARIANT - Invalid EMPTY variant
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) long CVariantHandler::GetBool(       BOOL &Value, 
                                                     const BOOL &Default,
                                                     const BOOL  EmptyIsError /* = TRUE */)
{
    // MUST use the non-default constructor...
    ASSERT(m_Initialized == TRUE);

    // Assume success...
    long RetVal = 0;

    // Get the Variant's type (once for efficiency!)
    VARTYPE Type = m_Variant.vt;

    // Get the value from the Variant...
    if ( Type == VT_ERROR )
    {
        // See if Empty is to be treated as an error or as 'use default'...
        if ( EmptyIsError )
            RetVal = WI_INVALIDEMPTYVARIANT;
        else
            Value = Default;
    }
    else if ( Type == VT_BOOL )         //
        Value = m_Variant.bVal;         // Shorts accept booleans
    else                                //
        RetVal = WI_INVALIDVARIANTTYPE; // Anything else is an error...

    return RetVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// long CVariantHandler::GetFloat(      float &Value, 
//                                const float &Default,
//                                const BOOL   EmptyIsError)
//
//  Gets the float (4 byte real) value of a Variant data item.
//
//  Currently allows values of type:
//                                      VT_R4
//                                      VT_I2
//                                      VT_I4
//
// INPUT PARAMETERS:
//
//       float &Value       - reference to boolean value to be returned
// 
//       float &Default     - reference to the Default value to be returned if 
//                            the EmptyIsError parameter is set to FALSE and the
//                            Variant is VT_EMPTY.
//  
//       BOOL  EmptyIsError - TRUE will cause a VT_EMPTY Variant to return a
//                            WI_INVALIDVARIANTTYPE error.
// 
//                            Note that this is the default such that a call
//                            of type GetLong(X) can simply be coded to allow
//                            no default case.
// 
//                            FALSE will cause a VT_Empty Variant to return
//                            the specified Default.
// 
//                            Note that as EmptyIsDefault is the last parameter
//                            in order to specify a value of FALSE a value for 
//                            the Default parameter MUST be specified.  
//
// OUTPUT:
//
//      0                      - success.
//      WI_INVALIDVARIANTTYPE  - Invalid Variant Type.
//      WI_INVALIDEMPTYVARIANT - Invalid EMPTY variant
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) long CVariantHandler::GetFloat(      float &Value, 
                                                     const float &Default,
                                                     const BOOL   EmptyIsError /* = TRUE */)
{
    // MUST use the non-default constructor...
    ASSERT(m_Initialized == TRUE);

    // Assume success...
    long RetVal = 0;

    // Get the Variant's type (once for efficiency!)
    VARTYPE Type = m_Variant.vt;

    // Get the value from the Variant...
    if ( Type == VT_ERROR )
    {
        // See if Empty is to be treated as an error or as 'use default'...
        if ( EmptyIsError )
            RetVal = WI_INVALIDEMPTYVARIANT;
        else
            Value = Default;
    }
    else if ( Type == VT_R4 )           //
        Value = m_Variant.fltVal;       // Floats accept R4
    else if ( Type == VT_I2 )           //
        Value = (float)m_Variant.iVal;  //               I2
    else if ( Type == VT_I4 )           //
        Value = (float)m_Variant.lVal;  //               I4
    else                                //
        RetVal = WI_INVALIDVARIANTTYPE; // Anything else is an error...

    return RetVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// long CVariantHandler::GetDouble(      double &Value, 
//                                 const double &Default,
//                                 const BOOL   EmptyIsError)
//
//  Gets the double (8 byte real) value of a Variant data item.
//
//  Currently allows values of type:
//                                      VT_R8
//                                      VT_R4
//                                      VT_I2
//                                      VT_I4
//
// INPUT PARAMETERS:
//
//       double &Value      - reference to boolean value to be returned
// 
//       double &Default    - reference to the Default value to be returned if 
//                            the EmptyIsError parameter is set to FALSE and the
//                            Variant is VT_EMPTY.
//  
//       BOOL  EmptyIsError - TRUE will cause a VT_EMPTY Variant to return a
//                            WI_INVALIDVARIANTTYPE error.
// 
//                            Note that this is the default such that a call
//                            of type GetLong(X) can simply be coded to allow
//                            no default case.
// 
//                            FALSE will cause a VT_Empty Variant to return
//                            the specified Default.
// 
//                            Note that as EmptyIsDefault is the last parameter
//                            in order to specify a value of FALSE a value for 
//                            the Default parameter MUST be specified.  
//
// OUTPUT:
//
//      0                      - success.
//      WI_INVALIDVARIANTTYPE  - Invalid Variant Type.
//      WI_INVALIDEMPTYVARIANT - Invalid EMPTY variant
//      
///////////////////////////////////////////////////////////////////////////////
_declspec (dllexport) long CVariantHandler::GetDouble(      double &Value, 
                                                      const double &Default,
                                                      const BOOL   EmptyIsError /* = TRUE */)
{
    // MUST use the non-default constructor...
    ASSERT(m_Initialized == TRUE);

    // Assume success...
    long RetVal = 0;

    // Get the Variant's type (once for efficiency!)
    VARTYPE Type = m_Variant.vt;

    // Get the value from the Variant...
    if ( Type == VT_ERROR )
    {
        // See if Empty is to be treated as an error or as 'use default'...
        if ( EmptyIsError )
            RetVal = WI_INVALIDEMPTYVARIANT;
        else
            Value = Default;
    }
    else if ( Type == VT_R8 )             //
        Value = m_Variant.dblVal;         // Doubles accept R8
    else if ( Type == VT_R4 )             //
        Value = (double)m_Variant.fltVal; //               R4
    else if ( Type == VT_I2 )             //
        Value = (double)m_Variant.iVal;   //               I2
    else if ( Type == VT_I4 )             //
        Value = (double)m_Variant.lVal;   //               I4
    else                                  //
        RetVal = WI_INVALIDVARIANTTYPE;   // Anything else is an error...

    return RetVal;
}
