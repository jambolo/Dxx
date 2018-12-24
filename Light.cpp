/** @file *//********************************************************************************************************

                                                    Light.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Light.cpp#10 $

    $NoKeywords: $

 *********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Light.h"

#include "D3d.h"

namespace Dxx
{
/*==================================================================================================================*/

/*													L I G H T														*/

/*==================================================================================================================*/

D3DLIGHT9 const Light::defaultLightingParameters_ =
{
    D3DLIGHT_DIRECTIONAL,       // Type
    { 1.f, 1.f, 1.f, 0.f },     // Diffuse
    { 0.f, 0.f, 0.f, 0.f },     // Specular
    { 0.f, 0.f, 0.f, 0.f },     // Ambient
    { 0.f, 0.f, 0.f },          // Position
    { 0.f, 0.f, 1.f },          // Direction
    0.f,                        // Range
    0.f,                        // Falloff
    0.f,                        // Attenuation0
    0.f,                        // Attenuation1
    0.f,                        // Attenuation2
    0.f,                        // Theta
    0.f                         // Phi
};

//! This constuctor initializes a light with the following lighting parameters.
//!		- Type				D3DLIGHT_DIRECTIONAL,
//!		- Diffuse			{ 1.f, 1.f, 1.f, 0.f }
//!		- Specular			{ 0.f, 0.f, 0.f, 0.f }
//!		- Ambient			{ 0.f, 0.f, 0.f, 0.f }
//!		- Position			{ 0.f, 0.f, 0.f }
//!		- Direction			{ 0.f, 0.f, 1.f }
//!		- Range				0.f
//!		- Falloff			0.f
//!		- Attenuation0		0.f
//!		- Attenuation1		0.f
//!		- Attenuation2		0.f
//!		- Theta				0.f
//!		- Phi				0.f
//!
//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//!
//! @exception	ConstructorFailedException	IDirect3DDevice9::SetLight failed

Light::Light(IDirect3DDevice9 * pD3dDevice, int id)
    : D3DLIGHT9(defaultLightingParameters_),
    pD3dDevice_(pD3dDevice),
    id_(id)

{
    HRESULT hr;

    pD3dDevice_->AddRef();

    // Tell D3D about this light

    hr = pD3dDevice_->SetLight(id_, this);
    if (FAILED(hr))
        throw ConstructorFailedException("IDirect3DDevice9::SetLight failed");
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	d3dLight	Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	IDirect3DDevice9::SetLight failed
//!
//! @note		See the docs for D3DLIGHT9 for restrictions on lighting parameter values.

Light::Light(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight)
    : D3DLIGHT9(d3dLight),
    pD3dDevice_(pD3dDevice),
    id_(id)
{
    HRESULT hr;

    pD3dDevice_->AddRef();

#if defined(_DEBUG)

    switch (d3dLight.Type)
    {
        case D3DLIGHT_POINT:
            assert(d3dLight.Range >= 0.f && d3dLight.Range <= sqrtf(FLT_MAX));
            assert(d3dLight.Attenuation0 != 0.f || d3dLight.Attenuation1 != 0.f || d3dLight.Attenuation2 != 0.f);
            break;

        case D3DLIGHT_DIRECTIONAL:
            assert(d3dLight.Direction.x != 0.f || d3dLight.Direction.y != 0.f || d3dLight.Direction.z != 0.f);
            break;

        case D3DLIGHT_SPOT:
            assert(d3dLight.Direction.x != 0.f || d3dLight.Direction.y != 0.f || d3dLight.Direction.z != 0.f);
            assert(d3dLight.Range >= 0.f && d3dLight.Range <= sqrtf(FLT_MAX));
            assert(d3dLight.Attenuation0 != 0.f || d3dLight.Attenuation1 != 0.f || d3dLight.Attenuation2 != 0.f);
            assert(d3dLight.Theta > 0.f && d3dLight.Theta <= d3dLight.Phi);
            assert(d3dLight.Phi > 0.f && d3dLight.Phi < D3DX_PI);
            break;

        default:
            assert(false);
    }

#endif  // defined( _DEBUG )

    // Tell D3D about this light

    hr = pD3dDevice_->SetLight(id_, this);
    if (FAILED(hr))
        throw ConstructorFailedException("IDirect3DDevice9::SetLight failed");
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	...			Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	IDirect3DDevice9::SetLight failed
//!
//! @note		See the docs for D3DLIGHT9 for restrictions on lighting parameter values.

Light::Light(IDirect3DDevice9 *    pD3dDevice,
             int                   id,
             D3DLIGHTTYPE          type,
             D3DCOLORVALUE const & diffuse,
             D3DCOLORVALUE const & specular,
             D3DCOLORVALUE const & ambient,
             D3DVECTOR const &     position,
             D3DVECTOR const &     direction,
             float                 range,
             float                 falloff,
             float                 attenuation0,
             float                 attenuation1,
             float                 attenuation2,
             float                 theta,
             float                 phi)
/*D3DLIGHT9(),*/ : pD3dDevice_(pD3dDevice),
    id_(id)
{
#if defined(_DEBUG)

    switch (type)
    {
        case D3DLIGHT_POINT:
            assert(range >= 0.f && range <= sqrtf(FLT_MAX));
            assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);
            break;

        case D3DLIGHT_DIRECTIONAL:
            assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);
            break;

        case D3DLIGHT_SPOT:
            assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);
            assert(range >= 0.f && range <= sqrtf(FLT_MAX));
            assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);
            assert(theta > 0.f && theta <= phi);
            assert(phi > 0.f && phi < D3DX_PI);
            break;

        default:
            assert(false);
    }

