#include "Frame.h"

#include "MyMath/MyMath.h"

#include <cassert>

using namespace DirectX;

namespace Dxx
{
//! The frame's transformation is computed as M = S * R * T
//!
//! @param	translation		Translation component as a 3D vector
//! @param	rotation		Rotation component as a quaternion
//! @param	scale			Scale component as a 3D vector

Frame::Frame(XMFLOAT3 const & translation,
             XMFLOAT4 const & rotation,
             XMFLOAT3 const & scale /* = XMFLOAT3( 1.0f, 1.0f, 1.0f )*/)
{
    XMVECTORF32 q_simd{ rotation.x, rotation.y, rotation.z, rotation.w };
    XMMATRIX    t_simd = XMMatrixTranslation(translation.x, translation.y, translation.z);
    XMMATRIX    r_simd = XMMatrixRotationQuaternion(q_simd);
    XMMATRIX    s_simd = XMMatrixScaling(scale.x, scale.y, scale.z);

    XMMATRIX m_simd = s_simd * r_simd * t_simd;

    XMStoreFloat4x4(&m_, m_simd);
}

//! M' =  T * M
//!
//! @param	t	translation (in local space)

Frame & Frame::translate(XMFLOAT3 const & t)
{
    XMMATRIX m_simd = XMLoadFloat4x4(&m_);
    XMMATRIX t_simd = XMMatrixTranslation(t.x, t.y, t.z);

    m_simd = t_simd * m_simd;

    XMStoreFloat4x4(&m_, m_simd);

    return *this;
}

//! M' = R * M
//!
//! @param	r	rotation (in local space)

Frame & Frame::rotate(XMFLOAT4 const & r)
{
    XMMATRIX    m_simd = XMLoadFloat4x4(&m_);
    XMVECTORF32 q_simd{ r.x, r.y, r.z, r.w };

    XMMATRIX r_simd = XMMatrixRotationQuaternion(q_simd);
    m_simd = r_simd * m_simd;

    XMStoreFloat4x4(&m_, m_simd);

    return *this;
}

//! M' = S * M
//!
//! @param	s	scale (in local space)

Frame & Frame::scale(XMFLOAT3 const & s)
{
    assert(!MyMath::IsCloseToZero(s.x));
    assert(!MyMath::IsCloseToZero(s.y));
    assert(!MyMath::IsCloseToZero(s.z));

    XMMATRIX m_simd = XMLoadFloat4x4(&m_);
    XMMATRIX s_simd = XMMatrixScaling(s.x, s.y, s.z);

    m_simd = s_simd * m_simd;

    XMStoreFloat4x4(&m_, m_simd);

    return *this;
}

//!
//! @param	t	translation

void Frame::setTranslation(XMFLOAT3 const & t)
{
    XMVECTOR t_simd(XMLoadFloat3(&t));
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR r_simd;
    XMVECTOR old_t_simd;
    XMMatrixDecompose(&s_simd, &r_simd, &old_t_simd, m_simd);

    // Replace translation
    m_simd = XMMatrixScalingFromVector(s_simd) * XMMatrixRotationQuaternion(r_simd) * XMMatrixTranslationFromVector(t_simd);

    XMStoreFloat4x4(&m_, m_simd);
}

XMFLOAT3 Frame::translation() const
{
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR q_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&s_simd, &q_simd, &t_simd, m_simd);

    XMFLOAT3 t;
    XMStoreFloat3(&t, t_simd);
    return t;
}

//!
//! @param	r	rotation

void Frame::setOrientation(XMFLOAT3X3 const & r)
{
    XMMATRIX r_simd(XMLoadFloat3x3(&r));
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR old_r_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&s_simd, &old_r_simd, &t_simd, m_simd);

    // Replace rotation
    m_simd = XMMatrixScalingFromVector(s_simd) * r_simd * XMMatrixTranslationFromVector(t_simd);

    XMStoreFloat4x4(&m_, m_simd);
}

//!
//! @param	r	Orientation value.

