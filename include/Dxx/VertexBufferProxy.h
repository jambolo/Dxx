#pragma once

#if !defined(DXX_VERTEXBUFFERPROXY_H)
#define DXX_VERTEXBUFFERPROXY_H

#if 0
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d11.h>

namespace Dxx
{
//! @defgroup	VertexBufferProxy	VertexBufferProxy Classes
//! Classes associated with VertexBufferProxy
//! @ingroup	D3dx

//! A class that gives structured access to vertices in a vertex buffer.
//
//! @ingroup VertexBufferProxy
//!

class VertexBufferProxy
{
    friend class VRefBase;

public:

    class VRefBase; // Declared below
    class VRef;     // Declared below
    class VPtr;     // Declared below

    //! Constructor
    VertexBufferProxy(ID3DXMesh * pMesh);

    //! Constructor
    VertexBufferProxy(ID3D11Buffer * pBuffer);

    //! Destructor
    ~VertexBufferProxy();

    //! Returns the vertex buffer
    ID3D11Buffer * GetVertexBuffer() const;

    //! Locks the buffer
    HRESULT Lock(UINT OffsetToLock, UINT SizeToLock, DWORD Flags);

    //! Unlocks the buffer
    HRESULT Unlock();

    //! Returns a pointer to a vertex (in the form of a VPtr).
    void * GetVertex(int i) const;

    //! Returns a reference to a vertex (in the form of a VRef).
    VRef operator [](int i) const;

private:

    //! Initializes the offset values
    void InitializeOffsets();

    ID3D11Buffer * pBuffer_;    //!< The vertex buffer.
    D3DVERTEXBUFFER_DESC desc_; //!< The "Desc" data for the buffer.
    void * pData_;              //!< Pointer to vertex buffer data (valid only while locked)
    int lockOffset_;            //!< Offset to beginning of the locked data
    int wOffset_;               //!< Offset to the W value.
    int blend0Offset_;          //!< Offset to the 1st blending weight value.
    int blend1Offset_;          //!< Offset to the 2nd blending weight value.
    int blend2Offset_;          //!< Offset to the 3rd blending weight value.
    int blend3Offset_;          //!< Offset to the 4th blending weight value.
    int blendIndexesOffset_;    //!< Offset to the blending weight indexes.
    int normalOffset_;          //!< Offset to the normal value.
    int pointSizeOffset_;       //!< Offset to the point size value.
    int diffuseOffset_;         //!< Offset to the diffuse color value.
    int specularOffset_;        //!< Offset to the specular value.
    int texCoord0Offset_;       //!< Offset to the 1st set of texture coordinates.
    int texCoord1Offset_;       //!< Offset to the 2nd set of texture coordinates.
    int texCoord2Offset_;       //!< Offset to the 3rd set of texture coordinates.
    int texCoord3Offset_;       //!< Offset to the 4th set of texture coordinates.
    int texCoord4Offset_;       //!< Offset to the 5th set of texture coordinates.
    int texCoord5Offset_;       //!< Offset to the 6th set of texture coordinates.
    int texCoord6Offset_;       //!< Offset to the 7th set of texture coordinates.
    int texCoord7Offset_;       //!< Offset to the 8th set of texture coordinates.
    int stride_;                //!< Size of a vertex in bytes.
};

//! A class that refers to a vertex in a vertex buffer. For use by VRef and VPtr.
//
//! @ingroup VertexBufferProxy
//!
//! This class is common to both VRef and VPtr and is used to enable access to vertex values through both pointer
//! and reference interfaces.

class VertexBufferProxy::VRefBase
{
public:

    //! Constructor
    VRefBase(VertexBufferProxy const * pProxy, void * pVertex);

    //! Returns a reference to the position value.
    DirectX::XMFLOAT4 & Position() const;

    //! Returns a reference to the W value.
    float & W() const;

    //! Returns a reference to the 1st blending weight value.
    float & Blend0() const;

    //! Returns a reference to the 2nd blending weight value.
    float & Blend1() const;

    //! Returns a reference to the 3rd blending weight value.
    float & Blend2() const;

    //! Returns a reference to the 4th blending weight value.
    float & Blend3() const;

    //! Returns a reference to the blending weight indexes.
    DWORD & BlendIndexes() const;

    //! Returns a reference to the normal value.
    DirectX::XMFLOAT4 & Normal() const;

    //! Returns a reference to the point size value.
    float & PointSize() const;

    //! Returns a reference to the diffuse color value.
    DWORD & Diffuse() const;

    //! Returns a reference to the specular value.
    DWORD & Specular() const;

    //! Returns a pointer to the 1st set of texture coordinates.
    float * TexCoord0() const;

    //! Returns a pointer to the 2nd set of texture coordinates.
    float * TexCoord1() const;

    //! Returns a pointer to the 3rd set of texture coordinates.
    float * TexCoord2() const;

    //! Returns a pointer to the 4th set of texture coordinates.
    float * TexCoord3() const;

    //! Returns a pointer to the 5th set of texture coordinates.
    float * TexCoord4() const;

