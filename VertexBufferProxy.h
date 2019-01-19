/** @file *//********************************************************************************************************

                                                     VertexBufferProxy.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/VertexBufferProxy.h#13 $

    $NoKeywords: $

 *********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>

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
    VertexBufferProxy(IDirect3DVertexBuffer11 * pBuffer);

    //! Destructor
    ~VertexBufferProxy();

    //! Returns the vertex buffer
    IDirect3DVertexBuffer11 * GetVertexBuffer() const;

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

    IDirect3DVertexBuffer11 * pBuffer_;                  //!< The vertex buffer.
    D3DVERTEXBUFFER_DESC desc_;                         //!< The "Desc" data for the buffer.
    void * pData_;                                  //!< Pointer to vertex buffer data (valid only while locked)
    int lockOffset_;                                    //!< Offset to beginning of the locked data
    int wOffset_;                                       //!< Offset to the W value.
    int blend0Offset_;                                  //!< Offset to the 1st blending weight value.
    int blend1Offset_;                                  //!< Offset to the 2nd blending weight value.
    int blend2Offset_;                                  //!< Offset to the 3rd blending weight value.
    int blend3Offset_;                                  //!< Offset to the 4th blending weight value.
    int blendIndexesOffset_;                            //!< Offset to the blending weight indexes.
    int normalOffset_;                                  //!< Offset to the normal value.
    int pointSizeOffset_;                               //!< Offset to the point size value.
    int diffuseOffset_;                             //!< Offset to the diffuse color value.
    int specularOffset_;                                //!< Offset to the specular value.
    int texCoord0Offset_;                               //!< Offset to the 1st set of texture coordinates.
    int texCoord1Offset_;                               //!< Offset to the 2nd set of texture coordinates.
    int texCoord2Offset_;                               //!< Offset to the 3rd set of texture coordinates.
    int texCoord3Offset_;                               //!< Offset to the 4th set of texture coordinates.
    int texCoord4Offset_;                               //!< Offset to the 5th set of texture coordinates.
    int texCoord5Offset_;                               //!< Offset to the 6th set of texture coordinates.
    int texCoord6Offset_;                               //!< Offset to the 7th set of texture coordinates.
    int texCoord7Offset_;                               //!< Offset to the 8th set of texture coordinates.
    int stride_;                                        //!< Size of a vertex in bytes.
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

#include "VertexBufferProxy.inl"