#endif  // defined( _DEBUG )

    HRESULT hr;

    pD3dDevice_->AddRef();

    // Set the values

    Type         = type;
    Diffuse      = diffuse;
    Specular     = specular;
    Ambient      = ambient;
    Position     = position;
    Direction    = direction;
    Range        = range;
    Falloff      = falloff;
    Attenuation0 = attenuation0;
    Attenuation1 = attenuation1;
    Attenuation2 = attenuation2;
    Theta        = theta;
    Phi          = phi;

    // Tell D3D about this light

    hr = pD3dDevice_->SetLight(id_, this);
    if (FAILED(hr))
        throw ConstructorFailedException("IDirect3DDevice9::SetLight failed");
}

Light::~Light()
{
    Wx::SafeRelease(pD3dDevice_);
}

Light::Light(Light const & src)
    : D3DLIGHT9(src),
    pD3dDevice_(src.pD3dDevice_),
    id_(src.id_)
{
    pD3dDevice_->AddRef();
}

Light & Light::operator =(Light const & rhs)
{
    if (this != &rhs)
    {
        D3DLIGHT9::operator =(rhs);

        Wx::SafeRelease(pD3dDevice_);

        pD3dDevice_ = rhs.pD3dDevice_;
        pD3dDevice_->AddRef();

        id_ = rhs.id_;
    }

    return *this;
}

//!
//! @param	all		Lighting parameters (See the docs for D3DLIGHT9)

HRESULT Light::SetPointValues(D3DCOLORVALUE const & diffuse,
                              D3DCOLORVALUE const & specular,
                              D3DCOLORVALUE const & ambient,
                              D3DVECTOR const &     position,
                              float                 range,
                              float                 attenuation0,
                              float                 attenuation1,
                              float                 attenuation2)
{
    assert(range >= 0.f && range <= sqrtf(FLT_MAX));
    assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);

    // Set the values

    Type         = D3DLIGHT_POINT;
    Diffuse      = diffuse;
    Specular     = specular;
    Ambient      = ambient;
    Position     = position;
    Range        = range;
    Attenuation0 = attenuation0;
    Attenuation1 = attenuation1;
    Attenuation2 = attenuation2;

    // Tell D3D about the new values

    return pD3dDevice_->SetLight(id_, this);
}

//!
//! @param	all		Lighting parameters (See the docs for D3DLIGHT9)

HRESULT Light::SetDirectionalValues(D3DCOLORVALUE const & diffuse,
                                    D3DCOLORVALUE const & specular,
                                    D3DCOLORVALUE const & ambient,
                                    D3DVECTOR const &     direction)
{
    assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);

    // Set the values

    Type      = D3DLIGHT_DIRECTIONAL;
    Diffuse   = diffuse;
    Specular  = specular;
    Ambient   = ambient;
    Direction = direction;

    // Tell D3D about the new values

    return pD3dDevice_->SetLight(id_, this);
}

