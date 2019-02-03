#include "VertexBuffer.h"

#include <cassert>

namespace Dxx
{
//! @param    pDevice        Device the vertex buffer is to be associated with.
//! @param    pData        Data to copy to the new vertex buffer.
//! @param    size        Number of bytes to copy.
//! @param    ppVB        Where to store the pointer to the new vertex buffer.
//!
//! @note    Release() must be called to release the buffer if it was successfully created

HRESULT CreateStaticVertexBuffer(ID3D11Device *  pDevice,
                                 void const *    pData,
                                 size_t          size,
                                 ID3D11Buffer ** ppVB)
{
    assert(pData);
    assert(size > 0);
    assert(ppVB);

    D3D11_BUFFER_DESC desc =
    {
        (UINT)size,                 // UINT        ByteWidth;
        D3D11_USAGE_DEFAULT,        // D3D11_USAGE Usage;
        D3D11_BIND_VERTEX_BUFFER,   // UINT        BindFlags;
        0,                          // UINT        CPUAccessFlags;
        0,                          // UINT        MiscFlags;
        0                           // UINT        StructureByteStride;
    };

    D3D11_SUBRESOURCE_DATA data =
    {
        pData,  // const void *pSysMem;
        0,      // UINT       SysMemPitch;
        0       // UINT       SysMemSlicePitch;
    };

    HRESULT hr = pDevice->CreateBuffer(&desc, &data, ppVB);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

//! @param    pDevice   Device the index buffer is to be associated with.
//! @param    pContext  Context the index buffer is to be associated with.
//! @param    pData     Data to copy to the new index buffer.
//! @param    size      Number of bytes to copy.
//! @param    format    Index value format DXGI_FORMAT_R16_UINT or DXGI_FORMAT_R32_UINT.
//! @param    ppIB      Where to store the pointer to the new index buffer.
//!
//! @note    Release() must be called to release the buffer if it was successfully created

HRESULT CreateStaticIndexBuffer(ID3D11Device *        pDevice,
                                ID3D11DeviceContext * pContext,
                                void const *          pData,
                                size_t                size,
                                DXGI_FORMAT           format,
                                ID3D11Buffer **       ppIB)
{
    assert(pData);
    assert(size > 0);
    assert(format == DXGI_FORMAT_R16_UINT || format == DXGI_FORMAT_R32_UINT);
    assert(ppIB);

    D3D11_BUFFER_DESC desc =
    {
        (UINT)size,                 // UINT        ByteWidth;
        D3D11_USAGE_DEFAULT,        // D3D11_USAGE Usage;
        D3D11_BIND_INDEX_BUFFER,    // UINT        BindFlags;
        0,                          // UINT        CPUAccessFlags;
        0,                          // UINT        MiscFlags;
        0                           // UINT        StructureByteStride;
    };

    D3D11_SUBRESOURCE_DATA data =
    {
        pData,  // const void *pSysMem;
        0,      // UINT       SysMemPitch;
        0       // UINT       SysMemSlicePitch;
    };

    HRESULT hr = pDevice->CreateBuffer(&desc, &data, ppIB);
    if (FAILED(hr))
        return hr;

    // Set the buffer.
    pContext->IASetIndexBuffer(*ppIB, format, 0);

    return S_OK;
}
} // namespace Dxx