inline void Frame::setOrientation(XMFLOAT4 const & r)
{
    XMVECTOR r_simd(XMLoadFloat4(&r));
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR old_r_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&s_simd, &old_r_simd, &t_simd, m_simd);

    // Replace rotation
    m_simd = XMMatrixScalingFromVector(s_simd) * XMMatrixRotationQuaternion(r_simd) * XMMatrixTranslationFromVector(t_simd);

    XMStoreFloat4x4(&m_, m_simd);
}

inline XMFLOAT4 Frame::orientation() const
{
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR r_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&s_simd, &r_simd, &t_simd, m_simd);

    XMFLOAT4 r;
    XMStoreFloat4(&r, r_simd);
    return r;
}

XMFLOAT3X3 Frame::orientationMatrix() const
{
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR q_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&s_simd, &q_simd, &t_simd, m_simd);
    XMMATRIX r_simd = XMMatrixRotationQuaternion(q_simd);

    XMFLOAT3X3 r;
    XMStoreFloat3x3(&r, r_simd);
    return r;
}

//!
//! @param	s	scale

void Frame::setScale(XMFLOAT3 const & s)
{
    assert(!MyMath::IsCloseToZero(s.x));
    assert(!MyMath::IsCloseToZero(s.y));
    assert(!MyMath::IsCloseToZero(s.z));

    XMVECTOR s_simd(XMLoadFloat3(&s));
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR old_s_simd;
    XMVECTOR r_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&old_s_simd, &r_simd, &t_simd, m_simd);

    // Replace scale
    m_simd = XMMatrixScalingFromVector(s_simd) * XMMatrixRotationQuaternion(r_simd) * XMMatrixTranslationFromVector(t_simd);

    XMStoreFloat4x4(&m_, m_simd);
}

XMFLOAT3 Frame::scale() const
{
    XMMATRIX m_simd(XMLoadFloat4x4(&m_));

    XMVECTOR s_simd;
    XMVECTOR r_simd;
    XMVECTOR t_simd;
    XMMatrixDecompose(&s_simd, &r_simd, &t_simd, m_simd);

    XMFLOAT3 s;
    XMStoreFloat3(&s, s_simd);
    return s;
}

inline XMFLOAT4X4 Frame::transformation() const
{
    return m_;
}

//!
//! @param	m	Value to set the transformation matrix to.

inline void Frame::setTransformation(XMFLOAT4X4 const & m)
{
    // Make sure that none of the scales are 0

    //	assert( !Math::IsCloseToZero( Vector3d( m._11, m._12, m._13 ).Length2() ) );
    //	assert( !Math::IsCloseToZero( Vector3d( m._21, m._22, m._23 ).Length2() ) );
    //	assert( !Math::IsCloseToZero( Vector3d( m._31, m._32, m._33 ).Length2() ) );
    //	assert( m._13 == 0.f );
    //	assert( m._23 == 0.f );
    //	assert( m._33 == 0.f );
    //	assert( m._43 == 1.f );

    m_ = m;
}

inline XMFLOAT3 Frame::xAxis() const
{
    XMVECTORF32 v_simd{ m_._11, m_._12, m_._13, 1.0f };

    XMVECTOR axis_simd = XMVector3Normalize(v_simd);

    XMFLOAT4 axis;
    XMStoreFloat4(&axis, axis_simd);
    return { axis.x, axis.y, axis.z };
}

inline XMFLOAT3 Frame::yAxis() const
{
    XMVECTORF32 v_simd{ m_._21, m_._22, m_._23, 1.0f };

    XMVECTOR axis_simd = XMVector3Normalize(v_simd);

    XMFLOAT4 axis;
    XMStoreFloat4(&axis, axis_simd);
    return { axis.x, axis.y, axis.z };
}

inline XMFLOAT3 Frame::zAxis() const
{
    XMVECTORF32 v_simd{ m_._31, m_._32, m_._33, 1.0f };

    XMVECTOR axis_simd = XMVector3Normalize(v_simd);

    XMFLOAT4 axis;
    XMStoreFloat4(&axis, axis_simd);
    return { axis.x, axis.y, axis.z };
}
} // namespace Dxx
