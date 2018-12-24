/** @file *//********************************************************************************************************

                                                      Camera.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Camera.cpp#20 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Camera.h"

namespace Dxx
{
//! @param	pDevice			The D3D device.
//! @param	angleOfView		The angle between the bottom and top of the view frustum (in degrees).
//! @param	nearDistance	The distance to the near clipping plane.
//! @param	farDistance		The distance to the far clipping plane.
//! @param	aspectRatio		View window w / h
//! @param	position		The camera's location.
//! @param	orientation		The camera's orientation.

Camera::Camera(IDirect3DDevice9 *     pDevice,
               float                  angleOfView,
               float                  nearDistance,
               float                  farDistance,
               float                  aspectRatio,
               D3DXVECTOR3 const &    position,
               D3DXQUATERNION const & orientation /* = QuaternionIdentity()*/)
    : pDevice_(pDevice),
    angleOfView_(Math::ToRadians(angleOfView)),
    nearDistance_(nearDistance),
    farDistance_(farDistance),
    frame_(position, orientation),
    aspectRatio_(aspectRatio),
    viewOffset_(0.0f, 0.0f)
{
    pDevice_->AddRef();

    SyncInternalState();
}

//! @param	pDevice			The D3D device.
//! @param	angleOfView		The angle between the bottom and top of the view frustum  (in degrees).
//! @param	nearDistance	The distance to the near clipping plane.
//! @param	farDistance		The distance to the far clipping plane.
//! @param	aspectRatio		View window w / h
//! @param	frame			The camera's frame of reference.

Camera::Camera(IDirect3DDevice9 * pDevice,
               float              angleOfView,
               float              nearDistance,
               float              farDistance,
               float              aspectRatio,
               Frame const &      frame /* = Frame::Identity()*/)
    : pDevice_(pDevice),
    angleOfView_(Math::ToRadians(angleOfView)),
    nearDistance_(nearDistance),
    farDistance_(farDistance),
    frame_(frame),
    aspectRatio_(aspectRatio),
    viewOffset_(0.0f, 0.0f)
{
    pDevice_->AddRef();

    SyncInternalState();
}

Camera::~Camera()
{
    Wx::SafeRelease(pDevice_);
}

Camera::Camera(Camera const & src)
    : pDevice_(src.pDevice_),
    frame_(src.frame_),
    nearDistance_(src.nearDistance_),
    farDistance_(src.farDistance_),
    angleOfView_(src.angleOfView_),
    viewOffset_(src.viewOffset_),
    aspectRatio_(src.aspectRatio_),
    viewMatrix_(src.viewMatrix_),
    projectionMatrix_(src.projectionMatrix_),
    viewProjectionMatrix_(src.viewProjectionMatrix_),
    viewFrustum_(src.viewFrustum_)
{
    pDevice_->AddRef();
}

Camera & Camera::operator =(Camera const & rhs)
{
    if (this != &rhs)
    {
        Wx::SafeRelease(pDevice_);

        pDevice_ = rhs.pDevice_;
        pDevice_->AddRef();

        frame_                = rhs.frame_;
        nearDistance_         = rhs.nearDistance_;
        farDistance_          = rhs.farDistance_;
        angleOfView_          = rhs.angleOfView_;
        viewOffset_           = rhs.viewOffset_;
        aspectRatio_          = rhs.aspectRatio_;
        viewMatrix_           = rhs.viewMatrix_;
        projectionMatrix_     = rhs.projectionMatrix_;
        viewProjectionMatrix_ = rhs.viewProjectionMatrix_;
        viewFrustum_          = rhs.viewFrustum_;
    }

    return *this;
}

void Camera::Look() const
{
    HRESULT hr;

    hr = pDevice_->SetTransform(D3DTS_VIEW, &viewMatrix_);
    assert_succeeded(hr);
}

void Camera::Reshape()
{
    HRESULT hr;

    hr = pDevice_->SetTransform(D3DTS_PROJECTION, &projectionMatrix_);
    assert_succeeded(hr);
}

