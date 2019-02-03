#pragma once

#if !defined(DXX_VERTEXBUFFER_H)
#define DXX_VERTEXBUFFER_H

#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>

namespace Dxx
{
//! @name	Vertex Buffer Functions
//! @ingroup	D3dx
//@{

//! Creates a static vertex buffer.
HRESULT CreateStaticVertexBuffer(ID3D11Device *  pDevice,
                                 void const *    pData,
                                 size_t          size,
                                 ID3D11Buffer ** ppVB);

//! Creates a static index buffer.
HRESULT CreateStaticIndexBuffer(ID3D11Device *        pDevice,
                                ID3D11DeviceContext * pContext,
                                void const *          pData,
                                size_t                size,
                                DXGI_FORMAT           format,
                                ID3D11Buffer **       ppIB);
//@}
} // namespace Dxx

#endif // !defined(DXX_VERTEXBUFFER_H)
