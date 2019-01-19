/** @file *//********************************************************************************************************

                                                      Frame.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Frame.cpp#9 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Frame.h"

namespace Dxx
{
//! @param	translation		Translation component.
//! @param	rotation		Rotation component.
//! @param	scale			Scale component.
//!
//! The frame's transformation is computed as M = S * R * T

Frame::Frame(DirectX::XMFLOAT4 const &    translation,
             DirectX::XMFLOAT4 const & rotation,
             DirectX::XMFLOAT4 const &    scale /* = DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f )*/)
{
    D3DXMatrixIdentity(&M_);
    Translate(translation);
    Rotate(rotation);
    Scale(scale);
}

//!
//! @param	t	translation (in local space)

Frame & Frame::Translate(DirectX::XMFLOAT4 const & t)
{
    // M' =  T * M
    M_._41 += t.x * M_._11 + t.y * M_._21 + t.z * M_._31;
    M_._42 += t.x * M_._12 + t.y * M_._22 + t.z * M_._32;
    M_._43 += t.x * M_._13 + t.y * M_._23 + t.z * M_._33;

    return *this;
}

//!
//! @param	r	rotation (in local space)

Frame & Frame::Rotate(DirectX::XMFLOAT4 const & r)
{
    // M' = R * M

    DirectX::XMFLOAT4X4 rm;
    D3DXMatrixRotationQuaternion(&rm, &r);

    D3DXMatrixMultiply(&M_, &rm, &M_);

    return *this;
}

//!
//! @param	s	scale (in local space)

Frame & Frame::Scale(DirectX::XMFLOAT4 const & s)
{
    assert(!Math::IsCloseToZero(s.x));
    assert(!Math::IsCloseToZero(s.y));
    assert(!Math::IsCloseToZero(s.z));

    // M' = S * M

    M_._11 *= s.x;
    M_._12 *= s.x;
    M_._13 *= s.x;

    M_._21 *= s.y;
    M_._22 *= s.y;
    M_._23 *= s.y;

    M_._31 *= s.z;
    M_._32 *= s.z;
    M_._33 *= s.z;

    return *this;
}

//!
//! @param	t	translation

void Frame::SetTranslation(DirectX::XMFLOAT4 const & t)
{
    *reinterpret_cast<DirectX::XMFLOAT4 *>(&M_._41) = t;
}

DirectX::XMFLOAT4 Frame::GetTranslation() const
{
    return *reinterpret_cast<DirectX::XMFLOAT4 const *>(&M_._41);
}

//!
//! @param	r	rotation

void Frame::SetOrientationMatrix(DirectX::XMFLOAT4X4 const & r)
{
    DirectX::XMFLOAT4 const s = GetScale();

    D3DXVec3Scale(reinterpret_cast<DirectX::XMFLOAT4 *>(&M_._11), reinterpret_cast<DirectX::XMFLOAT4 const *>(&r._11), s.x);
    D3DXVec3Scale(reinterpret_cast<DirectX::XMFLOAT4 *>(&M_._21), reinterpret_cast<DirectX::XMFLOAT4 const *>(&r._21), s.y);
    D3DXVec3Scale(reinterpret_cast<DirectX::XMFLOAT4 *>(&M_._31), reinterpret_cast<DirectX::XMFLOAT4 const *>(&r._31), s.z);
}

DirectX::XMFLOAT4X4 Frame::GetOrientationMatrix() const
{
    DirectX::XMFLOAT4 const s = GetScale();

    return DirectX::XMFLOAT4X4(M_._11 / s.x, M_._12 / s.x, M_._13 / s.x, 0.f,
                      M_._21 / s.y, M_._22 / s.y, M_._23 / s.y, 0.f,
                      M_._31 / s.z, M_._32 / s.z, M_._33 / s.z, 0.f,
                      0.f,           0.f,           0.f,           1.f);
}

//!
//! @param	s	scale

void Frame::SetScale(DirectX::XMFLOAT4 const & s)
{
    assert(!Math::IsCloseToZero(s.x));
    assert(!Math::IsCloseToZero(s.y));
    assert(!Math::IsCloseToZero(s.z));

    DirectX::XMFLOAT4 const s0 = GetScale();

    Scale(DirectX::XMFLOAT4(s.x / s0.x, s.y / s0.y, s.z / s0.z));
}

DirectX::XMFLOAT4 Frame::GetScale() const
{
    float const sx = D3DXVec3Length(reinterpret_cast<DirectX::XMFLOAT4 const *>(&M_._11));
    float const sy = D3DXVec3Length(reinterpret_cast<DirectX::XMFLOAT4 const *>(&M_._21));
    float const sz = D3DXVec3Length(reinterpret_cast<DirectX::XMFLOAT4 const *>(&M_._31));

    return DirectX::XMFLOAT4(sx, sy, sz);
}
} // namespace Dxx
