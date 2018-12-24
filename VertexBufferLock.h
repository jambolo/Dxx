/** @file *//********************************************************************************************************

                                                  VertexBufferLock.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/VertexBufferLock.h#10 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>

#include "Misc/exceptions.h"
#include <boost/noncopyable.hpp>

namespace Dxx
{
//! A class that locks a vertex buffer as long as it is in scope
//
//! @ingroup	D3dx
//!

class VertexBufferLock : public boost::noncopyable
{
public:
    //! Constructor
    //
    //! The constructor locks the vertex buffer (and adds a reference).
    //!
    //! @param	pVB			Vertex buffer to lock
    //! @param	offset		Where to start the lock (see IDirect3DVertexBuffer9::Lock for more info)
    //! @param	size		Size (in bytes) to lock (see IDirect3DVertexBuffer9::Lock for more info)
    //! @param	flags		Flags (see IDirect3DVertexBuffer9::Lock for more info)
    //!
    //! @exception	ConstructorFailedException	The lock failed

    VertexBufferLock(IDirect3DVertexBuffer9 * pVB, UINT offset = 0, UINT size = 0, DWORD flags = 0)
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

    //! Returns a pointer to the locked buffer data
    void * GetLockedBuffer()
    {
        return pBuffer_;
    }

private:

    IDirect3DVertexBuffer9 * const pVB_;
    void * pBuffer_;
};

//! A class that locks a index buffer as long as it is in scope
//
//! @ingroup	D3dx
//!

class IndexBufferLock : public boost::noncopyable
{
public:
    //! Constructor
    //
    //! The constructor locks the index buffer (and adds a reference).
    //!
    //! @param	pIB			Index buffer to lock
    //! @param	offset		Where to start the lock (see IDirect3DIndexBuffer9::Lock for more info)
    //! @param	size		Size (in bytes) to lock (see IDirect3DIndexBuffer9::Lock for more info)
    //! @param	flags		Flags (see IDirect3DIndexBuffer9::Lock for more info)
    //!
    //! @exception	ConstructorFailedException	The lock failed

    IndexBufferLock(IDirect3DIndexBuffer9 * pIB, UINT offset = 0, UINT size = 0, DWORD flags = 0)
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

    //! Returns a pointer to the locked buffer data
    void * GetLockedBuffer()
    {
        return pBuffer_;
    }

private:

    IDirect3DIndexBuffer9 * const pIB_;
    void * pBuffer_;
};
} // namespace Dxx
