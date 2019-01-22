#pragma once

#if !defined(DXX_CAMERA_H)
#define DXX_CAMERA_H

#include "Dxx/Frame.h"
#include "Dxx/Dxx.h"
#include "MyMath/Frustum.h"
#include <DirectXMath.h>

namespace Dxx
{
//! A camera.
//
//! @ingroup	D3dx
//!

class Camera
{
public:

    //! Constructor
    Camera(float              angleOfView,
           float              nearDistance,
           float              farDistance,
           float              aspectRatio,
           Frame const &      frame = Frame::identity());

    //! Constructor
    Camera(float                  angleOfView,
           float                  nearDistance,
           float                  farDistance,
           float                  aspectRatio,
           DirectX::XMFLOAT3 const &    position,
           DirectX::XMFLOAT4 const & orientation = QuaternionIdentity());

    // Destructor
    virtual ~Camera() = default;

#if 0
    //! Sets D3D's projection matrix based on the aspect ratio, near and far distance, and center.
    void reshape();

    //! Sets D3D's view matrix based on the current position and orientation of the camera.
    void look() const;
#endif

    //! Sets the camera's frame of reference.
    void setFrame(Dxx::Frame const & frame);

    //! Returns the camera's current frame of reference.
    Dxx::Frame frame() const;

    //! Sets the camera's current position.
    void setPosition(DirectX::XMFLOAT3 const & position);

    //! Returns the camera's current position.
    DirectX::XMFLOAT3 position() const;

    //! Sets the camera's current orientation.
    void setOrientation(DirectX::XMFLOAT4 const & orientation);

    //! Returns the camera's current orientation.
    DirectX::XMFLOAT4 orientation() const;

    //! Sets the camera's position and orientation
    void lookAt(DirectX::XMFLOAT3 const & to, DirectX::XMFLOAT3 const & from, DirectX::XMFLOAT3 const & up);

    //! Sets the distance to the near clipping plane.
    void setNearDistance(float nearDistance);

    //! Returns the distance to the near clipping plane.
    float nearDistance() const;

    //! Sets the distance to the far clipping plane.
    void setFarDistance(float farDistance);

    //! Returns the distance to the far clipping plane.
    float farDistance() const;

    //! Sets the angle of view.
    void setAngleOfView(float angle);

    //! Returns the angle of view.
    float angleOfView() const;

    //! Sets the view window aspect ratio
    void setAspectRatio(float w, float h);

    //! Sets the view offset
    void setViewOffset(float x, float y);

    //! Rotates the camera.
    void turn(DirectX::XMFLOAT4 const & rotation);

    //! Rotates the camera.
    void turn(float angle, DirectX::XMFLOAT3 const & axis);

    //! Moves the camera.
    void move(DirectX::XMFLOAT3 const & distance);

    //! Returns the direction vector
    DirectX::XMFLOAT3 direction() const;

    //! Returns the up vector.
    DirectX::XMFLOAT3 up() const;

    //! Returns the right vector.
    DirectX::XMFLOAT3 right() const;

    //! Returns the view matrix
    DirectX::XMFLOAT4X4 viewMatrix() const;

    //! Returns the projection matrix
    DirectX::XMFLOAT4X4 projectionMatrix() const;

    //! Returns the view-projection matrix
    DirectX::XMFLOAT4X4 viewProjectionMatrix() const;

    //! Returns the view frustum
    Frustum viewFrustum() const;

protected:

    //! Syncs the internal state of the camera so that all values are consistent.
    void SyncInternalState();

    Frame frame_;                               //!< View transformation
    float nearDistance_;                        //!< The distance to the near clipping plane
    float farDistance_;                         //!< The distance to the far clipping plane
    float angleOfView_;                         //!< Angle of view of the height of the display (in radians)
    DirectX::XMFLOAT2 viewOffset_;              //!< View window offset
    float aspectRatio_;                         //!< View window w / h
    DirectX::XMFLOAT4X4 viewMatrix_;            //!< The current world-view transformation
    DirectX::XMFLOAT4X4 projectionMatrix_;      //!< The current projection transformation
    DirectX::XMFLOAT4X4 viewProjectionMatrix_;  //!< The concatenation of the view matrix and the projection matrix
    Frustum viewFrustum_;                       //!< View frustum

private:

