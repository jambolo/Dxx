/** @file *//********************************************************************************************************

                                                       Frame.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Frame.h#11 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <DirectXMath.h>
#include <windows.h>

namespace Dxx
{
//! A frame of reference including translation, scale, and orientation.
//
//! @ingroup	D3dx
//!

class Frame
{
public:

    //! Constructor
    Frame();

    //! Constructor
    Frame(DirectX::XMFLOAT4 const & translation,
          DirectX::XMFLOAT4 const & rotation,
          DirectX::XMFLOAT4 const & scale = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f));

    //! Translates the frame. Returns the new frame.
    Frame & Translate(DirectX::XMFLOAT4 const & t);

    //! Rotates the frame. Returns the new frame.
    Frame & Rotate(DirectX::XMFLOAT4 const & r);

    //! Scales the frame. Returns the new frame.
    Frame & Scale(DirectX::XMFLOAT4 const & s);

    //! Sets the frame's translation.
    void SetTranslation(DirectX::XMFLOAT4 const & t);

    //! Returns the frame's translation.
    DirectX::XMFLOAT4 GetTranslation()                                const;

    //! Sets the frame's rotation as a quaternion.
    void SetOrientation(DirectX::XMFLOAT4 const & r);

    //! Returns the frame's rotation as a quaternion.
    DirectX::XMFLOAT4 GetOrientation()                             const;

    //! Sets the frame's orientation as a matrix.
    void SetOrientationMatrix(DirectX::XMFLOAT4X4 const & r);

    //! Returns the frame's orientation as a matrix.
    DirectX::XMFLOAT4X4 GetOrientationMatrix()                           const;

    //! Sets the frame's scale.
    void SetScale(DirectX::XMFLOAT4 const & s);

    //! Returns the frame's scale.
    DirectX::XMFLOAT4 GetScale()                                      const;

    //! Sets the frame's transformation matrix.
    void SetTransformationMatrix(DirectX::XMFLOAT4X4 const & m);

    //! Returns the frame's transformation matrix.
    DirectX::XMFLOAT4X4 const & GetTransformationMatrix()               const;

    //! Returns the frame's unit X axis in global space.
    DirectX::XMFLOAT4 GetXAxis()                                      const;

    //! Returns the frame's unit Y axis in global space.
    DirectX::XMFLOAT4 GetYAxis()                                      const;

    //! Returns the frame's unit Z axis in global space.
    DirectX::XMFLOAT4 GetZAxis()                                      const;

    //! Returns an untransformed Frame.
    static Frame Identity();

private:

    DirectX::XMFLOAT4X4 M_;  //!< Transformation matrix
};
} // namespace Dxx

// Inline functions

#include "Frame.inl"