void Camera::LookAt(D3DXVECTOR3 const & to, D3DXVECTOR3 const & from, D3DXVECTOR3 const & up)
{
    D3DXMATRIX lookat;
    D3DXMatrixLookAtLH(&lookat, &from, &to, &up);

    frame_.SetTransformationMatrix(lookat);
    SyncInternalState();
}

void Camera::SyncViewMatrix()
{
// Yuck this is slow...there is a faster way
//
//	// Get the frame and invert it (because, in reality, the camera remains
//	// at the origin and the world is transformed).
//
//	D3DXMATRIX	r;
//	D3DXMatrixInverse( r, NULL, frame_.GetTransformation() );

    // Rotate and translate
    //
    // Note the transformation is inverted (because, in reality, the camera remains at the origin and world space
    // is transformed). Also the inversion reverses the order of rotation and translation.

    // Get the rotation and invert it (by transposing).

#if defined(_DEBUG)

    // Make sure that there is no scaling so we don't have to worry about inverting being different from
    // transposing.

    D3DXVECTOR3 const scale = frame_.GetScale();
    assert(Math::IsCloseTo(scale.x, 1., Math::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(Math::IsCloseTo(scale.y, 1., Math::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));
    assert(Math::IsCloseTo(scale.z, 1., Math::DEFAULT_FLOAT_NORMALIZED_TOLERANCE));

#endif  // defined( _DEBUG )

    D3DXMATRIX const r = frame_.GetOrientationMatrix();
    D3DXMATRIX       ir;
    D3DXMatrixTranspose(&ir, &r);

    // Get the translation and invert it (by negating)

    D3DXMATRIX t;
    D3DXMatrixTranslation(&t, -frame_.GetTranslation().x,
                          -frame_.GetTranslation().y,
                          -frame_.GetTranslation().z);

    // Compute the view matrix

    D3DXMatrixMultiply(&viewMatrix_, &t, &ir);
}

void Camera::SyncProjectionMatrix()
{
    float const h = tanf(angleOfView_ * 0.5f) * nearDistance_;
    float const w = h * aspectRatio_;

    // Compute the projection matrix

    D3DXMatrixPerspectiveOffCenterLH(&projectionMatrix_,
                                     viewOffset_.x - w,
                                     viewOffset_.x + w,
                                     viewOffset_.y - h,
                                     viewOffset_.y + h,
                                     nearDistance_, farDistance_);
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

    D3DXMatrixMultiply(&viewProjectionMatrix_, &viewMatrix_, &projectionMatrix_);

    // Compute the view frustum

    ComputeViewFrustum(viewProjectionMatrix_);
}

void Camera::ComputeViewFrustum(D3DMATRIX const & m)
{
    viewFrustum_.sides_[Frustum::LEFT_SIDE]   = Plane(-m._14 - m._11, -m._24 - m._21, -m._34 - m._31, -m._44 - m._41);
    viewFrustum_.sides_[Frustum::RIGHT_SIDE]  = Plane(-m._14 + m._11, -m._24 + m._21, -m._34 + m._31, -m._44 + m._41);
    viewFrustum_.sides_[Frustum::TOP_SIDE]    = Plane(-m._14 + m._12, -m._24 + m._22, -m._34 + m._32, -m._44 + m._42);
    viewFrustum_.sides_[Frustum::BOTTOM_SIDE] = Plane(-m._14 - m._12, -m._24 - m._22, -m._34 - m._32, -m._44 - m._42);
    viewFrustum_.sides_[Frustum::NEAR_SIDE]   = Plane(-m._13,         -m._23,         -m._33,         -m._43);
    viewFrustum_.sides_[Frustum::FAR_SIDE]    = Plane(-m._14 + m._13, -m._24 + m._23, -m._34 + m._33, -m._44 + m._43);
}
} // namespace Dxx
