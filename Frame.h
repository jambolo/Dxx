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

#include <d3dx9math.h>
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
    Frame(D3DXVECTOR3 const & translation,
          D3DXQUATERNION const & rotation,
          D3DXVECTOR3 const & scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));

    //! Translates the frame. Returns the new frame.
    Frame & Translate(D3DXVECTOR3 const & t);

    //! Rotates the frame. Returns the new frame.
    Frame & Rotate(D3DXQUATERNION const & r);

    //! Scales the frame. Returns the new frame.
    Frame & Scale(D3DXVECTOR3 const & s);

    //! Sets the frame's translation.
    void SetTranslation(D3DXVECTOR3 const & t);

    //! Returns the frame's translation.
    D3DXVECTOR3 GetTranslation()                                const;

    //! Sets the frame's rotation as a quaternion.
    void SetOrientation(D3DXQUATERNION const & r);

    //! Returns the frame's rotation as a quaternion.
    D3DXQUATERNION GetOrientation()                             const;

    //! Sets the frame's orientation as a matrix.
    void SetOrientationMatrix(D3DXMATRIX const & r);

    //! Returns the frame's orientation as a matrix.
    D3DXMATRIX GetOrientationMatrix()                           const;

    //! Sets the frame's scale.
    void SetScale(D3DXVECTOR3 const & s);

    //! Returns the frame's scale.
    D3DXVECTOR3 GetScale()                                      const;

    //! Sets the frame's transformation matrix.
    void SetTransformationMatrix(D3DXMATRIX const & m);

    //! Returns the frame's transformation matrix.
    D3DXMATRIX const & GetTransformationMatrix()               const;

    //! Returns the frame's unit X axis in global space.
    D3DXVECTOR3 GetXAxis()                                      const;

    //! Returns the frame's unit Y axis in global space.
    D3DXVECTOR3 GetYAxis()                                      const;

    //! Returns the frame's unit Z axis in global space.
    D3DXVECTOR3 GetZAxis()                                      const;

    //! Returns an untransformed Frame.
    static Frame Identity();

private:

    D3DXMATRIX M_;  //!< Transformation matrix
};
} // namespace Dxx

// Inline functions

#include "Frame.inl"
