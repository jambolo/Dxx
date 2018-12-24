/** @file *//********************************************************************************************************

                                                   VertexBuffer.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/VertexBuffer.cpp#12 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "VertexBuffer.h"
#include "VertexBufferLock.h"

namespace Dxx
{
//! @param	pDevice		Device the vertex buffer is to be associated with.
//! @param	pData		Data to copy to the new vertex buffer.
//! @param	size		Number of bytes to copy.
//! @param	fvf			FVF flags (see the docs for D3DFVF).
//! @param	ppVB		Where to store the pointer to the new vertex buffer.
//! @param	pool		Memory pool (see the docs for D3DPOOL).
//!
//! @note	Release() must be called to release the buffer if it was successfully created

HRESULT CreateStaticVertexBuffer(IDirect3DDevice9 * pDevice,
                                 void const * pData, UINT size,
                                 DWORD fvf, IDirect3DVertexBuffer9 ** ppVB,
                                 D3DPOOL pool /* = D3DPOOL_MANAGED*/)
{
    assert(pData != 0);
    assert(size > 0);
    assert(ppVB != 0);

    IDirect3DVertexBuffer9 * pVB;
    HRESULT hr;

    // Create the vertex buffer

    hr = pDevice->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, fvf, pool, &pVB, NULL);
    if (FAILED(hr))
        return hr;

    // Copy the vertex data to the vertex buffer

    try
    {
        VertexBufferLock lock(pVB, 0, 0, 0);

        memcpy(lock.GetLockedBuffer(), pData, size);
    }
    catch (...)
    {
        pVB->Release();
        return S_FALSE;
    }

    // Return the address of the vertex buffer

    *ppVB = pVB;

    return D3D_OK;
}

//! @param	pDevice		Device the vertex buffer is to be associated with.
//! @param	pData		Data to copy to the new vertex buffer.
//! @param	size		Number of bytes to copy.
//! @param	format		Index value format (See the docs for CreateIndexBuffer for valid values).
//! @param	ppIB		Where to store the pointer to the new vertex buffer.
//! @param	pool		Memory pool (See the docs for D3DPOOL for valid values).
//!
//! @note	Release() must be called to release the buffer if it was successfully created

HRESULT CreateStaticIndexBuffer(IDirect3DDevice9 * pDevice,
                                void const * pData, UINT size,
                                D3DFORMAT format,
                                IDirect3DIndexBuffer9 ** ppIB,
                                D3DPOOL pool /* = D3DPOOL_MANAGED*/)
{
    assert(pData != 0);
    assert(size > 0);
    assert(ppIB != 0);

    IDirect3DIndexBuffer9 * pIB;
    HRESULT hr;

    // Create the index buffer

    hr = pDevice->CreateIndexBuffer(size, D3DUSAGE_WRITEONLY, format, pool, &pIB, NULL);
    if (FAILED(hr))
        return hr;

    // Copy the index data to the index buffer

    try
    {
        IndexBufferLock lock(pIB, 0, 0, 0);

        memcpy(lock.GetLockedBuffer(), pData, size);
    }
    catch (...)
    {
        pIB->Release();
        return S_FALSE;
    }

    // Return the address of the index buffer

    *ppIB = pIB;

    return D3D_OK;
}
} // namespace Dxx
