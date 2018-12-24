/** @file *//********************************************************************************************************

                                                      Camera.inl

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Camera.inl#15 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Camera.h"

#include "Frame.h"

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9math.h>

namespace Dxx
{
//!
//! @param	frame	New frame of reference

inline void Camera::SetFrame(Frame const & frame)
{
    frame_ = frame;
    SyncInternalState();
}

inline Frame Camera::GetFrame() const
{
    return frame_;
}

//!
//! @param	position	New position

inline void Camera::SetPosition(D3DXVECTOR3 const & position)
{
    frame_.SetTranslation(position);
    SyncInternalState();
}

inline D3DXVECTOR3 Camera::GetPosition() const
{
    return frame_.GetTranslation();
}

//!
//! @param	orientation		New orientation

inline void Camera::SetOrientation(D3DXQUATERNION const & orientation)
{
    frame_.SetOrientation(orientation);
    SyncInternalState();
}

inline D3DXQUATERNION Camera::GetOrientation() const
{
    return frame_.GetOrientation();
}

//!
//! @param	nearDistance		Distance to the near clipping plane.

inline void Camera::SetNearDistance(float nearDistance)
{
    nearDistance_ = nearDistance;
    SyncInternalState();
}

inline float Camera::GetNearDistance() const
{
    return nearDistance_;
}

//!
//! @param	farDistance		Distance to the far clipping plane.

inline void Camera::SetFarDistance(float farDistance)
{
    farDistance_ = farDistance;
    SyncInternalState();
}

inline float Camera::GetFarDistance() const
{
    return farDistance_;
}

//! The angle of view is the angle between the top and bottom of the view frustum.
//!
//! @param	angle	Angle of view (in degrees)

inline void Camera::SetAngleOfView(float angle)
{
    angleOfView_ = Math::ToRadians(angle);
    SyncInternalState();
}

//! The angle of view is the angle between the top and bottom of the view frustum from the viewpoint.
//!

inline float Camera::GetAngleOfView() const
{
    return angleOfView_;
}

//!
//! @param	rotation	A quaternion describing the rotation.

inline void Camera::Turn(D3DXQUATERNION const & rotation)
{
    frame_.Rotate(rotation);
    SyncInternalState();
}

//! @param	angle	Angle of rotation (in degrees)
//! @param	axis	Axis of rotation

inline void Camera::Turn(float angle, D3DXVECTOR3 const & axis)
{
    D3DXQUATERNION q;
    D3DXQuaternionRotationAxis(&q, &axis, Math::ToRadians(angle));
    Turn(q);
}

//!
//! @param	distance	Amount to move the camera

inline void Camera::Move(D3DXVECTOR3 const & distance)
{
    frame_.Translate(distance);
    SyncInternalState();
}

//! @param	w	Width of the image on the screen.
//! @param	h	Height of the image on the screen.
//!
//! @note	The units of @a w and @a h are not important. @a w and @a h are only used to compute the aspect ratio.
//!			If the pixels are square then @a w and @a h can simply be the width and height in pixels, otherwise
//!			they should be the actual width and height of the image on the screen.

inline void Camera::SetAspectRatio(float w, float h)
{
    assert(h > 0  && w > 0);

    aspectRatio_ = w / h;
    SyncInternalState();
}

//! @param	x	X-offset to the center of the near plane in view space.
//! @param	y	Y-offset to the center of the near plane in view space.

inline void Camera::SetViewOffset(float x, float y)
{
    viewOffset_ = D3DXVECTOR2(x, y);
    SyncInternalState();
}

inline D3DXVECTOR3 Camera::GetDirection() const
{
    return frame_.GetZAxis();
}

inline D3DXVECTOR3 Camera::GetUp() const
{
    return frame_.GetYAxis();
}

inline D3DXVECTOR3 Camera::GetRight() const
{
    return frame_.GetXAxis();
}

inline D3DXMATRIX const & Camera::GetProjectionMatrix() const
{
    return projectionMatrix_;
}

inline D3DXMATRIX const & Camera::GetViewMatrix() const
{
    return viewMatrix_;
}

inline D3DXMATRIX const & Camera::GetViewProjectionMatrix() const
{
    return viewProjectionMatrix_;
}

inline Frustum const & Camera::GetViewFrustum() const
{
    return viewFrustum_;
}
} // namespace Dxx