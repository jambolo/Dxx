/** @file *//********************************************************************************************************

                                                      Frame.inl

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Frame.inl#10 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Frame.h"

#include "Math/Math.h"

#include <cassert>
#include <DirectXMath.h>
#include <windows.h>

namespace Dxx
{
inline Frame::Frame()
{
    D3DXMatrixIdentity(&M_);
}

//!
//! @param	r	Orientation value.
inline void Frame::SetOrientation(DirectX::XMFLOAT4 const & r)
{
    D3DXMatrixRotationQuaternion(&M_, &r);
}

inline DirectX::XMFLOAT4 Frame::GetOrientation() const
{
    DirectX::XMFLOAT4X4     r = GetOrientationMatrix();
    DirectX::XMFLOAT4 q;

    D3DXQuaternionRotationMatrix(&q, &r);

    return q;
}

inline DirectX::XMFLOAT4X4 const & Frame::GetTransformationMatrix() const
{
    return M_;
}

//!
//! @param	m	Value to set the transformation matrix to.

inline void Frame::SetTransformationMatrix(DirectX::XMFLOAT4X4 const & m)
{
    // Make sure that none of the scales are 0

//	assert( !Math::IsCloseToZero( Vector3d( m._11, m._12, m._13 ).Length2() ) );
//	assert( !Math::IsCloseToZero( Vector3d( m._21, m._22, m._23 ).Length2() ) );
//	assert( !Math::IsCloseToZero( Vector3d( m._31, m._32, m._33 ).Length2() ) );
//	assert( m._13 == 0.f );
//	assert( m._23 == 0.f );
//	assert( m._33 == 0.f );
//	assert( m._43 == 1.f );

    M_ = m;
}

inline DirectX::XMFLOAT4 Frame::GetXAxis() const
{
    DirectX::XMFLOAT4 const axis = DirectX::XMFLOAT4(M_._11, M_._12, M_._13);
    DirectX::XMFLOAT4       x;

    D3DXVec3Normalize(&x, &axis);

    return x;
}

inline DirectX::XMFLOAT4 Frame::GetYAxis() const
{
    DirectX::XMFLOAT4 const axis = DirectX::XMFLOAT4(M_._21, M_._22, M_._23);
    DirectX::XMFLOAT4       y;

    D3DXVec3Normalize(&y, &axis);

    return y;
}

inline DirectX::XMFLOAT4 Frame::GetZAxis() const
{
    DirectX::XMFLOAT4 const axis = DirectX::XMFLOAT4(M_._31, M_._32, M_._33);
    DirectX::XMFLOAT4       z;

    D3DXVec3Normalize(&z, &axis);

    return z;
}

inline Frame Frame::Identity()
{
    return Frame();
}
} // namespace Dxx
