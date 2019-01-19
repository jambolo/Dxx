/** @file *//********************************************************************************************************

                                                     Light.inl

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Light.inl#4 $

    $NoKeywords: $

 *********************************************************************************************************************/

#pragma once

#include "Light.h"

namespace Dxx
{
/*==================================================================================================================*/

/*													L I G H T														*/

/*==================================================================================================================*/

inline int Light::GetId() const
{
    return id_;
}

inline HRESULT Light::Enable()
{
    return pD3dDevice_->LightEnable(id_, TRUE);
}

inline HRESULT Light::Disable()
{
    return pD3dDevice_->LightEnable(id_, FALSE);
}

inline D3DLIGHTTYPE Light::GetType() const
{
    return Type;
}

//!
//! @param	diffuse		See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetDiffuse(D3DCOLORVALUE const & diffuse)
{
    Diffuse = diffuse;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline D3DCOLORVALUE const & Light::GetDiffuse() const
{
    return Diffuse;
}

//!
//! @param	specular	See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetSpecular(D3DCOLORVALUE const & specular)
{
    Specular = specular;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline D3DCOLORVALUE const & Light::GetSpecular() const
{
    return Specular;
}

//!
//! @param	ambient		See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetAmbient(D3DCOLORVALUE const & ambient)
{
    Ambient = ambient;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline D3DCOLORVALUE const & Light::GetAmbient() const
{
    return Ambient;
}

//!
//! @param	position	See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetPosition(DirectX::XMFLOAT4 const & position)
{
    Position = position;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline DirectX::XMFLOAT4 const & Light::GetPosition() const
{
    return Position;
}

//!
//! @param	direction	See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetDirection(DirectX::XMFLOAT4 const & direction)
{
    Direction = direction;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline DirectX::XMFLOAT4 const & Light::GetDirection() const
{
    return Direction;
}

//!
//! @param	range	See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetRange(float range)
{
    Range = range;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline float Light::GetRange() const
{
    return Range;
}

//!
//! @param	falloff		See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetFalloff(float falloff)
{
    Falloff = falloff;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline float Light::GetFalloff() const
{
    return Falloff;
}

//!
//! @param	a0,a1,a2	See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetAttenuation(float a0, float a1, float a2)
{
    Attenuation0 = a0;
    Attenuation1 = a1;
    Attenuation2 = a2;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

//!
//! @param	pA0,pA1,pA2		Locations to return the attenuation values. See the docs for D3DLIGHT9 for a description.

inline void Light::GetAttenuation(float * pA0, float * pA1, float * pA2) const
{
    *pA0 = Attenuation0;
    *pA1 = Attenuation1;
    *pA2 = Attenuation2;
}

//!
//! @param	theta	See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetTheta(float theta)
{
    Theta = theta;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline float Light::GetTheta() const
{
    return Theta;
}

//!
//! @param	phi		See the docs for D3DLIGHT9 for a description.

inline HRESULT Light::SetPhi(float phi)
{
    Phi = phi;

    // Tell D3D about the new value

    return pD3dDevice_->SetLight(id_, this);
}

inline float Light::GetPhi() const
{
    return Phi;
}

/*==================================================================================================================*/

/*											S W I S S   A R M Y   L I G H T											*/

/*==================================================================================================================*/

inline HRESULT SwissArmyLight::SetDiffuse(D3DCOLORVALUE const & diffuse)
{
    return Light::SetDiffuse(diffuse);
}

inline D3DCOLORVALUE const & SwissArmyLight::GetDiffuse() const
{
    return Light::GetDiffuse();
}

inline HRESULT SwissArmyLight::SetSpecular(D3DCOLORVALUE const & specular)
{
    return Light::SetSpecular(specular);
}

inline D3DCOLORVALUE const & SwissArmyLight::GetSpecular() const
{
    return Light::GetSpecular();
}

inline HRESULT SwissArmyLight::SetAmbient(D3DCOLORVALUE const & ambient)
{
    return Light::SetAmbient(ambient);
}

inline D3DCOLORVALUE const & SwissArmyLight::GetAmbient() const
{
    return Light::GetAmbient();
}

inline HRESULT SwissArmyLight::SetPosition(DirectX::XMFLOAT4 const & position)
{
    return Light::SetPosition(position);
}

inline DirectX::XMFLOAT4 const & SwissArmyLight::GetPosition() const
{
    return Light::GetPosition();
}

inline HRESULT SwissArmyLight::SetDirection(DirectX::XMFLOAT4 const & direction)
{
    return Light::SetDirection(direction);
}

inline DirectX::XMFLOAT4 const & SwissArmyLight::GetDirection() const
{
    return Light::GetDirection();
}

inline HRESULT SwissArmyLight::SetRange(float range)
{
    return Light::SetRange(range);
}

inline float SwissArmyLight::GetRange() const
{
    return Light::GetRange();
}

inline HRESULT SwissArmyLight::SetFalloff(float falloff)
{
    return Light::SetFalloff(falloff);
}

inline float SwissArmyLight::GetFalloff() const
{
    return Light::GetFalloff();
}

inline HRESULT SwissArmyLight::SetAttenuation(float a0, float a1, float a2)
{
    return Light::SetAttenuation(a0, a1, a2);
}

inline void SwissArmyLight::GetAttenuation(float * pA0, float * pA1, float * pA2) const
{
    return Light::GetAttenuation(pA0, pA1, pA2);
}

inline HRESULT SwissArmyLight::SetTheta(float theta)
{
    return Light::SetTheta(theta);
}

inline float SwissArmyLight::GetTheta() const
{
    return Light::GetTheta();
}

inline HRESULT SwissArmyLight::SetPhi(float phi)
{
    return Light::SetPhi(phi);
}

inline float SwissArmyLight::GetPhi() const
{
    return Light::GetPhi();
}

/*==================================================================================================================*/

/*											A M B I E N T   L I G H T												*/

/*==================================================================================================================*/

inline HRESULT AmbientLight::SetAmbient(D3DCOLORVALUE const & ambient)
{
    return Light::SetAmbient(ambient);
}

inline D3DCOLORVALUE const & AmbientLight::GetAmbient() const
{
    return Light::GetAmbient();
}

/*==================================================================================================================*/

/*												P O I N T   L I G H T												*/

/*==================================================================================================================*/

inline HRESULT PointLight::SetDiffuse(D3DCOLORVALUE const & diffuse)
{
    return Light::SetDiffuse(diffuse);
}

inline D3DCOLORVALUE const & PointLight::GetDiffuse() const
{
    return Light::GetDiffuse();
}

inline HRESULT PointLight::SetSpecular(D3DCOLORVALUE const & specular)
{
    return Light::SetSpecular(specular);
}

inline D3DCOLORVALUE const & PointLight::GetSpecular() const
{
    return Light::GetSpecular();
}

inline HRESULT PointLight::SetAmbient(D3DCOLORVALUE const & ambient)
{
    return Light::SetAmbient(ambient);
}

inline D3DCOLORVALUE const & PointLight::GetAmbient() const
{
    return Light::GetAmbient();
}

inline HRESULT PointLight::SetPosition(DirectX::XMFLOAT4 const & position)
{
    return Light::SetPosition(position);
}

inline DirectX::XMFLOAT4 const & PointLight::GetPosition() const
{
    return Light::GetPosition();
}

inline HRESULT PointLight::SetRange(float range)
{
    return Light::SetRange(range);
}

inline float PointLight::GetRange() const
{
    return Light::GetRange();
}

inline HRESULT PointLight::SetAttenuation(float a0, float a1, float a2)
{
    return Light::SetAttenuation(a0, a1, a2);
}

inline void PointLight::GetAttenuation(float * pA0, float * pA1, float * pA2) const
{
    return Light::GetAttenuation(pA0, pA1, pA2);
}

/*==================================================================================================================*/

/*										D I R E C T I O N A L   L I G H T											*/

/*==================================================================================================================*/

inline HRESULT DirectionalLight::SetDiffuse(D3DCOLORVALUE const & diffuse)
{
    return Light::SetDiffuse(diffuse);
}

inline D3DCOLORVALUE const & DirectionalLight::GetDiffuse() const
{
    return Light::GetDiffuse();
}

inline HRESULT DirectionalLight::SetSpecular(D3DCOLORVALUE const & specular)
{
    return Light::SetSpecular(specular);
}

inline D3DCOLORVALUE const & DirectionalLight::GetSpecular() const
{
    return Light::GetSpecular();
}

inline HRESULT DirectionalLight::SetAmbient(D3DCOLORVALUE const & ambient)
{
    return Light::SetAmbient(ambient);
}

inline D3DCOLORVALUE const & DirectionalLight::GetAmbient() const
{
    return Light::GetAmbient();
}

inline HRESULT DirectionalLight::SetDirection(DirectX::XMFLOAT4 const & direction)
{
    return Light::SetDirection(direction);
}

inline DirectX::XMFLOAT4 const & DirectionalLight::GetDirection() const
{
    return Light::GetDirection();
}

/*==================================================================================================================*/

/*												S P O T   L I G H T													*/

/*==================================================================================================================*/

inline HRESULT SpotLight::SetDiffuse(D3DCOLORVALUE const & diffuse)
{
    return Light::SetDiffuse(diffuse);
}

inline D3DCOLORVALUE const & SpotLight::GetDiffuse() const
{
    return Light::GetDiffuse();
}

inline HRESULT SpotLight::SetSpecular(D3DCOLORVALUE const & specular)
{
    return Light::SetSpecular(specular);
}

inline D3DCOLORVALUE const & SpotLight::GetSpecular() const
{
    return Light::GetSpecular();
}

inline HRESULT SpotLight::SetAmbient(D3DCOLORVALUE const & ambient)
{
    return Light::SetAmbient(ambient);
}

inline D3DCOLORVALUE const & SpotLight::GetAmbient() const
{
    return Light::GetAmbient();
}

inline HRESULT SpotLight::SetPosition(DirectX::XMFLOAT4 const & position)
{
    return Light::SetPosition(position);
}

inline DirectX::XMFLOAT4 const & SpotLight::GetPosition() const
{
    return Light::GetPosition();
}

inline HRESULT SpotLight::SetDirection(DirectX::XMFLOAT4 const & direction)
{
    return Light::SetDirection(direction);
}

inline DirectX::XMFLOAT4 const & SpotLight::GetDirection() const
{
    return Light::GetDirection();
}

inline HRESULT SpotLight::SetRange(float range)
{
    return Light::SetRange(range);
}

inline float SpotLight::GetRange() const
{
    return Light::GetRange();
}

inline HRESULT SpotLight::SetFalloff(float falloff)
{
    return Light::SetFalloff(falloff);
}

inline float SpotLight::GetFalloff() const
{
    return Light::GetFalloff();
}

inline HRESULT SpotLight::SetAttenuation(float a0, float a1, float a2)
{
    return Light::SetAttenuation(a0, a1, a2);
}

inline void SpotLight::GetAttenuation(float * pA0, float * pA1, float * pA2) const
{
    return Light::GetAttenuation(pA0, pA1, pA2);
}

inline HRESULT SpotLight::SetTheta(float theta)
{
    return Light::SetTheta(theta);
}

inline float SpotLight::GetTheta() const
{
    return Light::GetTheta();
}

inline HRESULT SpotLight::SetPhi(float phi)
{
    return Light::SetPhi(phi);
}

inline float SpotLight::GetPhi() const
{
    return Light::GetPhi();
}
} // namespace Dxx