//!
//! @param	all		Lighting parameters (See the docs for D3DLIGHT9)

HRESULT Light::SetSpotValues(D3DCOLORVALUE const & diffuse,
                             D3DCOLORVALUE const & specular,
                             D3DCOLORVALUE const & ambient,
                             D3DVECTOR const &     position,
                             D3DVECTOR const &     direction,
                             float                 range,
                             float                 falloff,
                             float                 attenuation0,
                             float                 attenuation1,
                             float                 attenuation2,
                             float                 theta,
                             float                 phi)
{
    assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);
    assert(range >= 0.f && range <= sqrtf(FLT_MAX));
    assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);
    assert(theta > 0.f && theta <= phi);
    assert(phi > 0.f && phi < D3DX_PI);

    // Set the values

    Type         = D3DLIGHT_SPOT;
    Diffuse      = diffuse;
    Specular     = specular;
    Ambient      = ambient;
    Position     = position;
    Direction    = direction;
    Range        = range;
    Falloff      = falloff;
    Attenuation0 = attenuation0;
    Attenuation1 = attenuation1;
    Attenuation2 = attenuation2;
    Theta        = theta;
    Phi          = phi;

    // Tell D3D about the new values

    return pD3dDevice_->SetLight(id_, this);
}

/*==================================================================================================================*/

/*											S W I S S   A R M Y   L I G H T											*/

/*==================================================================================================================*/

D3DLIGHT9 const SwissArmyLight::defaultLightingParameters_ =
{
    D3DLIGHT_DIRECTIONAL,       // Type
    { 1.f, 1.f, 1.f, 0.f },     // Diffuse
    { 0.f, 0.f, 0.f, 0.f },     // Specular
    { 0.f, 0.f, 0.f, 0.f },     // Ambient
    { 0.f, 0.f, 0.f },          // Position
    { 0.f, 0.f, 1.f },          // Direction
    0.f,                        // Range
    0.f,                        // Falloff
    0.f,                        // Attenuation0
    0.f,                        // Attenuation1
    0.f,                        // Attenuation2
    0.f,                        // Theta
    0.f                         // Phi
};

//! This constuctor initializes a light with the following lighting parameters.
//!		- Type				D3DLIGHT_DIRECTIONAL,
//!		- Diffuse			{ 1.f, 1.f, 1.f, 0.f }
//!		- Specular			{ 0.f, 0.f, 0.f, 0.f }
//!		- Ambient			{ 0.f, 0.f, 0.f, 0.f }
//!		- Position			{ 0.f, 0.f, 0.f }
//!		- Direction			{ 0.f, 0.f, 1.f }
//!		- Range				0.f
//!		- Falloff			0.f
//!		- Attenuation0		0.f
//!		- Attenuation1		0.f
//!		- Attenuation2		0.f
//!		- Theta				0.f
//!		- Phi				0.f
//!
//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//!
//! @exception	ConstructorFailedException	Light() failed

SwissArmyLight::SwissArmyLight(IDirect3DDevice9 * pD3dDevice, int id)
    : Light(pD3dDevice, id)

