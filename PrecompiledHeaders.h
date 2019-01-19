/*********************************************************************************************************************

                                                 PrecompiledHeaders.h

                                            Copyright 2002, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/PrecompiledHeaders.h#14 $

    $NoKeywords: $

*********************************************************************************************************************/

/* Warnings to be ignored																							*/

#pragma warning( disable: 4127 )    // conditional expression is constant
#pragma warning( disable: 4201 )    // nonstandard extension used : nameless struct/union
#pragma warning( disable: 4512 )    // 'class' : assignment operator could not be generated

/* Windows header files																								*/

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <atlbase.h>
#include <atlcomcli.h>
#include <msxml2.h>
#include <ole2.h>
#include <windows.h>

/* Direct X header files																							*/

#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3d9types.h>
#include <d3dx9.h>
#include <DirectXMath.h>
#include <dxerr9.h>

/* Standard Library header files																					*/

#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>
#include <sstream>
#include <vector>

/* Library header files																								*/

#include <boost/noncopyable.hpp>
#include <Math/Constants.h>
#include <Math/FastMath.h>
#include <Math/Frustum.h>
#include <Math/Math.h>
#include <Misc/Assert.h>
#include <Misc/exceptions.h>
#include <Misc/Etc.h>
#include <Misc/Random.h>
#include <Misc/Types.h>
#include <Wx/Wx.h>

/* Project header files																								*/
