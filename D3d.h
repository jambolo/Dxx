/** @file *//********************************************************************************************************

                                                        D3d.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/D3d.h#26 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include "Misc/Exceptions.h"
#include "Misc/Types.h"
#include <d3d9.h>
#include <DirectXMath.h>

//! @defgroup	D3dx	Direct3D Extensions
//!	@ingroup	Dxx
//! Home-brew extensions to Direct3D

namespace Dxx
{
//! @name	Useful Vector Constants
//! @ingroup	D3dx
//@{

//! 2D origin
inline DirectX::XMFLOAT2 Vector2Origin() { return DirectX::XMFLOAT2(0.f, 0.f); }

//! 2D unit X vector
inline DirectX::XMFLOAT2 Vector2XAxis() { return DirectX::XMFLOAT2(1.f, 0.f); }

//! 2D unit Y vector
inline DirectX::XMFLOAT2 Vector2YAxis() { return DirectX::XMFLOAT2(0.f, 1.f); }

//! 3D origin
inline DirectX::XMFLOAT4 Vector3Origin() { return DirectX::XMFLOAT4(0.f, 0.f, 0.f); }

//! 3D unit X vector
inline DirectX::XMFLOAT4 Vector3XAxis() { return DirectX::XMFLOAT4(1.f, 0.f, 0.f); }

//! 3D unit Y vector
inline DirectX::XMFLOAT4 Vector3YAxis() { return DirectX::XMFLOAT4(0.f, 1.f, 0.f); }

//! 3D unit Z vector
inline DirectX::XMFLOAT4 Vector3ZAxis() { return DirectX::XMFLOAT4(0.f, 0.f, 1.f); }

//! 4D origin
inline D3DXVECTOR4 Vector4Origin() { return D3DXVECTOR4(0.f, 0.f, 0.f, 0.f); }

//! 4D unit X vector
inline D3DXVECTOR4 Vector4XAxis() { return D3DXVECTOR4(1.f, 0.f, 0.f, 0.f); }

//! 4D unit Y vector
inline D3DXVECTOR4 Vector4YAxis() { return D3DXVECTOR4(0.f, 1.f, 0.f, 0.f); }

//! 4D unit Z vector
inline D3DXVECTOR4 Vector4ZAxis() { return D3DXVECTOR4(0.f, 0.f, 1.f, 0.f); }

//! 4D unit W vector
inline D3DXVECTOR4 Vector4WAxis() { return D3DXVECTOR4(0.f, 0.f, 0.f, 1.f); }

//! %Quaternion multiplicative identity
inline DirectX::XMFLOAT4 QuaternionIdentity() { return DirectX::XMFLOAT4(0.f, 0.f, 0.f, 1.f); }

//@}

//! @name	Useful Matrix Functions
//! @ingroup	D3dx
//@{

//! Returns a const reference to the const matrix's X basis vector
inline DirectX::XMFLOAT4 const & MatrixXBasis(D3DMATRIX const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[0]);
}

//! Returns a const reference to the const matrix's Y basis vector
inline DirectX::XMFLOAT4 const & MatrixYBasis(D3DMATRIX const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[4]);
}

//! Returns a const reference to the const matrix's Z basis vector
inline DirectX::XMFLOAT4 const & MatrixZBasis(D3DMATRIX const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[8]);
}

//! Returns a const reference to the const matrix's translation vector
inline DirectX::XMFLOAT4 const & MatrixTranslation(D3DMATRIX const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[12]);
}

//! Returns a reference to the matrix's X basis vector
inline DirectX::XMFLOAT4 & MatrixXBasis(D3DMATRIX & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixXBasis(const_cast<D3DMATRIX const &>(m)));
}

//! Returns a reference to the matrix's Y basis vector
inline DirectX::XMFLOAT4 & MatrixYBasis(D3DMATRIX & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixYBasis(const_cast<D3DMATRIX const &>(m)));
}

//! Returns a reference to the matrix's Z basis vector
inline DirectX::XMFLOAT4 & MatrixZBasis(D3DMATRIX & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixZBasis(const_cast<D3DMATRIX const &>(m)));
}

//! Returns a reference to the matrix's translation vector
inline DirectX::XMFLOAT4 & MatrixTranslation(D3DMATRIX & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixTranslation(const_cast<D3DMATRIX const &>(m)));
}

//! Returns @c true if the 3x3 submatrix is orthonormal
bool IsOrthonormal(D3DMATRIX const & m);

//@}

//! @name	Miscellaneous Constants
//! @ingroup	D3dx
//@{

enum
{
    VERTEX_NONE    = 0xffff,    //!< A vertex id with this value is unassigned or invalid
    FACE_NONE      = 0xffff,    //!< A face id with this value is unassigned or invalid
    ATTRIBUTE_NONE = 0xffff,    //!< An attribute id with this value is unassigned or invalid
};

//@}

//! @name	Common Colors
//! @ingroup	D3dx
//@{

static DirectX::XMFLOAT4 const WHITE{ 1.0f, 1.0f, 1.0f, 1.0f };
static DirectX::XMFLOAT4 const BLACK{ 0.0f, 0.0f, 0.0f, 1.0f };
static DirectX::XMFLOAT4 const RED{ 1.0f, 0.0f, 0.0f, 1.0f };
static DirectX::XMFLOAT4 const GREEN{ 0.0f, 1.0f, 0.0f, 1.0f };
static DirectX::XMFLOAT4 const BLUE{ 0.0f, 0.0f, 1.0f, 1.0f };
static DirectX::XMFLOAT4 const CYAN{ 0.0f, 1.0f, 1.0f, 1.0f };
static DirectX::XMFLOAT4 const MAGENTA{ 1.0f, 0.0f, 1.0f, 1.0f };
static DirectX::XMFLOAT4 const YELLOW{ 1.0f, 1.0f, 0.0f, 1.0f };
static DirectX::XMFLOAT4 const GRAY{ 0.5f, 0.5f, 0.5f, 1.0f };
static DirectX::XMFLOAT4 const NOCOLOR{ 0.0f, 0.0f, 0.0f, 0.0f };
static DirectX::XMFLOAT4 const SUNLIGHT{ 0.75f, 0.73f, 0.70f, 1.0f };
static DirectX::XMFLOAT4 const SKYLIGHT{ 0.25f, 0.27f, 0.30f, 1.0f };

//@}

//! @name	Miscellaneous Functions
//! @ingroup	D3dx
//@{

//! Computes the normal of a face
DirectX::XMFLOAT4 * ComputeFaceNormal(DirectX::XMFLOAT4 const & v0, DirectX::XMFLOAT4 const & v1, DirectX::XMFLOAT4 const & v2, DirectX::XMFLOAT4 * pN);

//! Computes the normal for a vertex in a uniform axis-aligned grid
DirectX::XMFLOAT4 * ComputeGridNormal(float z1, float z2, float z3, float z4, float scale, DirectX::XMFLOAT4 * pN);

//! Creates a full-screen D3D device. Returns a result code.
HRESULT CreateD3dFullScreenDevice(IDirect3D9 *        pD3d,
                                  HWND                hWnd,
                                  int                 width,
                                  int                 height,
                                  D3DFORMAT           format,
                                  IDirect3DDevice11 ** ppDevice,
                                  D3DFORMAT           zBufferFormat = D3DFMT_D24S8,
                                  UINT                adapter      = D3DADAPTER_DEFAULT,
                                  UINT                swapInterval = D3DPRESENT_INTERVAL_DEFAULT,
                                  D3DDEVTYPE          deviceType   = D3DDEVTYPE_HAL,
                                  DWORD               behavior     = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE
);

//! Creates a D3D device associated with a window. Returns a result code.
HRESULT CreateD3dWindowedDevice(IDirect3D9 *        pD3d,
                                HWND                hWnd,
                                IDirect3DDevice11 ** ppDevice,
                                D3DFORMAT           zBufferFormat = D3DFMT_UNKNOWN,
                                UINT                adapter      = D3DADAPTER_DEFAULT,
                                UINT                swapInterval = D3DPRESENT_INTERVAL_DEFAULT,
                                D3DDEVTYPE          deviceType   = D3DDEVTYPE_HAL,
                                DWORD               behavior     = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE
);

//! Resets an existing D3D device associated with a window. Returns a result code.
HRESULT ResetD3dWindowedDevice(IDirect3DDevice11 * pDevice, D3DFORMAT zBufferFormat = D3DFMT_UNKNOWN);

//! Finds a matching display mode. Returns a result code.
HRESULT FindDisplayMode(IDirect3D9 *     pD3d,
                        int              width,
                        int              height,
                        D3DFORMAT        format,
                        D3DDISPLAYMODE * pDisplayMode,
                        UINT             adapter     = D3DADAPTER_DEFAULT,
                        int              refreshRate = 0
);

//! Strips a grid generating 32-bit indexes.
int StripGrid(int w, int h, uint16_t * pData);

//! Strips a grid generating 32-bit indexes.
int StripGrid(int w, int h, uint32_t * pData);

//! Sets a render state, caching the values to prevent redundant state changes.
HRESULT SetRenderState(IDirect3DDevice11 * pD3dDevice, D3DRENDERSTATETYPE state, DWORD value);

//! Gets a render state and caches the value.
HRESULT GetRenderState(IDirect3DDevice11 * pD3dDevice, D3DRENDERSTATETYPE state, DWORD * pValue);

//! Clears the render state read cache.
void ClearRenderStateCache();

//! Assembles and returns a vertex shader
HRESULT AssembleVertexShader(IDirect3DDevice11 * pDevice,
                             LPCTSTR pSrcFile,
                             D3DXMACRO const * pDefines, ID3DXInclude * pInclude, DWORD Flags,
                             IDirect3DVertexShader9 ** ppShader);

//! Assembles and returns a pixel shader
HRESULT AssemblePixelShader(IDirect3DDevice11 * pDevice,
                            LPCTSTR pSrcFile,
                            D3DXMACRO const * pDefines, ID3DXInclude * pInclude, DWORD Flags,
                            IDirect3DPixelShader9 ** ppPixelShader);

// Sets up a texture stage
HRESULT SetTextureStage(IDirect3DDevice11 *      pD3dDevice,
                        int                     stage,
                        D3DTEXTUREOP            op,
                        DWORD                   arg1 = D3DTA_TEXTURE,
                        DWORD                   arg2 = D3DTA_CURRENT,
                        IDirect3DBaseTexture9 * pTexture = 0);
//@}
} // namespace Dxx
