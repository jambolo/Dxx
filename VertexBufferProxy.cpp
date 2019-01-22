/** @file *//********************************************************************************************************

                                                    VertexBufferProxy.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/VertexBufferProxy.cpp#10 $

    $NoKeywords: $

 *********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "VertexBufferProxy.h"

#if 0
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d11.h>

namespace Dxx
{
//!
//! @param	pMesh	Mesh containing the vertex buffer to proxy

VertexBufferProxy::VertexBufferProxy(ID3DXMesh * pMesh)
{
    pMesh->GetVertexBuffer(&pBuffer_);

    // Get the "Desc" data

    pBuffer_->GetDesc(&desc_);

    InitializeOffsets();
}

//! @param	pBuffer		Vertex buffer to proxy

VertexBufferProxy::VertexBufferProxy(ID3D11Buffer * pBuffer)
    : pBuffer_(pBuffer)
{
    pBuffer_->AddRef();

    // Get the "Desc" data

    pBuffer_->GetDesc(&desc_);

    InitializeOffsets();
}

void VertexBufferProxy::InitializeOffsets()
{
    int bump;

    // Compute the stride and offset values

    // Note: Position offset is 0 (if there is a position)

    switch (desc_.FVF & D3DFVF_POSITION_MASK)
    {
        case D3DFVF_XYZ:
            bump = 0                     + sizeof(DirectX::XMFLOAT4);
            break;

        case D3DFVF_XYZRHW:
        case D3DFVF_XYZW:
            wOffset_ = 0                     + sizeof(DirectX::XMFLOAT4);
            bump     = wOffset_              + sizeof(float);
            break;

        case D3DFVF_XYZB1:
            if ((desc_.FVF & D3DFVF_LASTBETA_UBYTE4) == 0)
            {
                blend0Offset_ = 0                     + sizeof(DirectX::XMFLOAT4);
                bump          = blend0Offset_     + sizeof(float);
            }
            else
            {
                blendIndexesOffset_ = 0                     + sizeof(DirectX::XMFLOAT4);
                bump = blendIndexesOffset_   + sizeof(DWORD);
            }
            break;

        case D3DFVF_XYZB2:
            blend0Offset_ = 0                     + sizeof(DirectX::XMFLOAT4);
            if ((desc_.FVF & D3DFVF_LASTBETA_UBYTE4) == 0)
            {
                blend1Offset_ = blend0Offset_     + sizeof(float);
                bump          = blend1Offset_     + sizeof(float);
            }
            else
            {
                blendIndexesOffset_ = blend0Offset_     + sizeof(float);
                bump = blendIndexesOffset_   + sizeof(DWORD);
            }
            break;

        case D3DFVF_XYZB3:
            blend0Offset_ = 0                     + sizeof(DirectX::XMFLOAT4);
            blend1Offset_ = blend0Offset_         + sizeof(float);
            if ((desc_.FVF & D3DFVF_LASTBETA_UBYTE4) == 0)
            {
                blend2Offset_ = blend1Offset_     + sizeof(float);
                bump          = blend2Offset_     + sizeof(float);
            }
            else
            {
                blendIndexesOffset_ = blend1Offset_     + sizeof(float);
                bump = blendIndexesOffset_   + sizeof(DWORD);
            }
            break;

        case D3DFVF_XYZB4:
            blend0Offset_ = 0                     + sizeof(DirectX::XMFLOAT4);
            blend1Offset_ = blend0Offset_         + sizeof(float);
            blend2Offset_ = blend1Offset_         + sizeof(float);
            if ((desc_.FVF & D3DFVF_LASTBETA_UBYTE4) == 0)
            {
                blend3Offset_ = blend2Offset_     + sizeof(float);
                bump          = blend3Offset_     + sizeof(float);
            }
            else
            {
                blendIndexesOffset_ = blend2Offset_     + sizeof(float);
                bump = blendIndexesOffset_   + sizeof(DWORD);
            }
            break;

        case D3DFVF_XYZB5:
            blend0Offset_ = 0                     + sizeof(DirectX::XMFLOAT4);
            blend1Offset_ = blend0Offset_         + sizeof(float);
            blend2Offset_ = blend1Offset_         + sizeof(float);
            blend3Offset_ = blend2Offset_         + sizeof(float);
            assert((desc_.FVF & D3DFVF_LASTBETA_UBYTE4) != 0);
            blendIndexesOffset_ = blend3Offset_     + sizeof(float);
            bump = blendIndexesOffset_   + sizeof(DWORD);
            break;

        default:
            bump = 0;                   // No position value.
            break;
    }

    normalOffset_    = bump;
    pointSizeOffset_ = bump;
    diffuseOffset_   = bump;
    specularOffset_  = bump;
    texCoord0Offset_ = bump;
    texCoord1Offset_ = bump;
    texCoord2Offset_ = bump;
    texCoord3Offset_ = bump;
    texCoord4Offset_ = bump;
    texCoord5Offset_ = bump;
    texCoord6Offset_ = bump;
    texCoord7Offset_ = bump;
    stride_          = bump;

    if ((desc_.FVF & D3DFVF_NORMAL) != 0)
    {
        bump = sizeof(DirectX::XMFLOAT4);
        pointSizeOffset_ += bump;
        diffuseOffset_   += bump;
        specularOffset_  += bump;
        texCoord0Offset_ += bump;
        texCoord1Offset_ += bump;
        texCoord2Offset_ += bump;
        texCoord3Offset_ += bump;
        texCoord4Offset_ += bump;
        texCoord5Offset_ += bump;
        texCoord6Offset_ += bump;
        texCoord7Offset_ += bump;
        stride_          += bump;
    }

    if ((desc_.FVF & D3DFVF_PSIZE) != 0)
    {
        bump              = sizeof(float);
        diffuseOffset_   += bump;
        specularOffset_  += bump;
        texCoord0Offset_ += bump;
        texCoord1Offset_ += bump;
        texCoord2Offset_ += bump;
        texCoord3Offset_ += bump;
        texCoord4Offset_ += bump;
        texCoord5Offset_ += bump;
        texCoord6Offset_ += bump;
        texCoord7Offset_ += bump;
        stride_          += bump;
    }

    if ((desc_.FVF & D3DFVF_DIFFUSE) != 0)
    {
        bump = sizeof(DWORD);
        specularOffset_  += bump;
        texCoord0Offset_ += bump;
        texCoord1Offset_ += bump;
        texCoord2Offset_ += bump;
        texCoord3Offset_ += bump;
        texCoord4Offset_ += bump;
        texCoord5Offset_ += bump;
        texCoord6Offset_ += bump;
        texCoord7Offset_ += bump;
        stride_          += bump;
    }

    if ((desc_.FVF & D3DFVF_SPECULAR) != 0)
    {
        bump = sizeof(DWORD);
        texCoord0Offset_ += bump;
        texCoord1Offset_ += bump;
        texCoord2Offset_ += bump;
        texCoord3Offset_ += bump;
        texCoord4Offset_ += bump;
        texCoord5Offset_ += bump;
        texCoord6Offset_ += bump;
        texCoord7Offset_ += bump;
        stride_          += bump;
    }

    switch (desc_.FVF & D3DFVF_TEXCOUNT_MASK)
    {
        case D3DFVF_TEX8:
            bump     = ((((desc_.FVF >> 30) + 1) & 3) + 1) * sizeof(float);
            stride_ += bump;
        /* fall through */

        case D3DFVF_TEX7:
            bump = ((((desc_.FVF >> 28) + 1) & 3) + 1) * sizeof(float);
            texCoord7Offset_ += bump;
            stride_          += bump;
        /* fall through */

        case D3DFVF_TEX6:
            bump = ((((desc_.FVF >> 26) + 1) & 3) + 1) * sizeof(float);
            texCoord6Offset_ += bump;
            texCoord7Offset_ += bump;
            stride_          += bump;
        /* fall through */

        case D3DFVF_TEX5:
            bump = ((((desc_.FVF >> 24) + 1) & 3) + 1) * sizeof(float);
            texCoord5Offset_ += bump;
            texCoord6Offset_ += bump;
            texCoord7Offset_ += bump;
            stride_          += bump;
        /* fall through */

        case D3DFVF_TEX4:
            bump = ((((desc_.FVF >> 22) + 1) & 3) + 1) * sizeof(float);
            texCoord4Offset_ += bump;
            texCoord5Offset_ += bump;
            texCoord6Offset_ += bump;
            texCoord7Offset_ += bump;
            stride_          += bump;
        /* fall through */

        case D3DFVF_TEX3:
            bump = ((((desc_.FVF >> 20) + 1) & 3) + 1) * sizeof(float);
            texCoord3Offset_ += bump;
            texCoord4Offset_ += bump;
            texCoord5Offset_ += bump;
            texCoord6Offset_ += bump;
            texCoord7Offset_ += bump;
            stride_          += bump;
        /* fall through */

        case D3DFVF_TEX2:
            bump = ((((desc_.FVF >> 18) + 1) & 3) + 1) * sizeof(float);
            texCoord2Offset_ += bump;
            texCoord3Offset_ += bump;
            texCoord4Offset_ += bump;
            texCoord5Offset_ += bump;
            texCoord6Offset_ += bump;
            texCoord7Offset_ += bump;
            stride_          += bump;
        /* fall through */

        case D3DFVF_TEX1:
            bump = ((((desc_.FVF >> 16) + 1) & 3) + 1) * sizeof(float);
            texCoord1Offset_ += bump;
            texCoord2Offset_ += bump;
            texCoord3Offset_ += bump;
            texCoord4Offset_ += bump;
            texCoord5Offset_ += bump;
            texCoord6Offset_ += bump;
            texCoord7Offset_ += bump;
            stride_          += bump;
    }
}
} // namespace Dxx
#endif
