#pragma once

#if !defined(DXX_VERTEXBUFFER_H)
#define DXX_VERTEXBUFFER_H

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d11.h>
#include <dxgi.h>

namespace Dxx
{
//! @name	Vertex Buffer Functions
//! @ingroup	D3dx
//@{

//! Creates a static vertex buffer. Returns the result code.
HRESULT CreateStaticVertexBuffer(ID3D11Device * pDevice,
                                 void const * pData, size_t size,
                                 DWORD fvf,
                                 ID3D11Buffer ** ppVB/*,
                                                        D3DPOOL pool = D3DPOOL_MANAGED*/);

//! Creates a static vertex buffer. Returns the result code.
HRESULT CreateStaticIndexBuffer(ID3D11Device * pDevice,
                                void const * pData, size_t size,
                                DXGI_FORMAT format,
                                ID3D11Buffer ** ppVB/*,
                                                       D3DPOOL pool = D3DPOOL_MANAGED*/);
//@}
} // namespace Dxx

#endif // !defined(DXX_VERTEXBUFFER_H)
