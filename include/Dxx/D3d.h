/** @file *//********************************************************************************************************

                                                        D3d.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/D3d.h#26 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <windows.h>

//! @defgroup	D3dx	Direct3D Extensions
//!	@ingroup	Dxx
//! Home-brew extensions to Direct3D

namespace Dxx
{
//! @name	Useful Vector Constants
//! @ingroup	D3dx
//@{

//! 2D origin
DirectX::XMFLOAT2 constexpr Vector2Origin() { return { 0.f, 0.f }; }

//! 2D unit X vector
DirectX::XMFLOAT2 constexpr Vector2XAxis() { return { 1.f, 0.f }; }

//! 2D unit Y vector
DirectX::XMFLOAT2 constexpr Vector2YAxis() { return { 0.f, 1.f }; }

//! 3D origin
DirectX::XMFLOAT3 constexpr Vector3Origin() { return { 0.f, 0.f, 0.f }; }

//! 3D unit X vector
DirectX::XMFLOAT3 constexpr Vector3XAxis() { return { 1.f, 0.f, 0.f }; }

//! 3D unit Y vector
DirectX::XMFLOAT3 constexpr Vector3YAxis() { return { 0.f, 1.f, 0.f }; }

//! 3D unit Z vector
DirectX::XMFLOAT3 constexpr Vector3ZAxis() { return { 0.f, 0.f, 1.f }; }

//! 4D origin
DirectX::XMFLOAT4 constexpr Vector4Origin() { return { 0.f, 0.f, 0.f, 0.f }; }

//! 4D unit X vector
DirectX::XMFLOAT4 constexpr Vector4XAxis() { return { 1.f, 0.f, 0.f, 0.f }; }

//! 4D unit Y vector
DirectX::XMFLOAT4 constexpr Vector4YAxis() { return { 0.f, 1.f, 0.f, 0.f }; }

//! 4D unit Z vector
DirectX::XMFLOAT4 constexpr Vector4ZAxis() { return { 0.f, 0.f, 1.f, 0.f }; }

//! 4D unit W vector
DirectX::XMFLOAT4 constexpr Vector4WAxis() { return { 0.f, 0.f, 0.f, 1.f }; }

//! %Quaternion multiplicative identity
DirectX::XMFLOAT4 constexpr QuaternionIdentity() { return { 0.f, 0.f, 0.f, 1.f }; }

//@}

//! @name	Useful Matrix Functions
//! @ingroup	D3dx
//@{

//! Returns a const reference to the const matrix's X basis vector
inline DirectX::XMFLOAT4 const & MatrixXBasis(DirectX::XMFLOAT4X4 const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[0]);
}

//! Returns a const reference to the const matrix's Y basis vector
inline DirectX::XMFLOAT4 const & MatrixYBasis(DirectX::XMFLOAT4X4 const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[4]);
}

//! Returns a const reference to the const matrix's Z basis vector
inline DirectX::XMFLOAT4 const & MatrixZBasis(DirectX::XMFLOAT4X4 const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[8]);
}

//! Returns a const reference to the const matrix's translation vector
inline DirectX::XMFLOAT4 const & MatrixTranslation(DirectX::XMFLOAT4X4 const & m)
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(m.m[12]);
}

//! Returns a reference to the matrix's X basis vector
inline DirectX::XMFLOAT4 & MatrixXBasis(DirectX::XMFLOAT4X4 & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixXBasis(const_cast<DirectX::XMFLOAT4X4 const &>(m)));
}

//! Returns a reference to the matrix's Y basis vector
inline DirectX::XMFLOAT4 & MatrixYBasis(DirectX::XMFLOAT4X4 & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixYBasis(const_cast<DirectX::XMFLOAT4X4 const &>(m)));
}

//! Returns a reference to the matrix's Z basis vector
inline DirectX::XMFLOAT4 & MatrixZBasis(DirectX::XMFLOAT4X4 & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixZBasis(const_cast<DirectX::XMFLOAT4X4 const &>(m)));
}

//! Returns a reference to the matrix's translation vector
inline DirectX::XMFLOAT4 & MatrixTranslation(DirectX::XMFLOAT4X4 & m)
{
    return const_cast<DirectX::XMFLOAT4 &>(MatrixTranslation(const_cast<DirectX::XMFLOAT4X4 const &>(m)));
}

//! Returns true if the 3x3 submatrix is orthonormal (within the given tolerance)
bool IsOrthonormal(DirectX::XMFLOAT4X4 const & m, float tolerance);

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

//! @name	Miscellaneous Functions
//! @ingroup	D3dx
//@{

//! Computes the normal of a face
DirectX::XMFLOAT3 ComputeFaceNormal(DirectX::XMFLOAT3 const & v0,
                                      DirectX::XMFLOAT3 const & v1,
                                      DirectX::XMFLOAT3 const & v2,
                                      DirectX::XMFLOAT3 *       pN);

//! Computes the normal for a vertex in a uniform axis-aligned grid
DirectX::XMFLOAT3 ComputeGridNormal(float               z1,
                                      float               z2,
                                      float               z3,
                                      float               z4,
                                      float               scale,
                                      DirectX::XMFLOAT3 * pN = nullptr);

#if 0
//! Creates a full-screen D3D device. Returns a result code.
HRESULT CreateD3dFullScreenDevice(IDirect3D9 *    pD3d,
                                  HWND            hWnd,
                                  int             width,
                                  int             height,
                                  D3DFORMAT       format,
                                  ID3D11Device ** ppDevice,
                                  D3DFORMAT       zBufferFormat = D3DFMT_D24S8,
                                  UINT            adapter      = D3DADAPTER_DEFAULT,
                                  UINT            swapInterval = D3DPRESENT_INTERVAL_DEFAULT,
                                  D3DDEVTYPE      deviceType   = D3DDEVTYPE_HAL,
                                  DWORD           behavior     = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE
);

//! Creates a D3D device associated with a window. Returns a result code.
HRESULT CreateD3dWindowedDevice(IDirect3D9 *    pD3d,
                                HWND            hWnd,
                                ID3D11Device ** ppDevice,
                                D3DFORMAT       zBufferFormat = D3DFMT_UNKNOWN,
                                UINT            adapter      = D3DADAPTER_DEFAULT,
                                UINT            swapInterval = D3DPRESENT_INTERVAL_DEFAULT,
                                D3DDEVTYPE      deviceType   = D3DDEVTYPE_HAL,
                                DWORD           behavior     = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE
);

//! Resets an existing D3D device associated with a window. Returns a result code.
HRESULT ResetD3dWindowedDevice(ID3D11Device * pDevice, D3DFORMAT zBufferFormat = D3DFMT_UNKNOWN);

//! Finds a matching display mode. Returns a result code.
HRESULT FindDisplayMode(IDirect3D9 *     pD3d,
                        int              width,
                        int              height,
                        D3DFORMAT        format,
                        D3DDISPLAYMODE * pDisplayMode,
                        UINT             adapter     = D3DADAPTER_DEFAULT,
                        int              refreshRate = 0
);
#endif // if 0

//! Strips a grid generating 32-bit indexes.
int StripGrid(int w, int h, uint16_t * pData);

//! Strips a grid generating 32-bit indexes.
int StripGrid(int w, int h, uint32_t * pData);

#if 0
//! Sets a render state, caching the values to prevent redundant state changes.
HRESULT SetRenderState(ID3D11Device * pD3dDevice, D3DRENDERSTATETYPE state, DWORD value);

//! Gets a render state and caches the value.
HRESULT GetRenderState(ID3D11Device * pD3dDevice, D3DRENDERSTATETYPE state, DWORD * pValue);

//! Clears the render state read cache.
void ClearRenderStateCache();

//! Assembles and returns a vertex shader
HRESULT AssembleVertexShader(ID3D11Device * pDevice,
                             LPCTSTR pSrcFile,
                             D3DXMACRO const * pDefines, ID3DXInclude * pInclude, DWORD Flags,
                             IDirect3DVertexShader9 ** ppShader);

//! Assembles and returns a pixel shader
HRESULT AssemblePixelShader(ID3D11Device * pDevice,
                            LPCTSTR pSrcFile,
                            D3DXMACRO const * pDefines, ID3DXInclude * pInclude, DWORD Flags,
                            IDirect3DPixelShader9 ** ppPixelShader);

// Sets up a texture stage
HRESULT SetTextureStage(ID3D11Device *          pD3dDevice,
                        int                     stage,
                        D3DTEXTUREOP            op,
                        DWORD                   arg1 = D3DTA_TEXTURE,
                        DWORD                   arg2 = D3DTA_CURRENT,
                        IDirect3DBaseTexture9 * pTexture = 0);
#endif // if 0
//@}
} // namespace Dxx
