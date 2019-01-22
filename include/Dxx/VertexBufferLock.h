#pragma once

#if !defined(DXX_VERTEXBUFFERLOCK_H)
#define DXX_VERTEXBUFFERLOCK_H

#if 0
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d11.h>

#include "Misc/exceptions.h"

namespace Dxx
{
//! A class that locks a vertex buffer as long as it is in scope
//
//! @ingroup	D3dx
//!

class VertexBufferLock
{
public:
    //! Constructor
    //
    //! The constructor locks the vertex buffer (and adds a reference).
    //!
    //! @param	pVB			Vertex buffer to lock
    //! @param	offset		Where to start the lock (see ID3D11Buffer::Lock for more info)
    //! @param	size		Size (in bytes) to lock (see ID3D11Buffer::Lock for more info)
    //! @param	flags		Flags (see ID3D11Buffer::Lock for more info)
    //!
    //! @exception	ConstructorFailedException	The lock failed

    VertexBufferLock(ID3D11Buffer * pVB, UINT offset = 0, UINT size = 0, DWORD flags = 0)
        : pVB_(pVB)
    {
        pVB_->AddRef();

        HRESULT hr;
        hr = pVB_->Lock(offset, size, &pBuffer_, flags);
        if (FAILED(hr))
            throw ConstructorFailedException("VertexBufferLock failed");
    }

    //! Destructor
    //
    //! The destructor unlocks the vertex buffer (and releases it, also)
    //!

    ~VertexBufferLock()
    {
        HRESULT hr;

        hr = pVB_->Unlock();

        pVB_->Release();
    }

    // non-copyable
    VertexBufferLock(VertexBufferLock const &) = delete;
    VertexBufferLock & operator=(VertexBufferLock const &) = delete;

    //! Returns a pointer to the locked buffer data
    void * GetLockedBuffer()
    {
        return pBuffer_;
    }

private:

    ID3D11Buffer * const pVB_;
    void * pBuffer_;
};

//! A class that locks a index buffer as long as it is in scope
//
//! @ingroup	D3dx
//!

class IndexBufferLock
{
public:
    //! Constructor
    //
    //! The constructor locks the index buffer (and adds a reference).
    //!
    //! @param	pIB			Index buffer to lock
    //! @param	offset		Where to start the lock (see ID3D11Buffer::Lock for more info)
    //! @param	size		Size (in bytes) to lock (see ID3D11Buffer::Lock for more info)
    //! @param	flags		Flags (see ID3D11Buffer::Lock for more info)
    //!
    //! @exception	ConstructorFailedException	The lock failed

    IndexBufferLock(ID3D11Buffer * pIB, UINT offset = 0, UINT size = 0, DWORD flags = 0)
        : pIB_(pIB)
    {
        pIB_->AddRef();

        HRESULT hr;
        hr = pIB_->Lock(offset, size, &pBuffer_, flags);
        if (FAILED(hr))
            throw ConstructorFailedException("IndexBufferLock failed");
    }

    //! Destructor
    //
    //! The destructor unlocks the index buffer (and releases it, also)
    //!

    ~IndexBufferLock()
    {
        HRESULT hr;

        hr = pIB_->Unlock();

        pIB_->Release();
    }

    // non-copyable
    IndexBufferLock(IndexBufferLock const &) = delete;
    IndexBufferLock & operator=(IndexBufferLock const &) = delete;

    //! Returns a pointer to the locked buffer data
    void * GetLockedBuffer()
    {
        return pBuffer_;
    }

private:

    ID3D11Buffer * const pIB_;
    void * pBuffer_;
};
} // namespace Dxx
#endif

#endif // !defined(DXX_VERTEXBUFFERLOCK_H)
