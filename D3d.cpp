#include "PrecompiledHeaders.h"

#include "D3d.h"

namespace Dxx
{
#if 0
//! @param	pD3d			Direct3D object
//! @param	hWnd			Window handle
//! @param	width			Display width
//! @param	height			Display height
//! @param	format			Pixel format
//! @param	ppDevice		Where to store the new device pointer
//! @param	zBufferFormat	Z-buffer format
//! @param	adapter			Which adapter
//! @param	swapInterval	VSync behavior
//! @param	deviceType		Device type
//! @param	behavior		Behavior (see docs for <tt>IDirect3D9::CreateDevice</tt>)
//!
//! @return		S_OK is returned if successful, S_FALSE is returned if the desired display device
//!				is not available. Any other value indicates an error.

HRESULT CreateD3dFullScreenDevice(IDirect3D9 *        pD3d,
                                  HWND                hWnd,
                                  int                 width,
                                  int                 height,
                                  D3DFORMAT           format,
                                  ID3D11Device ** ppDevice,
                                  D3DFORMAT           zBufferFormat /* = D3DFMT_D24S8 */,
                                  UINT                adapter /* = D3DADAPTER_DEFAULT*/,
                                  UINT                swapInterval /* = D3DPRESENT_INTERVAL_DEFAULT */,
                                  D3DDEVTYPE          deviceType /* = D3DDEVTYPE_HAL*/,
                                  DWORD               behavior          /* =
                                                                           D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE*/
)
{
    HRESULT        hr;
    D3DDISPLAYMODE displayMode;

    *ppDevice = 0;

    // Get the desired display mode

    hr = FindDisplayMode(pD3d, width, height, format, &displayMode, adapter);
    if (hr != S_OK)
        return hr;

    // Create the d3d device using the desktop format

    D3DPRESENT_PARAMETERS present;

    present.BackBufferWidth        = displayMode.Width;
    present.BackBufferHeight       = displayMode.Height;
    present.BackBufferFormat       = displayMode.Format;
    present.BackBufferCount        = 0;
    present.MultiSampleType        = D3DMULTISAMPLE_NONE;
    present.MultiSampleQuality     = 0;
    present.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    present.hDeviceWindow          = hWnd;
    present.Windowed               = FALSE;
    present.EnableAutoDepthStencil = (zBufferFormat != D3DFMT_UNKNOWN);
    present.AutoDepthStencilFormat = zBufferFormat;
    present.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
    present.FullScreen_RefreshRateInHz = displayMode.RefreshRate;
    present.PresentationInterval       = swapInterval;

    return pD3d->CreateDevice(adapter, deviceType, hWnd, behavior, &present, ppDevice);
}

//! @param	pD3d			Direct3D object.
//! @param	hWnd			Window handle.
//! @param	ppDevice		Where to store the new device.
//! @param	zBufferFormat	Z-buffer format.
//! @param	adapter			Which adapter.
//! @param	swapInterval	VSync behavior
//! @param	deviceType		Device type.
//! @param	behavior		Behavior (see docs for <tt>IDirect3D9::CreateDevice</tt>).

HRESULT CreateD3dWindowedDevice(IDirect3D9 *        pD3d,
                                HWND                hWnd,
                                ID3D11Device ** ppDevice,
                                D3DFORMAT           zBufferFormat /* = D3DFMT_UNKNOWN */,
                                UINT                adapter /* = D3DADAPTER_DEFAULT*/,
                                UINT                swapInterval /* = D3DPRESENT_INTERVAL_DEFAULT */,
                                D3DDEVTYPE          deviceType /* = D3DDEVTYPE_HAL*/,
                                DWORD               behavior            /* =
                                                                           D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE*/
)
{
    HRESULT hr;

    *ppDevice = 0;

    // Get the format of the desktop

    D3DDISPLAYMODE displayMode;

    hr = pD3d->GetAdapterDisplayMode(adapter, &displayMode);
    if (FAILED(hr))
        return hr;

    // Create the d3d device using the desktop format

    D3DPRESENT_PARAMETERS present;

    ZeroMemory(&present, sizeof(present));
    present.Windowed               = TRUE;
    present.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    present.BackBufferFormat       = displayMode.Format;
    present.EnableAutoDepthStencil = (zBufferFormat != D3DFMT_UNKNOWN);
    present.AutoDepthStencilFormat = zBufferFormat;
    present.PresentationInterval   = swapInterval;

    return pD3d->CreateDevice(adapter, deviceType, hWnd, behavior, &present, ppDevice);
}

//! @param	pDevice			The device to reset.
//! @param	zBufferFormat	Z-buffer format. The default is @c D3DFMT_UNKNOWN.

HRESULT ResetD3dWindowedDevice(ID3D11Device * pDevice, D3DFORMAT zBufferFormat /* = D3DFMT_UNKNOWN*/)
{
    ClearRenderStateCache();    // All render states will be reset, so clear the cache.

    D3DPRESENT_PARAMETERS present;

    present.BackBufferWidth        = 0;
    present.BackBufferHeight       = 0;
    present.BackBufferFormat       = D3DFMT_UNKNOWN;
    present.BackBufferCount        = 0;
    present.MultiSampleType        = D3DMULTISAMPLE_NONE;
    present.MultiSampleQuality     = 0;
    present.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    present.hDeviceWindow          = NULL;
    present.Windowed               = TRUE;
    present.EnableAutoDepthStencil = (zBufferFormat != D3DFMT_UNKNOWN);
    present.AutoDepthStencilFormat = zBufferFormat;
    present.Flags = 0;
    present.FullScreen_RefreshRateInHz = 0;
    present.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;

    return pDevice->Reset(&present);
}

HRESULT FindDisplayMode(IDirect3D9 *     pD3d,
                        int              width,
                        int              height,
                        D3DFORMAT        format,
                        D3DDISPLAYMODE * pDisplayMode,
                        UINT             adapter /* = D3DADAPTER_DEFAULT*/,
                        int              refreshRate        /* = 0 */
)
{
    int const nModes = pD3d->GetAdapterModeCount(adapter, format);

    HRESULT        hr;
    bool           found = false;
    D3DDISPLAYMODE displayMode;

    for (int mode = 0; mode < nModes; mode++)
    {
        hr = pD3d->EnumAdapterModes(adapter, format, mode, &displayMode);
        if (FAILED(hr))
            return hr;

        if (displayMode.Width == (unsigned)width && displayMode.Height == (unsigned)height)
        {
            found         = true;
            *pDisplayMode = displayMode;

            if (refreshRate > 0 && displayMode.RefreshRate == (unsigned)refreshRate)
                break;
        }
    }

    return (found) ? S_OK : S_FALSE;
}

#define RENDERSTATE_CACHE_SIZE 256

static DWORD s_aRenderStateCache[RENDERSTATE_CACHE_SIZE];
static bitset<RENDERSTATE_CACHE_SIZE> s_aRenderStateCacheValueIsValid;

HRESULT SetRenderState(ID3D11Device * pD3dDevice, D3DRENDERSTATETYPE state, DWORD value)
{
    assert_array_index_valid(s_aRenderStateCache, state);

    HRESULT hr;

    // If the new value is different from the current value, then set it and save it.

    if (!s_aRenderStateCacheValueIsValid.test(state) || s_aRenderStateCache[state] != value)
    {
        // Set the new state

        hr = pD3dDevice->SetRenderState(state, value);
        assert_succeeded(hr);

        // Save the state's new value.

        s_aRenderStateCache[state] = value;
        s_aRenderStateCacheValueIsValid.set(state);
    }
    else
    {
        hr = S_OK;
    }

    return hr;
}

HRESULT GetRenderState(ID3D11Device * pD3dDevice, D3DRENDERSTATETYPE state, DWORD * pValue)
{
    assert_array_index_valid(s_aRenderStateCache, state);

    HRESULT hr;

    if (!s_aRenderStateCacheValueIsValid[state])
    {
        hr = pD3dDevice->GetRenderState(state, &s_aRenderStateCache[state]);
        assert_succeeded(hr);
        s_aRenderStateCacheValueIsValid.set(state);
    }
    else
    {
        hr = S_OK;
    }

    *pValue = s_aRenderStateCache[state];

    return hr;
}

void ClearRenderStateCache()
{
    s_aRenderStateCacheValueIsValid.reset();
}

HRESULT AssembleVertexShader(ID3D11Device * pDevice,
                             LPCTSTR pSrcFile,
                             D3DXMACRO const * pDefines, ID3DXInclude * pInclude, DWORD Flags,
                             IDirect3DVertexShader9 ** ppShader)
{
    HRESULT       hr;
    ID3D11Buffer * pCode      = 0;
    ID3D11Buffer * pErrorMsgs = 0;

    hr = D3DXAssembleShaderFromFile(pSrcFile, pDefines, pInclude, Flags, &pCode, &pErrorMsgs);
    if (FAILED(hr))
    {
#if defined(_DEBUG)
        if (pErrorMsgs != 0 && pErrorMsgs->GetBufferPointer() != 0)
            OutputDebugString((char *)pErrorMsgs->GetBufferPointer());

#endif      // defined( _DEBUG )
        return hr;
    }

    hr = pDevice->CreateVertexShader((DWORD *)pCode->GetBufferPointer(), ppShader);

    Wx::SafeRelease(pCode);
    Wx::SafeRelease(pErrorMsgs);

    return hr;
}

HRESULT AssemblePixelShader(ID3D11Device * pDevice,
                            LPCTSTR pSrcFile,
                            D3DXMACRO const * pDefines, ID3DXInclude * pInclude, DWORD Flags,
                            IDirect3DPixelShader9 ** ppPixelShader)
{
    HRESULT       hr;
    ID3D11Buffer * pCode      = 0;
    ID3D11Buffer * pErrorMsgs = 0;

    hr = D3DXAssembleShaderFromFile(pSrcFile, pDefines, pInclude, Flags, &pCode, &pErrorMsgs);
    if (FAILED(hr))
    {
#if defined(_DEBUG)
        if (pErrorMsgs != 0 && pErrorMsgs->GetBufferPointer() != 0)
            OutputDebugString((char *)pErrorMsgs->GetBufferPointer());

#endif      // defined( _DEBUG )
        return hr;
    }

    hr = pDevice->CreatePixelShader((DWORD *)pCode->GetBufferPointer(), ppPixelShader);

    Wx::SafeRelease(pCode);
    Wx::SafeRelease(pErrorMsgs);

    return hr;
}

//! @param	pD3dDevice	Device this applies to
//! @param	stage		Texture stage
//! @param	op			Operation (see docs for @c D3DTEXTUREOP)
//! @param	arg1		Source 1 (see docs for @c D3DTA)
//! @param	arg2		Source 2 (see docs for @c D3DTA)
//! @param	pTexture	Texture, or 0 if not used

HRESULT SetTextureStage(ID3D11Device *      pD3dDevice,
                        int                     stage,
                        D3DTEXTUREOP            op,
                        DWORD                   arg1 /* = D3DTA_TEXTURE*/,
                        DWORD                   arg2 /* = D3DTA_CURRENT*/,
                        IDirect3DBaseTexture9 * pTexture /* = 0*/)
{
    HRESULT hr;

    hr = pD3dDevice->SetTextureStageState(stage, D3DTSS_COLOROP, op);
    if (FAILED(hr))
        return hr;

    hr = pD3dDevice->SetTextureStageState(stage, D3DTSS_COLORARG1, arg1);
    if (FAILED(hr))
        return hr;

    hr = pD3dDevice->SetTextureStageState(stage, D3DTSS_COLORARG2, arg2);
    if (FAILED(hr))
        return hr;

    hr = pD3dDevice->SetTexture(stage, pTexture);

    return hr;
}
#endif

//! @param	m			Matrix to check
//! @param	tolerance	Maximum allowed deviation

bool IsOrthonormal(DirectX::XMFLOAT4X4 const & m, float tolerance)
{
    // The (square of the) length of each row and column vector should be 1. Compute the error for each row and column.

    float const erx = 1.0f - m._11 * m._11 + m._12 * m._12 + m._13 * m._13;
    float const ery = 1.0f - m._21 * m._21 + m._22 * m._22 + m._23 * m._23;
    float const erz = 1.0f - m._31 * m._31 + m._32 * m._32 + m._33 * m._33;
    float const ecx = 1.0f - m._11 * m._11 + m._21 * m._21 + m._31 * m._31;
    float const ecy = 1.0f - m._12 * m._12 + m._22 * m._22 + m._32 * m._32;
    float const ecz = 1.0f - m._13 * m._13 + m._23 * m._23 + m._33 * m._33;

    float const e = erx * erx + ery * ery + erz * erz + ecx * ecx + ecy * ecy + ecz * ecz;

    return e <= tolerance;
}
} // namespace Dxx