    //! Returns a pointer to the 6th set of texture coordinates.
    float * TexCoord5() const;

    //! Returns a pointer to the 7th set of texture coordinates.
    float * TexCoord6() const;

    //! Returns a pointer to the 8th set of texture coordinates.
    float * TexCoord7() const;

protected:

    VertexBufferProxy const * pProxy_;      //!< Which vertex buffer proxy this vertex belongs to.
    void * pVertex_;                        //!< Start of this vertex's data.
};

//! A class that acts as a pointer to a vertex in a vertex buffer
//
//! @ingroup VertexBufferProxy
//!

class VertexBufferProxy::VPtr : private VertexBufferProxy::VRefBase
{
public:

    //! Constructor
    VPtr(VertexBufferProxy const * pProxy, void * pVertex);

    //! @name Overloaded Operators
    //@{

    //! Dereference
    VertexBufferProxy::VRef operator *() const;

    //! Subscript
    VertexBufferProxy::VRef operator [](int i) const;

    //! Member selection by reference
    VertexBufferProxy::VRefBase const * operator ->() const;

    //! Member selection by reference
    VertexBufferProxy::VRefBase * operator ->();

    //! Pre-increment
    VPtr & operator ++();

    //! Post-increment
    VPtr operator ++(int);

    //! Pre-decrement
    VPtr & operator --();

    //! Post-decrement
    VPtr operator --(int);

    //! Addition assignment
    VPtr & operator +=(int i);

    //! Subtraction assignment
    VPtr & operator -=(int i);

    //! Converion to void *
    operator void *() const;

    //@}

    //! @name Overrides VRefBase
    //@{
    //	DirectX::XMFLOAT4 & Position() const;
    //	float & W() const;
    //	float & Blend0() const;
    //	float & Blend1() const;
    //	float & Blend2() const;
    //	float & Blend3() const;
    //	float & BlendIndexes() const;
    //	DirectX::XMFLOAT4 & Normal() const;
    //	float & PointSize() const;
    //	DWORD & Diffuse() const;
    //	DWORD & Specular() const;
    //	float * TexCoord0() const;
    //	float * TexCoord1() const;
    //	float * TexCoord2() const;
    //	float * TexCoord3() const;
    //	float * TexCoord4() const;
    //	float * TexCoord5() const;
    //	float * TexCoord6() const;
    //	float * TexCoord7() const;
    //@}
};
} // namespace Dxx

//! @name Binary Operators for VertexBufferProxy::VPtr
//! @ingroup VertexBufferProxy
//@{

//! Vptr addition operator
Dxx::VertexBufferProxy::VPtr operator +(Dxx::VertexBufferProxy::VPtr const & vptr, int i);

//! Vptr subtraction operator
Dxx::VertexBufferProxy::VPtr operator -(Dxx::VertexBufferProxy::VPtr const & vptr, int i);

//! Vptr addition operator
Dxx::VertexBufferProxy::VPtr operator +(int i, Dxx::VertexBufferProxy::VPtr const & vptr);

//@}

namespace Dxx
{
//! A class that refers to a vertex in a vertex buffer
//
//! @ingroup VertexBufferProxy
//!

class VertexBufferProxy::VRef : public VertexBufferProxy::VRefBase
{
public:

    //! Constructor
    VRef(VertexBufferProxy const * pProxy, void * pVertex);

    //! Returns a pointer to the vertex data (in the form of a VPtr)
    VPtr operator &();

    //! @name Overrides VRefBase
    //@{
    //	DirectX::XMFLOAT4 & Position() const;
    //	float & W() const;
    //	float & Blend0() const;
    //	float & Blend1() const;
    //	float & Blend2() const;
    //	float & Blend3() const;
    //	float & BlendIndexes() const;
    //	DirectX::XMFLOAT4 & Normal() const;
    //	float & PointSize() const;
    //	DWORD & Diffuse() const;
    //	DWORD & Specular() const;
    //	float * TexCoord0() const;
    //	float * TexCoord1() const;
    //	float * TexCoord2() const;
    //	float * TexCoord3() const;
    //	float * TexCoord4() const;
    //	float * TexCoord5() const;
    //	float * TexCoord6() const;
    //	float * TexCoord7() const;
    //@}
};
} // namespace Dxx

// Inline functions

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

inline IDirect3DVertexBuffer11 * VertexBufferProxy::GetVertexBuffer() const
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
    : pProxy_(pProxy)
    , pVertex_(pVertex)
{
}

inline DirectX::XMFLOAT4 & VertexBufferProxy::VRefBase::Position() const
{
    return *(DirectX::XMFLOAT4 *)((char *)pVertex_ + 0);
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

inline DirectX::XMFLOAT4 & VertexBufferProxy::VRefBase::Normal() const
{
    return *(DirectX::XMFLOAT4 *)((char *)pVertex_ + pProxy_->normalOffset_);
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
#endif // if 0

#endif // !defined(DXX_VERTEXBUFFERPROXY_H)
