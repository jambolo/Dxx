#pragma once

#if !defined(DXX_FRAME_H)
#define DXX_FRAME_H

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
    constexpr Frame()
        : m_(DirectX::XMFLOAT4X4(
                 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f))
    {
    }

    //! Constructor
    Frame(DirectX::XMFLOAT3 const & translation,
          DirectX::XMFLOAT4 const & rotation,
          DirectX::XMFLOAT3 const & scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    //! Translates the frame and returns it.
    Frame & translate(DirectX::XMFLOAT3 const & t);

    //! Rotates the frame by the given quaternion and returns it.
    Frame & rotate(DirectX::XMFLOAT4 const & r);

    //! Scales the frame and returns it.
    Frame & scale(DirectX::XMFLOAT3 const & s);

    //! Sets the frame's translation.
    void setTranslation(DirectX::XMFLOAT3 const & t);

    //! Returns the frame's translation.
    DirectX::XMFLOAT3 translation() const;

    //! Sets the frame's rotation according to the given quaternion.
    void setOrientation(DirectX::XMFLOAT4 const & r);

    //! Sets the frame's orientation as a matrix.
    void setOrientation(DirectX::XMFLOAT3X3 const & r);

    //! Returns the frame's rotation as a quaternion.
    DirectX::XMFLOAT4 orientation() const;

    //! Returns the frame's orientation as a matrix.
    DirectX::XMFLOAT3X3 orientationMatrix() const;

    //! Sets the frame's scale.
    void setScale(DirectX::XMFLOAT3 const & s);

    //! Returns the frame's scale.
    DirectX::XMFLOAT3 scale() const;

    //! Sets the frame's transformation matrix.
    void setTransformation(DirectX::XMFLOAT4X4 const & m);

    //! Returns the frame's transformation matrix.
    DirectX::XMFLOAT4X4 transformation() const;

    //! Returns the frame's unit X axis in global space.
    DirectX::XMFLOAT3 xAxis() const;

    //! Returns the frame's unit Y axis in global space.
    DirectX::XMFLOAT3 yAxis() const;

    //! Returns the frame's unit Z axis in global space.
    DirectX::XMFLOAT3 zAxis() const;

    //! Returns an untransformed Frame.
    static Frame identity() { return Frame(); }

private:

    DirectX::XMFLOAT4X4 m_;  //!< Transformation matrix
};
} // namespace Dxx

#endif // !defined(DXX_FRAME_H)