    // Computes the projection matrix
    void SyncProjectionMatrix();

    // Computes the view matrix
    void SyncViewMatrix();

    // Computes the view frustum
    void ComputeViewFrustum(DirectX::XMFLOAT4X4 const & m);
};
} // namespace Dxx

#include "Frame.h"

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <d3d11.h>
#include <DirectXMath.h>

namespace Dxx
{
//!
//! @param	frame	New frame of reference

inline void Camera::setFrame(Frame const & frame)
{
    frame_ = frame;
    SyncInternalState();
}

inline Frame Camera::frame() const
{
    return frame_;
}

//!
//! @param	position	New position

inline void Camera::setPosition(DirectX::XMFLOAT3 const & position)
{
    frame_.setTranslation(position);
    SyncInternalState();
}

//!
//! @param	orientation		New orientation

inline void Camera::setOrientation(DirectX::XMFLOAT4 const & orientation)
{
    frame_.setOrientation(orientation);
    SyncInternalState();
}

//!
//! @param	nearDistance		Distance to the near clipping plane.

inline void Camera::setNearDistance(float nearDistance)
{
    nearDistance_ = nearDistance;
    SyncInternalState();
}

inline float Camera::nearDistance() const
{
    return nearDistance_;
}

//!
//! @param	farDistance		Distance to the far clipping plane.

inline void Camera::setFarDistance(float farDistance)
{
    farDistance_ = farDistance;
    SyncInternalState();
}

inline float Camera::farDistance() const
{
    return farDistance_;
}

//! The angle of view is the angle between the top and bottom of the view frustum.
//!
//! @param	angle	Angle of view (in degrees)

inline void Camera::setAngleOfView(float angle)
{
    angleOfView_ = MyMath::ToRadians(angle);
    SyncInternalState();
}

//! The angle of view is the angle between the top and bottom of the view frustum from the viewpoint.
//!

inline float Camera::angleOfView() const
{
    return angleOfView_;
}

//!
//! @param	rotation	A quaternion describing the rotation.

inline void Camera::turn(DirectX::XMFLOAT4 const & rotation)
{
    frame_.rotate(rotation);
    SyncInternalState();
}

//!
//! @param	distance	Amount to move the camera

inline void Camera::move(DirectX::XMFLOAT3 const & distance)
{
    frame_.translate(distance);
    SyncInternalState();
}

//! @param	w	Width of the image on the screen.
//! @param	h	Height of the image on the screen.
//!
//! @note	The units of @a w and @a h are not important. @a w and @a h are only used to compute the aspect ratio.
//!			If the pixels are square then @a w and @a h can simply be the width and height in pixels, otherwise
//!			they should be the actual width and height of the image on the screen.

inline void Camera::setAspectRatio(float w, float h)
{
    assert(h > 0 && w > 0);

    aspectRatio_ = w / h;
    SyncInternalState();
}

//! @param	x	X-offset to the center of the near plane in view space.
//! @param	y	Y-offset to the center of the near plane in view space.

inline void Camera::setViewOffset(float x, float y)
{
    viewOffset_ = DirectX::XMFLOAT2(x, y);
    SyncInternalState();
}

inline DirectX::XMFLOAT3 Camera::direction() const
{
    return frame_.zAxis();
}

inline DirectX::XMFLOAT3 Camera::up() const
{
    return frame_.yAxis();
}

inline DirectX::XMFLOAT3 Camera::right() const
{
    return frame_.xAxis();
}

inline DirectX::XMFLOAT4X4 Camera::projectionMatrix() const
{
    return projectionMatrix_;
}

inline DirectX::XMFLOAT4X4 Camera::viewMatrix() const
{
    return viewMatrix_;
}

inline DirectX::XMFLOAT4X4 Camera::viewProjectionMatrix() const
{
    return viewProjectionMatrix_;
}

inline Frustum Camera::viewFrustum() const
{
    return viewFrustum_;
}
} // namespace Dxx

#endif // !defined(DXX_CAMERA_H)
