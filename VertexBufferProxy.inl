/** @file *//********************************************************************************************************

                                                 VertexBufferProxy.inl

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/VertexBufferProxy.inl#6 $

    $NoKeywords: $

 *********************************************************************************************************************/

#pragma once

#include "VertexBufferProxy.h"

namespace Dxx
{
/*										V E R T E X B U F F E R P R O X Y											*/

inline VertexBufferProxy::~VertexBufferProxy()
{
    // If the buffer is locked, it must be unlocked first (I assume)
    if (pData_ != 0)
        Unlock();
    pBuffer_->Release();
}

inline IDirect3DVertexBuffer9 * VertexBufferProxy::GetVertexBuffer() const
{
    return pBuffer_;
}

//! @param	OffsetToLock	Offset to start of locked region
//! @param	SizeToLock		Number of bytes to lock
//! @param	Flags			Flags (see docs for D3DLOCK)

inline HRESULT VertexBufferProxy::Lock(UINT OffsetToLock, UINT SizeToLock, DWORD Flags)
{
    lockOffset_ = OffsetToLock;
    return pBuffer_->Lock(OffsetToLock, SizeToLock, (void **)&pData_, Flags);
}

inline HRESULT VertexBufferProxy::Unlock()
{
    pData_      = 0;
    lockOffset_ = 0;
    return pBuffer_->Unlock();
}

//!
//! @param	i	Index of vertex to point to (relative to locked region)

inline void * VertexBufferProxy::GetVertex(int i) const
{
    return (void *)((char *)pData_ + (stride_ * i - lockOffset_));
}

//!
//! @param	i	Index of vertex to get (relative to locked region)

inline VertexBufferProxy::VRef VertexBufferProxy::operator [](int i) const
{
    return VRef(this, GetVertex(i));
}

/*												V R E F B A S E														*/

inline VertexBufferProxy::VRefBase::VRefBase(VertexBufferProxy const * pProxy, void * pVertex)
    : pProxy_(pProxy), pVertex_(pVertex)
{
}

inline D3DXVECTOR3 & VertexBufferProxy::VRefBase::Position() const
{
    return *(D3DXVECTOR3 *)((char *)pVertex_ + 0);
}

inline float & VertexBufferProxy::VRefBase::W() const
{
    return *(float *)((char *)pVertex_ + pProxy_->wOffset_);
}

inline float & VertexBufferProxy::VRefBase::Blend0() const
{
    return *(float *)((char *)pVertex_ + pProxy_->blend0Offset_);
}

inline float & VertexBufferProxy::VRefBase::Blend1() const
{
    return *(float *)((char *)pVertex_ + pProxy_->blend1Offset_);
}

inline float & VertexBufferProxy::VRefBase::Blend2() const
{
    return *(float *)((char *)pVertex_ + pProxy_->blend2Offset_);
}

inline float & VertexBufferProxy::VRefBase::Blend3() const
{
    return *(float *)((char *)pVertex_ + pProxy_->blend3Offset_);
}

inline DWORD & VertexBufferProxy::VRefBase::BlendIndexes() const
{
    return *(DWORD *)((char *)pVertex_ + pProxy_->blendIndexesOffset_);
}

inline D3DXVECTOR3 & VertexBufferProxy::VRefBase::Normal() const
{
    return *(D3DXVECTOR3 *)((char *)pVertex_ + pProxy_->normalOffset_);
}

inline float & VertexBufferProxy::VRefBase::PointSize() const
{
    return *(float *)((char *)pVertex_ + pProxy_->pointSizeOffset_);
}

inline DWORD & VertexBufferProxy::VRefBase::Diffuse() const
{
    return *(DWORD *)((char *)pVertex_ + pProxy_->diffuseOffset_);
}

inline DWORD & VertexBufferProxy::VRefBase::Specular() const
{
    return *(DWORD *)((char *)pVertex_ + pProxy_->specularOffset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord0() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord0Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord1() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord1Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord2() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord2Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord3() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord3Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord4() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord4Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord5() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord5Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord6() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord6Offset_);
}

inline float * VertexBufferProxy::VRefBase::TexCoord7() const
{
    return (float *)((char *)pVertex_ + pProxy_->texCoord7Offset_);
}

/*													V P T R															*/

//! @param	pProxy		VertexBufferProxy this is associated with
//! @param	pVertex		Vertex this refers to

inline VertexBufferProxy::VPtr::VPtr(VertexBufferProxy const * pProxy, void * pVertex)
    : VRefBase(pProxy, pVertex)
{
}

inline VertexBufferProxy::VRef VertexBufferProxy::VPtr::operator *() const
{
    return VertexBufferProxy::VRef(pProxy_, pVertex_);
}

//!
//! @param	i	index relative to this vertex

inline VertexBufferProxy::VRef VertexBufferProxy::VPtr::operator [](int i) const
{
    return *(*this + i);
}

inline VertexBufferProxy::VRefBase const * VertexBufferProxy::VPtr::operator ->() const
{
    return this;
}

inline VertexBufferProxy::VRefBase * VertexBufferProxy::VPtr::operator ->()
{
    return this;
}

inline VertexBufferProxy::VPtr & VertexBufferProxy::VPtr::operator ++()
{
    pVertex_ = (char *)pVertex_ + pProxy_->stride_;
    return *this;
}

inline VertexBufferProxy::VPtr VertexBufferProxy::VPtr::operator ++(int)
{
    VPtr v(*this);
    pVertex_ = (char *)pVertex_ + pProxy_->stride_;
    return v;
}

inline VertexBufferProxy::VPtr & VertexBufferProxy::VPtr::operator --()
{
    pVertex_ = (char *)pVertex_ - pProxy_->stride_;
    return *this;
}

inline VertexBufferProxy::VPtr VertexBufferProxy::VPtr::operator --(int)
{
    VPtr v(*this);
    pVertex_ = (char *)pVertex_ - pProxy_->stride_;
    return v;
}

//!
//! @param	i	Value to add

inline VertexBufferProxy::VPtr & VertexBufferProxy::VPtr::operator +=(int i)
{
    pVertex_ = (char *)pVertex_ + (i * pProxy_->stride_);
    return *this;
}

//!
//! @param	i	Value to subtract

inline VertexBufferProxy::VPtr & VertexBufferProxy::VPtr::operator -=(int i)
{
    pVertex_ = (char *)pVertex_ - (i * pProxy_->stride_);
    return *this;
}

inline VertexBufferProxy::VPtr::operator void *() const
{
    return pVertex_;
}
} // namespace Dxx