{
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	d3dLight	Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		See the docs for D3DLIGHT9 for restrictions on lighting parameter values.

SwissArmyLight::SwissArmyLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight)
    : Light(pD3dDevice, id, d3dLight)
{
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	...			Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		See the docs for D3DLIGHT9 for restrictions on lighting parameter values.

SwissArmyLight::SwissArmyLight(IDirect3DDevice9 *    pD3dDevice,
                               int                   id,
                               D3DLIGHTTYPE          type,
                               D3DCOLORVALUE const & diffuse,
                               D3DCOLORVALUE const & specular,
                               D3DCOLORVALUE const & ambient,
                               D3DVECTOR const &     position,
                               D3DVECTOR const &     direction,
                               float                 range,
                               float                 falloff,
                               float                 attenuation0,
                               float                 attenuation1,
                               float                 attenuation2,
                               float                 theta,
                               float                 phi)
    : Light(pD3dDevice, id, type,
            diffuse, specular, ambient,
            position, direction,
            range, falloff, attenuation0, attenuation1, attenuation2,
            theta, phi)
{
}

SwissArmyLight::~SwissArmyLight()
{
}

/*==================================================================================================================*/

/*												A M B I E N T   L I G H T											*/

/*==================================================================================================================*/

D3DLIGHT9 const AmbientLight::defaultLightingParameters_ =
{
    D3DLIGHT_DIRECTIONAL,       // Type (must be D3DLIGHT_DIRECTIONAL)
    { 0.f, 0.f, 0.f, 0.f },     // Diffuse (must be black)
    { 0.f, 0.f, 0.f, 0.f },     // Specular (must be black)
    { 1.f, 1.f, 1.f, 0.f },     // Ambient
    { 0.f, 0.f, 0.f },          // Position (ignored)
    { 0.f, 0.f, 1.f },          // Direction (ignored)
    0.f,                        // Range (ignored)
    0.f,                        // Falloff (ignored)
    0.f,                        // Attenuation0 (ignored)
    0.f,                        // Attenuation1 (ignored)
    0.f,                        // Attenuation2 (ignored)
    0.f,                        // Theta (ignored)
    0.f                         // Phi (ignored)
};

//! This constuctor initializes a light with the following lighting parameters.
//!		- Type				D3DLIGHT_DIRECTIONAL,
//!		- Diffuse			{ 0.f, 0.f, 0.f, 0.f },
//!		- Specular			{ 0.f, 0.f, 0.f, 0.f },
//!		- Ambient			{ 1.f, 1.f, 1.f, 0.f },
//!		- Position			{ 0.f, 0.f, 0.f },
//!		- Direction			{ 0.f, 0.f, 1.f },
//!		- Range				0.f,
//!		- Falloff			0.f,
//!		- Attenuation0		0.f,
//!		- Attenuation1		0.f,
//!		- Attenuation2		0.f,
//!		- Theta				0.f,
//!		- Phi				0.f
//!
//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//!
//! @exception	ConstructorFailedException	Light() failed

AmbientLight::AmbientLight(IDirect3DDevice9 * pD3dDevice, int id)
    : Light(pD3dDevice, id, defaultLightingParameters_)
{
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	ambient		Ambient color (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed

AmbientLight::AmbientLight(IDirect3DDevice9 *    pD3dDevice,
                           int                   id,
                           D3DCOLORVALUE const & ambient)
    : Light(pD3dDevice, id,
            D3DLIGHT_DIRECTIONAL,
            Dxx::NoColor(),
            Dxx::NoColor(),
            ambient,
            Dxx::Vector3Origin(),
            Dxx::Vector3ZAxis(),
            0.f,
            0.f,
            0.f, 0.f, 0.f,
            0.f, 0.f)
{
}

AmbientLight::~AmbientLight()
{
}

//!
//! @param	ambient		Ambient color (See the docs for D3DLIGHT9)

HRESULT AmbientLight::Set(D3DCOLORVALUE const & ambient)
{
    return SetAmbient(ambient);
}

/*==================================================================================================================*/

/*												P O I N T   L I G H T												*/

/*==================================================================================================================*/

D3DLIGHT9 const PointLight::defaultLightingParameters_ =
{
    D3DLIGHT_POINT,             // Type
    { 1.f, 1.f, 1.f, 0.f },     // Diffuse
    { 0.f, 0.f, 0.f, 0.f },     // Specular
    { 0.f, 0.f, 0.f, 0.f },     // Ambient
    { 0.f, 0.f, 0.f },          // Position
    { 0.f, 0.f, 1.f },          // Direction (ignored)
    sqrtf(FLT_MAX),             // Range
    0.f,                        // Falloff (ignored)
    1.f,                        // Attenuation0
    0.f,                        // Attenuation1
    0.f,                        // Attenuation2
    0.f,                        // Theta (ignored)
    0.f                         // Phi (ignored)
};

//! This constuctor initializes a light with the following lighting parameters.
//!		- Type				D3DLIGHT_POINT,
//!		- Diffuse			{ 1.f, 1.f, 1.f, 0.f }
//!		- Specular			{ 0.f, 0.f, 0.f, 0.f }
//!		- Ambient			{ 0.f, 0.f, 0.f, 0.f }
//!		- Position			{ 0.f, 0.f, 0.f }
//!		- Range				sqrtf( FLT_MAX )
//!		- Attenuation0		1.f
//!		- Attenuation1		0.f
//!		- Attenuation2		0.f
//!
//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//!
//! @exception	ConstructorFailedException	Light() failed

PointLight::PointLight(IDirect3DDevice9 * pD3dDevice, int id)
    : Light(pD3dDevice, id, defaultLightingParameters_)
{
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	d3dLight	Lighting parameters (Type @b must be @c D3DLIGHT_POINT)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		Requirements for point lights:
//!					- @c Type must be @c D3DLIGHT_POINT.
//!					- 0.f <= @c Range <= @c sqrt(FLT_MAX).
//!					- One of the @c Attenuation values must not be 0.

PointLight::PointLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight)
    : Light(pD3dDevice, id, d3dLight)
{
    // If the light's type is not D3DLIGHT_POINT, then there will be a problem.

    assert(d3dLight.Type == D3DLIGHT_POINT);
    assert(d3dLight.Range >= 0.f && d3dLight.Range <= sqrtf(FLT_MAX));
    assert(d3dLight.Attenuation0 != 0.f || d3dLight.Attenuation1 != 0.f || d3dLight.Attenuation2 != 0.f);
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	...			Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		Requirements for point lights:
//!					- 0.f <= @c Range <= @c sqrt(FLT_MAX).
//!					- One of the @c Attenuation values must not be 0.

PointLight::PointLight(IDirect3DDevice9 *    pD3dDevice,
                       int                   id,
                       D3DCOLORVALUE const & diffuse,
                       D3DCOLORVALUE const & specular,
                       D3DCOLORVALUE const & ambient,
                       D3DVECTOR const &     position,
                       float                 range,
                       float                 attenuation0,
                       float                 attenuation1,
                       float                 attenuation2)
    : Light(pD3dDevice, id,
            D3DLIGHT_POINT,
            diffuse, specular, ambient,
            position,
            Dxx::Vector3Origin(),
            range,
            0.f,
            attenuation0, attenuation1, attenuation2,
            0.f, 0.f)
{
    assert(range >= 0.f && range <= sqrtf(FLT_MAX));
    assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);
}

PointLight::~PointLight()
{
}

//!
//! @param	all		Lighting parameters (See the docs for D3DLIGHT9)

HRESULT PointLight::Set(D3DCOLORVALUE const & diffuse,
                        D3DCOLORVALUE const & specular,
                        D3DCOLORVALUE const & ambient,
                        D3DVECTOR const &     position,
                        float                 range,
                        float                 attenuation0,
                        float                 attenuation1,
                        float                 attenuation2)
{
    assert(range >= 0.f && range <= sqrtf(FLT_MAX));
    assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);

    return SetPointValues(diffuse, specular, ambient, position, range, attenuation0, attenuation1, attenuation2);
}

/*==================================================================================================================*/

/*										D I R E C T I O N A L   L I G H T											*/

/*==================================================================================================================*/

D3DLIGHT9 const DirectionalLight::defaultLightingParameters_ =
{
    D3DLIGHT_DIRECTIONAL,       // Type
    { 1.f, 1.f, 1.f, 0.f },     // Diffuse
    { 0.f, 0.f, 0.f, 0.f },     // Specular
    { 0.f, 0.f, 0.f, 0.f },     // Ambient
    { 0.f, 0.f, 0.f },          // Position (ignored)
    { 0.f, 0.f, 1.f },          // Direction
    0.f,                        // Range (ignored)
    0.f,                        // Falloff (ignored)
    0.f,                        // Attenuation0 (ignored)
    0.f,                        // Attenuation1 (ignored)
    0.f,                        // Attenuation2 (ignored)
    0.f,                        // Theta (ignored)
    0.f                         // Phi (ignored)
};

//! This constuctor initializes a light with the following lighting parameters.
//!		- Type				D3DLIGHT_DIRECTIONAL,
//!		- Diffuse			{ 1.f, 1.f, 1.f, 0.f }
//!		- Specular			{ 0.f, 0.f, 0.f, 0.f }
//!		- Ambient			{ 0.f, 0.f, 0.f, 0.f }
//!		- Direction			{ 0.f, 0.f, 1.f }
//!
//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//!
//! @exception	ConstructorFailedException	Light() failed

DirectionalLight::DirectionalLight(IDirect3DDevice9 * pD3dDevice, int id)
    : Light(pD3dDevice, id, defaultLightingParameters_)
{
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	d3dLight	Lighting parameters (Type @b must be @c D3DLIGHT_DIRECTIONAL)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		Requirements for directional lights:
//!					- @c Type must be @c D3DLIGHT_DIRECTIONAL.
//!					- @c Direction must not be (0, 0, 0).

DirectionalLight::DirectionalLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight)
    : Light(pD3dDevice, id, d3dLight)
{
    // If the light's type is not D3DLIGHT_DIRECTIONAL, then there will be a problem.

    assert(d3dLight.Type == D3DLIGHT_DIRECTIONAL);
    assert(d3dLight.Direction.x != 0.f || d3dLight.Direction.y != 0.f || d3dLight.Direction.z != 0.f);
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	...			Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		Requirements for directional lights:
//!					- @c Direction must not be (0, 0, 0).

DirectionalLight::DirectionalLight(IDirect3DDevice9 *    pD3dDevice,
                                   int                   id,
                                   D3DCOLORVALUE const & diffuse,
                                   D3DCOLORVALUE const & specular,
                                   D3DCOLORVALUE const & ambient,
                                   D3DVECTOR const &     direction)
    : Light(pD3dDevice, id,
            D3DLIGHT_DIRECTIONAL,
            diffuse, specular, ambient,
            Dxx::Vector3Origin(),
            direction,
            0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f)
{
    assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);
}

DirectionalLight::~DirectionalLight()
{
}

//!
//! @param	all		Lighting parameters (See the docs for D3DLIGHT9)

HRESULT DirectionalLight::Set(D3DCOLORVALUE const & diffuse,
                              D3DCOLORVALUE const & specular,
                              D3DCOLORVALUE const & ambient,
                              D3DVECTOR const &     direction)
{
    assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);

    return SetDirectionalValues(diffuse, specular, ambient, direction);
}

/*==================================================================================================================*/

/*												S P O T   L I G H T													*/

/*==================================================================================================================*/

D3DLIGHT9 const SpotLight::defaultLightingParameters_ =
{
    D3DLIGHT_SPOT,              // Type
    { 1.f, 1.f, 1.f, 0.f },     // Diffuse
    { 0.f, 0.f, 0.f, 0.f },     // Specular
    { 0.f, 0.f, 0.f, 0.f },     // Ambient
    { 0.f, 0.f, 0.f },          // Position
    { 0.f, 0.f, 1.f },          // Direction
    sqrtf(FLT_MAX),             // Range
    1.f,                        // Falloff
    1.f,                        // Attenuation0
    0.f,                        // Attenuation1
    0.f,                        // Attenuation2
    D3DX_PI / 2.f,                // Theta
    D3DX_PI / 2.f                 // Phi
};

//! This constuctor initializes a light with the following lighting parameters.
//!		- Type				D3DLIGHT_SPOT,
//!		- Diffuse			{ 1.f, 1.f, 1.f, 0.f },
//!		- Specular			{ 0.f, 0.f, 0.f, 0.f },
//!		- Ambient			{ 0.f, 0.f, 0.f, 0.f },
//!		- Position			{ 0.f, 0.f, 0.f },
//!		- Direction			{ 0.f, 0.f, 1.f },
//!		- Range				sqrtf( FLT_MAX ),
//!		- Falloff			1.f,
//!		- Attenuation0		1.f,
//!		- Attenuation1		0.f,
//!		- Attenuation2		0.f,
//!		- Theta				D3DX_PI,
//!		- Phi				D3DX_PI
//!
//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//!
//! @exception	ConstructorFailedException	Light() failed

SpotLight::SpotLight(IDirect3DDevice9 * pD3dDevice, int id)
    : Light(pD3dDevice, id, defaultLightingParameters_)
{
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	d3dLight	Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		Requirements for spot lights:
//!					- @c Type must be @c D3DLIGHT_SPOT.
//!					- @c Direction must not be (0, 0, 0).
//!					- 0.f <= @c Range <= @c sqrt(FLT_MAX).
//!					- One of the @c Attenuation values must not be 0.
//!					- 0.f < @c Theta <= @c Phi
//!					- 0.f < @c Phi < @c pi.

SpotLight::SpotLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight)
    : Light(pD3dDevice, id, d3dLight)
{
    assert(d3dLight.Type == D3DLIGHT_SPOT);
    assert(d3dLight.Direction.x != 0.f || d3dLight.Direction.y != 0.f || d3dLight.Direction.z != 0.f);
    assert(d3dLight.Range >= 0.f && d3dLight.Range <= sqrtf(FLT_MAX));
    assert(d3dLight.Attenuation0 != 0.f || d3dLight.Attenuation1 != 0.f || d3dLight.Attenuation2 != 0.f);
    assert(d3dLight.Theta > 0.f && d3dLight.Theta <= d3dLight.Phi);
    assert(d3dLight.Phi > 0.f && d3dLight.Phi < D3DX_PI);
}

//! @param	pD3dDevice	The D3D device this light that this light applies to
//! @param	id			An identifier for this light. Valid values are 0 to MaxActiveLights-1 (in D3DCAPS9)
//! @param	...			Lighting parameters (See the docs for D3DLIGHT9)
//!
//! @exception	ConstructorFailedException	Light() failed
//!
//! @note		Requirements for spot lights:
//!					- @c Direction must not be (0, 0, 0).
//!					- 0.f <= @c Range <= @c sqrt(FLT_MAX).
//!					- One of the @c Attenuation values must not be 0.
//!					- 0.f < @c Theta <= @c Phi
//!					- 0.f < @c Phi < @c pi.

SpotLight::SpotLight(IDirect3DDevice9 *    pD3dDevice,
                     int                   id,
                     D3DCOLORVALUE const & diffuse,
                     D3DCOLORVALUE const & specular,
                     D3DCOLORVALUE const & ambient,
                     D3DVECTOR const &     position,
                     D3DVECTOR const &     direction,
                     float                 range,
                     float                 falloff,
                     float                 attenuation0,
                     float                 attenuation1,
                     float                 attenuation2,
                     float                 theta,
                     float                 phi)
    : Light(pD3dDevice, id,
            D3DLIGHT_SPOT,
            diffuse, specular, ambient,
            position,
            direction,
            range,
            falloff,
            attenuation0, attenuation1, attenuation2,
            theta, phi)
{
    assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);
    assert(range >= 0.f && range <= sqrtf(FLT_MAX));
    assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);
    assert(theta > 0.f && theta <= phi);
    assert(phi > 0.f && phi < D3DX_PI);
}

SpotLight::~SpotLight()
{
}

//!
//! @param	all		Lighting parameters (See the docs for D3DLIGHT9)

HRESULT SpotLight::Set(D3DCOLORVALUE const & diffuse,
                       D3DCOLORVALUE const & specular,
                       D3DCOLORVALUE const & ambient,
                       D3DVECTOR const &     position,
                       D3DVECTOR const &     direction,
                       float                 range,
                       float                 falloff,
                       float                 attenuation0,
                       float                 attenuation1,
                       float                 attenuation2,
                       float                 theta,
                       float                 phi)
{
    assert(direction.x != 0.f || direction.y != 0.f || direction.z != 0.f);
    assert(range >= 0.f && range <= sqrtf(FLT_MAX));
    assert(attenuation0 != 0.f || attenuation1 != 0.f || attenuation2 != 0.f);
    assert(theta > 0.f && theta <= phi);
    assert(phi > 0.f && phi < D3DX_PI);

    return SetSpotValues(diffuse, specular, ambient,
                         position,
                         direction,
                         range,
                         falloff,
                         attenuation0, attenuation1, attenuation2,
                         theta, phi);
}
} // namespace Dxx
