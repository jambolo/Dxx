/** @file *//********************************************************************************************************

                                                     Light.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Light.h#11 $

    $NoKeywords: $

 *********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3d9types.h>

//! @defgroup Lights	Light Types
//! Wrappers for D3D lights
//!
//! @ingroup D3dx

namespace Dxx
{
//! A base class for lights
//
//! @ingroup Lights
//!
//! @note	The only way to change the type of the light is by calling SetD3dLight().

class Light : private D3DLIGHT9     // Note: private because changing values directly may lead to inconsistencies.
{
public:

    // Destructor
    virtual ~Light();

    // Copy constructor
    Light(Light const & src);

    // Assignment operator
    Light & operator =(Light const & rhs);

    //! Returns the light's ID.
    int GetId() const;

    //! Enables the light. Returns an HRESULT (See the docs for IDirect3DDevice::LightEnable()).
    HRESULT Enable();

    //! Disables the light. Returns an HRESULT (See the docs for IDirect3DDevice::LightEnable()).
    HRESULT Disable();

    //! Returns the light type
    D3DLIGHTTYPE GetType() const;

protected:

    //! Constructor
    Light(IDirect3DDevice9 * pD3dDevice, int id);

    //! Constructor
    Light(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight);

    Light(IDirect3DDevice9 *    pD3dDevice,
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
          float                 phi);

    //! Sets the diffuse color. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetDiffuse(D3DCOLORVALUE const & diffuse);

    //! Returns the diffuse color.
    D3DCOLORVALUE const & GetDiffuse() const;

    //! Sets the specular color. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetSpecular(D3DCOLORVALUE const & specular);

    //! Returns the specular color.
    D3DCOLORVALUE const & GetSpecular() const;

    //! Sets the ambient color. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetAmbient(D3DCOLORVALUE const & ambient);

    //! Returns the ambient color
    D3DCOLORVALUE const & GetAmbient() const;

    //! Sets the light's position. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetPosition(D3DVECTOR const & position);

    //! Returns the light's position
    D3DVECTOR const & GetPosition() const;

    //! Sets the light's direction. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetDirection(D3DVECTOR const & direction);

    //! Returns the light's direction
    D3DVECTOR const & GetDirection() const;

    //! Sets the range value. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetRange(float range);

    //! Returns the range value
    float GetRange() const;

    //! Sets the falloff value. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetFalloff(float falloff);

    //! Returns the falloff value
    float GetFalloff() const;

    //! Sets the attenuation value. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetAttenuation(float a0, float a1, float a2);

    //! Returns the attenuation values
    void GetAttenuation(float * pA0, float * pA1, float * pA2) const;

    //! Sets the theta value. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetTheta(float theta);

    //! Returns the theta value
    float GetTheta() const;

    //! Sets the phi value. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetPhi(float phi);

    //! Returns the phi value
    float GetPhi() const;

    //! Sets the D3D light data. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetD3dLight(D3DLIGHT9 const & d3dLight);

    //! Returns the D3D light data
    D3DLIGHT9 const & GetD3dLight() const;

    //! Sets the values specific to point lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetPointValues(D3DCOLORVALUE const & diffuse,
                           D3DCOLORVALUE const & specular,
                           D3DCOLORVALUE const & ambient,
                           D3DVECTOR const &     position,
                           float                 range,
                           float                 attenuation0,
                           float                 attenuation1,
                           float                 attenuation2);

    //! Sets the values specific to directional lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetDirectionalValues(D3DCOLORVALUE const & diffuse,
                                 D3DCOLORVALUE const & specular,
                                 D3DCOLORVALUE const & ambient,
                                 D3DVECTOR const &     direction);

    //! Sets the values specific to spot lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT SetSpotValues(D3DCOLORVALUE const & diffuse,
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
                          float                 phi);

private:

    IDirect3DDevice9 * pD3dDevice_;                         // The D3D device the light is associated with
    int id_;                                                // Light Id

    static D3DLIGHT9 const defaultLightingParameters_;  // Default lighting parameters (same as D3D)
};

//! A generic light
//
//! @ingroup Lights
//!
//! You can use this class for any kind of light but you might want to use the subclasses for specific light types
//! instead. Their interfaces are specific to the type of light.
//!
//! @note	The only way to change the type of the light is by calling SetD3dLight().

class SwissArmyLight : public Light
{
public:

    //! Constructor
    SwissArmyLight(IDirect3DDevice9 * pD3dDevice, int id);

    //! Constructor
    SwissArmyLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight);

    //! Constructor
    SwissArmyLight(IDirect3DDevice9 *    pD3dDevice,
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
                   float                 phi);

    //! Destructor
    virtual ~SwissArmyLight();

    //! @name Overrides Light
    //@{
    //	int GetId() const;
    //	HRESULT Enable();
    //	HRESULT Disable();
    //	D3DLIGHTTYPE GetType() const;
    HRESULT               SetDiffuse(D3DCOLORVALUE const & diffuse);
    D3DCOLORVALUE const & GetDiffuse() const;
    HRESULT               SetSpecular(D3DCOLORVALUE const & specular);
    D3DCOLORVALUE const & GetSpecular() const;
    HRESULT               SetAmbient(D3DCOLORVALUE const & ambient);
    D3DCOLORVALUE const & GetAmbient() const;
    HRESULT               SetPosition(D3DVECTOR const & position);
    D3DVECTOR const &     GetPosition() const;
    HRESULT               SetDirection(D3DVECTOR const & direction);
    D3DVECTOR const &     GetDirection() const;
    HRESULT               SetRange(float range);
    float                 GetRange() const;
    HRESULT               SetFalloff(float falloff);
    float                 GetFalloff() const;
    HRESULT               SetAttenuation(float a0, float a1, float a2);
    void                  GetAttenuation(float * pA0, float * pA1, float * pA2) const;
    HRESULT               SetTheta(float theta);
    float                 GetTheta() const;
    HRESULT               SetPhi(float phi);
    float                 GetPhi() const;
    HRESULT               SetD3dLight(D3DLIGHT9 const & d3dLight);
    D3DLIGHT9 const &     GetD3dLight() const;
    //@}

private:

    static D3DLIGHT9 const defaultLightingParameters_;  // Default lighting parameters (same as D3D)
};

//! An ambient light
//
//! @ingroup Lights
//!
//! @note	All lights have an ambient component. This light is ambient only.

class AmbientLight : public Light
{
public:

    //! Constructor
    AmbientLight(IDirect3DDevice9 * pD3dDevice, int id);

    //! Constructor
    AmbientLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight);

    //! Constructor
    AmbientLight(IDirect3DDevice9 *    pD3dDevice,
                 int                   id,
                 D3DCOLORVALUE const & ambient);

    //! Destructor
    virtual ~AmbientLight();

    //! @name Overrides Light
    //@{
    //	int GetId() const;
    //	HRESULT Enable();
    //	HRESULT Disable();
    //	D3DLIGHTTYPE GetType() const;
    HRESULT               SetAmbient(D3DCOLORVALUE const & ambient);
    D3DCOLORVALUE const & GetAmbient() const;
    HRESULT               SetD3dLight(D3DLIGHT9 const & d3dLight);
    D3DLIGHT9 const &     GetD3dLight() const;
    //@}

    //! Sets the values specific to ambient lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT Set(D3DCOLORVALUE const & ambient);

private:

    static D3DLIGHT9 const defaultLightingParameters_;  //!< Default lighting parameters
};

//! A point light
//
//! @ingroup Lights
//!

class PointLight : public Light
{
public:

    //! Constructor
    PointLight(IDirect3DDevice9 * pD3dDevice, int id);

    //! Constructor
    PointLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight);

    //! Constructor
    PointLight(IDirect3DDevice9 *    pD3dDevice,
               int                   id,
               D3DCOLORVALUE const & diffuse,
               D3DCOLORVALUE const & specular,
               D3DCOLORVALUE const & ambient,
               D3DVECTOR const &     position,
               float                 range,
               float                 attenuation0,
               float                 attenuation1,
               float                 attenuation2);

    //! Destructor
    virtual ~PointLight();

    //! @name Overrides Light
    //@{
    //	int GetId() const;
    //	HRESULT Enable();
    //	HRESULT Disable();
    //	D3DLIGHTTYPE GetType() const;
    HRESULT               SetDiffuse(D3DCOLORVALUE const & diffuse);
    D3DCOLORVALUE const & GetDiffuse() const;
    HRESULT               SetSpecular(D3DCOLORVALUE const & specular);
    D3DCOLORVALUE const & GetSpecular() const;
    HRESULT               SetAmbient(D3DCOLORVALUE const & ambient);
    D3DCOLORVALUE const & GetAmbient() const;
    HRESULT               SetPosition(D3DVECTOR const & position);
    D3DVECTOR const &     GetPosition() const;
    HRESULT               SetRange(float range);
    float                 GetRange() const;
    HRESULT               SetAttenuation(float a0, float a1, float a2);
    void                  GetAttenuation(float * pA0, float * pA1, float * pA2) const;
    HRESULT               SetD3dLight(D3DLIGHT9 const & d3dLight);
    D3DLIGHT9 const &     GetD3dLight() const;
    //@}

    //! Sets the values specific to point lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT Set(D3DCOLORVALUE const & diffuse,
                D3DCOLORVALUE const & specular,
                D3DCOLORVALUE const & ambient,
                D3DVECTOR const &     position,
                float                 range,
                float                 attenuation0,
                float                 attenuation1,
                float                 attenuation2);

private:

    static D3DLIGHT9 const defaultLightingParameters_;  //!< Default lighting parameters
};

//! A directional light
//
//! @ingroup Lights
//!

class DirectionalLight : public Light
{
public:

    //! Constructor
    DirectionalLight(IDirect3DDevice9 * pD3dDevice, int id);

    //! Constructor
    DirectionalLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight);

    //! Constructor
    DirectionalLight(IDirect3DDevice9 *    pD3dDevice,
                     int                   id,
                     D3DCOLORVALUE const & diffuse,
                     D3DCOLORVALUE const & specular,
                     D3DCOLORVALUE const & ambient,
                     D3DVECTOR const &     direction);

    //! Destructor
    virtual ~DirectionalLight();

    //! @name Overrides Light
    //@{
    //	int GetId() const;
    //	HRESULT Enable();
    //	HRESULT Disable();
    //	D3DLIGHTTYPE GetType() const;
    HRESULT               SetDiffuse(D3DCOLORVALUE const & diffuse);
    D3DCOLORVALUE const & GetDiffuse() const;
    HRESULT               SetSpecular(D3DCOLORVALUE const & specular);
    D3DCOLORVALUE const & GetSpecular() const;
    HRESULT               SetAmbient(D3DCOLORVALUE const & ambient);
    D3DCOLORVALUE const & GetAmbient() const;
    HRESULT               SetDirection(D3DVECTOR const & direction);
    D3DVECTOR const &     GetDirection() const;
    HRESULT               SetD3dLight(D3DLIGHT9 const & d3dLight);
    D3DLIGHT9 const &     GetD3dLight() const;
    //@}

    //! Sets the values specific to directional lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT Set(D3DCOLORVALUE const & diffuse,
                D3DCOLORVALUE const & specular,
                D3DCOLORVALUE const & ambient,
                D3DVECTOR const &     direction);

private:

    static D3DLIGHT9 const defaultLightingParameters_;  //!< Default lighting parameters
};

//! A spot light
//
//! @ingroup Lights
//!

class SpotLight : public Light
{
public:

    //! Constructor
    SpotLight(IDirect3DDevice9 * pD3dDevice, int id);

    //! Constructor
    SpotLight(IDirect3DDevice9 * pD3dDevice, int id, D3DLIGHT9 const & d3dLight);

    //! Constructor
    SpotLight(IDirect3DDevice9 *    pD3dDevice,
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
              float                 phi);

    //! Destructor
    virtual ~SpotLight();

    //! @name Overrides Light
    //@{
    //	int GetId() const;
    //	HRESULT Enable();
    //	HRESULT Disable();
    //	D3DLIGHTTYPE GetType() const;
    HRESULT               SetDiffuse(D3DCOLORVALUE const & diffuse);
    D3DCOLORVALUE const & GetDiffuse() const;
    HRESULT               SetSpecular(D3DCOLORVALUE const & specular);
    D3DCOLORVALUE const & GetSpecular() const;
    HRESULT               SetAmbient(D3DCOLORVALUE const & ambient);
    D3DCOLORVALUE const & GetAmbient() const;
    HRESULT               SetPosition(D3DVECTOR const & position);
    D3DVECTOR const &     GetPosition() const;
    HRESULT               SetDirection(D3DVECTOR const & direction);
    D3DVECTOR const &     GetDirection() const;
    HRESULT               SetRange(float range);
    float                 GetRange() const;
    HRESULT               SetFalloff(float falloff);
    float                 GetFalloff() const;
    HRESULT               SetAttenuation(float a0, float a1, float a2);
    void                  GetAttenuation(float * pA0, float * pA1, float * pA2) const;
    HRESULT               SetTheta(float theta);
    float                 GetTheta() const;
    HRESULT               SetPhi(float phi);
    float                 GetPhi() const;
    HRESULT               SetD3dLight(D3DLIGHT9 const & d3dLight);
    D3DLIGHT9 const &     GetD3dLight() const;
    //@}

    //! Sets the values specific to spot lights. Returns an HRESULT (See the docs for IDirect3DDevice::SetLight()).
    HRESULT Set(D3DCOLORVALUE const & diffuse,
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
                float                 phi);

private:

    static D3DLIGHT9 const defaultLightingParameters_;  //!< Default lighting parameters
};
} // namespace Dxx

#include "Light.inl"
