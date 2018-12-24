/** @file *//********************************************************************************************************

                                                    VertexBuffer.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/VertexBuffer.h#13 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>

namespace Dxx
{
//! @name	Vertex Buffer Functions
//! @ingroup	D3dx
//@{

//! Creates a static vertex buffer. Returns the result code.
HRESULT CreateStaticVertexBuffer(IDirect3DDevice9 * pDevice,
                                 void const * pData, size_t size, DWORD fvf,
                                 IDirect3DVertexBuffer9 ** ppVB,
                                 D3DPOOL pool = D3DPOOL_MANAGED);

//! Creates a static vertex buffer. Returns the result code.
HRESULT CreateStaticIndexBuffer(IDirect3DDevice9 * pDevice,
                                void const * pData, size_t size,
                                D3DFORMAT format,
                                IDirect3DIndexBuffer9 ** ppVB,
                                D3DPOOL pool = D3DPOOL_MANAGED);
//@}
} // namespace Dxx
