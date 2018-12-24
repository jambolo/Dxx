/** @file *//********************************************************************************************************

                                                       Camera.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Camera.h#15 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include "D3d.h"
#include "Frame.h"
#include "Math/Frustum.h"
#include <d3d9.h>
#include <d3dx9math.h>

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
    Camera(IDirect3DDevice9 * pDevice,
           float              angleOfView,
           float              nearDistance,
           float              farDistance,
           float              aspectRatio,
           Frame const &      frame = Frame::Identity());

    //! Constructor
    Camera(IDirect3DDevice9 *     pDevice,
           float                  angleOfView,
           float                  nearDistance,
           float                  farDistance,
           float                  aspectRatio,
           D3DXVECTOR3 const &    position,
           D3DXQUATERNION const & orientation = QuaternionIdentity());

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
    void SetPosition(D3DXVECTOR3 const & position);

    //! Returns the camera's current position.
    D3DXVECTOR3 GetPosition() const;

    //! Sets the camera's current orientation.
    void SetOrientation(D3DXQUATERNION const & orientation);

    //! Returns the camera's current orientation.
    D3DXQUATERNION GetOrientation() const;

    //! Sets the camera's position and orientation
    void LookAt(D3DXVECTOR3 const & to, D3DXVECTOR3 const & from, D3DXVECTOR3 const & up);

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
    void Turn(D3DXQUATERNION const & rotation);

    //! Rotates the camera.
    void Turn(float angle, D3DXVECTOR3 const & axis);

    //! Moves the camera.
    void Move(D3DXVECTOR3 const & distance);

    //! Returns the direction vector
    D3DXVECTOR3 GetDirection() const;

    //! Returns the up vector.
    D3DXVECTOR3 GetUp() const;

    //! Returns the right vector.
    D3DXVECTOR3 GetRight() const;

    //! Returns the view matrix
    D3DXMATRIX const & GetViewMatrix() const;

    //! Returns the projection matrix
    D3DXMATRIX const & GetProjectionMatrix() const;

    //! Returns the view-projection matrix
    D3DXMATRIX const & GetViewProjectionMatrix() const;

    //! Returns the view frustum
    Frustum const & GetViewFrustum() const;

protected:

    //! Syncs the internal state of the camera so that all values are consistent.
    void SyncInternalState();

    IDirect3DDevice9 * pDevice_;                //!< Display device
    Frame frame_;                           //!< View transformation
    float nearDistance_;                        //!< The distance to the near clipping plane
    float farDistance_;                         //!< The distance to the far clipping plane
    float angleOfView_;                         //!< Angle of view of the height of the display (in radians)
    D3DXVECTOR2 viewOffset_;                    //!< View window offset
    float aspectRatio_;                         //!< View window w / h
    D3DXMATRIX viewMatrix_;                     //!< The current world-view transformation
    D3DXMATRIX projectionMatrix_;               //!< The current projection transformation
    D3DXMATRIX viewProjectionMatrix_;           //!< The concatenation of the view matrix and the projection matrix
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
