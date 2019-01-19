/** @file *//********************************************************************************************************

                                                       Camera.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Camera.h#15 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#include "Frame.h"
#include "Math/Frustum.h"
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
    Camera(IDirect3DDevice11 * pDevice,
           float              angleOfView,
           float              nearDistance,
           float              farDistance,
           float              aspectRatio,
           Frame const &      frame = Frame::Identity());

    //! Constructor
    Camera(IDirect3DDevice11 *     pDevice,
           float                  angleOfView,
           float                  nearDistance,
           float                  farDistance,
           float                  aspectRatio,
           DirectX::XMFLOAT4 const &    position,
           DirectX::XMFLOAT4 const & orientation = QuaternionIdentity());

    // Destructor
    virtual ~Camera();

    // Copy constructor
    Camera(Camera const & src);

    // Assignment operator
    Camera & operator =(Camera const & rhs);

    //! Sets D3D's projection matrix based on the aspect ratio, near and far distance, and center.
    void Reshape();

    //! Sets D3D's view matrix based on the current position and orientation of the camera.
    void Look() const;

    //! Set the camera's frame of reference.
    void SetFrame(Frame const & frame);

    //! Returns the camera's current frame of reference.
    Frame GetFrame() const;

    //! Sets the camera's current position.
    void SetPosition(DirectX::XMFLOAT4 const & position);

    //! Returns the camera's current position.
    DirectX::XMFLOAT4 GetPosition() const;

    //! Sets the camera's current orientation.
    void SetOrientation(DirectX::XMFLOAT4 const & orientation);

    //! Returns the camera's current orientation.
    DirectX::XMFLOAT4 GetOrientation() const;

    //! Sets the camera's position and orientation
    void LookAt(DirectX::XMFLOAT4 const & to, DirectX::XMFLOAT4 const & from, DirectX::XMFLOAT4 const & up);

    //! Sets the distance to the near clipping plane.
    void SetNearDistance(float nearDistance);

    //! Returns the distance to the near clipping plane.
    float GetNearDistance() const;

    //! Sets the distance to the far clipping plane.
    void SetFarDistance(float farDistance);

    //! Returns the distance to the far clipping plane.
    float GetFarDistance() const;

    //! Sets the angle of view.
    void SetAngleOfView(float angle);

    //! Returns the angle of view.
    float GetAngleOfView() const;

    //! Sets the view window aspect ratio
    void SetAspectRatio(float w, float h);

    //! Sets the view offset
    void SetViewOffset(float x, float y);

    //! Rotates the camera.
    void Turn(DirectX::XMFLOAT4 const & rotation);

    //! Rotates the camera.
    void Turn(float angle, DirectX::XMFLOAT4 const & axis);

    //! Moves the camera.
    void Move(DirectX::XMFLOAT4 const & distance);

    //! Returns the direction vector
    DirectX::XMFLOAT4 GetDirection() const;

    //! Returns the up vector.
    DirectX::XMFLOAT4 GetUp() const;

    //! Returns the right vector.
    DirectX::XMFLOAT4 GetRight() const;

    //! Returns the view matrix
    DirectX::XMFLOAT4X4 const & GetViewMatrix() const;

    //! Returns the projection matrix
    DirectX::XMFLOAT4X4 const & GetProjectionMatrix() const;

    //! Returns the view-projection matrix
    DirectX::XMFLOAT4X4 const & GetViewProjectionMatrix() const;

    //! Returns the view frustum
    Frustum const & GetViewFrustum() const;

protected:

    //! Syncs the internal state of the camera so that all values are consistent.
    void SyncInternalState();

    IDirect3DDevice11 * pDevice_;                //!< Display device
    Frame frame_;                           //!< View transformation
    float nearDistance_;                        //!< The distance to the near clipping plane
    float farDistance_;                         //!< The distance to the far clipping plane
    float angleOfView_;                         //!< Angle of view of the height of the display (in radians)
    DirectX::XMFLOAT2 viewOffset_;                    //!< View window offset
    float aspectRatio_;                         //!< View window w / h
    DirectX::XMFLOAT4X4 viewMatrix_;                     //!< The current world-view transformation
    DirectX::XMFLOAT4X4 projectionMatrix_;               //!< The current projection transformation
    DirectX::XMFLOAT4X4 viewProjectionMatrix_;           //!< The concatenation of the view matrix and the projection matrix
    Frustum viewFrustum_;                       //!< View frustum

private:

    // Computes the projection matrix
    void SyncProjectionMatrix();

    // Computes the view matrix
    void SyncViewMatrix();

    // Computes the view frustum
    void ComputeViewFrustum(D3DMATRIX const & m);
};
} // namespace Dxx

#include "Camera.inl"
