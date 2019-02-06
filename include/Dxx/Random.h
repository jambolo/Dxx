#pragma once

#if !defined(DXX_RANDOM_H)
#define DXX_RANDOM_H

#include <DirectXMath.h>
#include <random>

namespace Dxx
{
//! Generates a random direction as a unit vector.

class RandomDirection
{
public:

    //! Constructor.
    explicit RandomDirection(float phi = 0.0f, float theta = 0.0f);

    //! Returns a unit vector with a random direction.
    template <typename Generator>
    DirectX::XMFLOAT3 RandomDirection::operator ()(Generator & rng) const
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);
        return convert(range(rng), range(rng));
    }

private:
    DirectX::XMFLOAT3 convert(float u, float v) const;

    float phi_;
    float theta_;
};

//! Generates an orientation as a quaternion.

class RandomOrientation
{
public:

    //! Returns a random orientation.
    template <typename Generator>
    DirectX::XMFLOAT4 RandomOrientation::operator ()(Generator & rng) const
    {
        RandomDirection axis;
        std::uniform_real_distribution<float> angle(0.0f, DirectX::XM_2PI);
        return convert(axis(rng), angle(rng));
    }

private:
    DirectX::XMFLOAT4 convert(DirectX::XMFLOAT3 const & axis, float angle) const;
};
} // namespace Dxx

#endif // !defined(DXX_RANDOM_H)
