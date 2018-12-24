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
#include <d3dx9math.h>
#include <windows.h>

namespace Dxx
{
inline Frame::Frame()
{
    D3DXMatrixIdentity(&M_);
}

//!
//! @param	r	Orientation value.
inline void Frame::SetOrientation(D3DXQUATERNION const & r)
{
    D3DXMatrixRotationQuaternion(&M_, &r);
}

inline D3DXQUATERNION Frame::GetOrientation() const
{
    D3DXMATRIX     r = GetOrientationMatrix();
    D3DXQUATERNION q;

    D3DXQuaternionRotationMatrix(&q, &r);

    return q;
}

inline D3DXMATRIX const & Frame::GetTransformationMatrix() const
{
    return M_;
}

//!
//! @param	m	Value to set the transformation matrix to.

inline void Frame::SetTransformationMatrix(D3DXMATRIX const & m)
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

inline D3DXVECTOR3 Frame::GetXAxis() const
{
    D3DXVECTOR3 const axis = D3DXVECTOR3(M_._11, M_._12, M_._13);
    D3DXVECTOR3       x;

    D3DXVec3Normalize(&x, &axis);

    return x;
}

inline D3DXVECTOR3 Frame::GetYAxis() const
{
    D3DXVECTOR3 const axis = D3DXVECTOR3(M_._21, M_._22, M_._23);
    D3DXVECTOR3       y;

    D3DXVec3Normalize(&y, &axis);

    return y;
}

inline D3DXVECTOR3 Frame::GetZAxis() const
{
    D3DXVECTOR3 const axis = D3DXVECTOR3(M_._31, M_._32, M_._33);
    D3DXVECTOR3       z;

    D3DXVec3Normalize(&z, &axis);

    return z;
}

inline Frame Frame::Identity()
{
    return Frame();
}
} // namespace Dxx
