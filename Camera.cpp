#include "Camera.h"

#include <d3d11.h>

using namespace DirectX;

namespace Dxx
{
//! @param	angleOfView		The angle between the bottom and top of the view frustum (in degrees).
//! @param	nearDistance	The distance to the near clipping plane.
//! @param	farDistance		The distance to the far clipping plane.
//! @param	aspectRatio		View window w / h
//! @param	position		The camera's location.
//! @param	orientation		The camera's orientation.

Camera::Camera(float            angleOfView,
               float            nearDistance,
               float            farDistance,
               float            aspectRatio,
               XMFLOAT3 const & position,
               XMFLOAT4 const & orientation /* = QuaternionIdentity()*/)
    : angleOfView_(MyMath::ToRadians(angleOfView))
    , nearDistance_(nearDistance)
    , farDistance_(farDistance)
    , frame_(position, orientation)
    , aspectRatio_(aspectRatio)
    , viewOffset_(0.0f, 0.0f)
{
    SyncInternalState();
}

//! @param	angleOfView		The angle between the bottom and top of the view frustum  (in degrees).
//! @param	nearDistance	The distance to the near clipping plane.
//! @param	farDistance		The distance to the far clipping plane.
//! @param	aspectRatio		View window w / h
//! @param	frame			The camera's frame of reference.

Camera::Camera(float         angleOfView,
               float         nearDistance,
               float         farDistance,
               float         aspectRatio,
               Frame const & frame /* = Frame::Identity()*/)
    : angleOfView_(MyMath::ToRadians(angleOfView))
    , nearDistance_(nearDistance)
    , farDistance_(farDistance)
    , frame_(frame)
    , aspectRatio_(aspectRatio)
    , viewOffset_(0.0f, 0.0f)
{
    SyncInternalState();
}

#if 0
void Camera::look() const
{
    HRESULT hr;

    hr = pDevice_->SetTransform(D3DTS_VIEW, &viewMatrix_);
    assert_succeeded(hr);
}

void Camera::reshape()
{
    HRESULT hr;

    hr = pDevice_->SetTransform(D3DTS_PROJECTION, &projectionMatrix_);
    assert_succeeded(hr);
}
#endif // if 0

XMFLOAT3 Camera::position() const
{
#if defined(_DEBUG)
    // Make sure that there is no scaling so we can simply extract the last row and avoid decomposition
    XMFLOAT3 const scale = frame_.scale();
    assert(MyMath::IsCloseTo(scale.x, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(MyMath::IsCloseTo(scale.y, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(MyMath::IsCloseTo(scale.z, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
#endif  // defined( _DEBUG )

    XMFLOAT4X4 frame = frame_.transformation();
    return { frame._41, frame._42, frame._43 };
}

XMFLOAT4 Camera::orientation() const
{
#if defined(_DEBUG)
    // Make sure that there is no scaling so we can simply extract the upper left 3x3 and avoid decomposition
    XMFLOAT3 const scale = frame_.scale();
    assert(MyMath::IsCloseTo(scale.x, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(MyMath::IsCloseTo(scale.y, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(MyMath::IsCloseTo(scale.z, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
#endif  // defined( _DEBUG )

    XMFLOAT4X4 frame = frame_.transformation();
    XMFLOAT3X3 r(frame._11, frame._12, frame._13, frame._21, frame._22, frame._23, frame._31, frame._32, frame._33);
    XMMATRIX   r_simd(XMLoadFloat3x3(&r));

    XMVECTOR q_simd(XMQuaternionRotationMatrix(r_simd));

    XMFLOAT4 q;
    XMStoreFloat4(&q, q_simd);
    return q;
}

void Camera::lookAt(XMFLOAT3 const & to, XMFLOAT3 const & from, XMFLOAT3 const & up)
{
    XMVECTOR to_simd(XMLoadFloat3(&from));
    XMVECTOR from_simd(XMLoadFloat3(&from));
    XMVECTOR up_simd(XMLoadFloat3(&from));
    XMMATRIX lookat_simd(XMMatrixLookAtLH(from_simd, to_simd, up_simd));

    XMFLOAT4X4 lookat;
    XMStoreFloat4x4(&lookat, lookat_simd);
    frame_.setTransformation(lookat);
    SyncInternalState();
}

//! @param	angle	Angle of rotation (in degrees)
//! @param	axis	Axis of rotation

void Camera::turn(float angle, XMFLOAT3 const & axis)
{
    XMVECTOR axis_simd(XMLoadFloat3(&axis));

    XMVECTOR q_simd = XMQuaternionRotationAxis(axis_simd, MyMath::ToRadians(angle));

    XMFLOAT4 q;
    XMStoreFloat4(&q, q_simd);
    turn(q);
}
void Camera::SyncViewMatrix()
{
// Yuck this is slow...there is a faster way
//
//	// Get the frame and invert it (because, in reality, the camera remains
//	// at the origin and the world is transformed).
//
//	XMFLOAT4X4	r;
//	D3DXMatrixInverse( r, NULL, frame_.GetTransformation() );

    // Rotate and translate
    //
    // Note the transformation is inverted (because, in reality, the camera remains at the origin and world space
    // is transformed). Also the inversion reverses the order of rotation and translation.

    // Get the rotation and invert it (by transposing).

#if defined(_DEBUG)

    // Make sure that there is no scaling so we don't have to worry about inverting being different from
    // transposing.

    XMFLOAT3 const scale = frame_.scale();
    assert(MyMath::IsCloseTo(scale.x, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(MyMath::IsCloseTo(scale.y, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(MyMath::IsCloseTo(scale.z, 1., MyMath::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));

#endif  // defined( _DEBUG )

    XMFLOAT4X4 frame = frame_.transformation();
    XMFLOAT3X3 r(frame._11, frame._12, frame._13, frame._21, frame._22, frame._23, frame._31, frame._32, frame._33);
    XMFLOAT3   t(frame._41, frame._42, frame._43);
    XMMATRIX   r_simd(XMLoadFloat3x3(&r));
    XMVECTOR   t_simd(XMLoadFloat3(&t));

    XMMATRIX ir_simd = XMMatrixTranspose(r_simd);
    XMMATRIX it_simd = XMMatrixTranslationFromVector(-t_simd);

    // Compute the view matrix
    XMMATRIX view_simd = it_simd * ir_simd;

    XMStoreFloat4x4(&viewMatrix_, view_simd);
}

void Camera::SyncProjectionMatrix()
{
    float const h = tanf(angleOfView_ * 0.5f) * nearDistance_;
    float const w = h * aspectRatio_;

    // Compute the projection matrix

    XMMATRIX projection_simd = XMMatrixPerspectiveOffCenterLH(viewOffset_.x - w,
                                                              viewOffset_.x + w,
                                                              viewOffset_.y - h,
                                                              viewOffset_.y + h,
                                                              nearDistance_, farDistance_);
    XMStoreFloat4x4(&projectionMatrix_, projection_simd);
}

//!
//! @note	This function should be called whenever any value is modified directly.

void Camera::SyncInternalState()
{
    // Sync the view matrix

    SyncViewMatrix();

    // Sync the projection matrix

    SyncProjectionMatrix();

    // Compute the view-projection matrix

    XMMATRIX view_simd(XMLoadFloat4x4(&viewMatrix_));
    XMMATRIX projection_simd(XMLoadFloat4x4(&projectionMatrix_));
    XMMATRIX viewProjection_simd = view_simd * projection_simd;

    XMStoreFloat4x4(&viewProjectionMatrix_, viewProjection_simd);

    // Compute the view frustum

    ComputeViewFrustum(viewProjectionMatrix_);
}

void Camera::ComputeViewFrustum(XMFLOAT4X4 const & m)
{
    viewFrustum_.sides_[Frustum::LEFT_SIDE]   = Plane(-m._14 - m._11, -m._24 - m._21, -m._34 - m._31, -m._44 - m._41);
    viewFrustum_.sides_[Frustum::RIGHT_SIDE]  = Plane(-m._14 + m._11, -m._24 + m._21, -m._34 + m._31, -m._44 + m._41);
    viewFrustum_.sides_[Frustum::TOP_SIDE]    = Plane(-m._14 + m._12, -m._24 + m._22, -m._34 + m._32, -m._44 + m._42);
    viewFrustum_.sides_[Frustum::BOTTOM_SIDE] = Plane(-m._14 - m._12, -m._24 - m._22, -m._34 - m._32, -m._44 - m._42);
    viewFrustum_.sides_[Frustum::FRONT_SIDE]  = Plane(-m._13,         -m._23,         -m._33,         -m._43);
    viewFrustum_.sides_[Frustum::BACK_SIDE]   = Plane(-m._14 + m._13, -m._24 + m._23, -m._34 + m._33, -m._44 + m._43);
}
} // namespace Dxx