//! @param	vptr	Operand
//! @param	i		Operand

inline Dxx::VertexBufferProxy::VPtr operator +(Dxx::VertexBufferProxy::VPtr const & vptr, int i)
{
    return Dxx::VertexBufferProxy::VPtr(vptr) += i;
}

//! @param	vptr	Operand
//! @param	i		Operand

inline Dxx::VertexBufferProxy::VPtr operator -(Dxx::VertexBufferProxy::VPtr const & vptr, int i)
{
    return Dxx::VertexBufferProxy::VPtr(vptr) -= i;
}

//! @param	i		Operand
//! @param	vptr	Operand

inline Dxx::VertexBufferProxy::VPtr operator +(int i, Dxx::VertexBufferProxy::VPtr const & vptr)
{
    return operator +(vptr, i);
}

/*													V R E F															*/

namespace Dxx
{
//! @param	pProxy		VertexBufferProxy this is associated with
//! @param	pVertex		Vertex this refers to

inline VertexBufferProxy::VRef::VRef(VertexBufferProxy const * pProxy, void * pVertex)
    : VRefBase(pProxy, pVertex)

{
}

inline VertexBufferProxy::VPtr VertexBufferProxy::VRef::operator &()
{
    return VPtr(pProxy_, pVertex_);
}
} // namespace Dxx
