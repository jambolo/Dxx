#include "Random.h"

#include "Misc/Assertx.h"
#include "MyMath/Constants.h"
#include "MyMath/FastMath.h"

#include <DirectXMath.h>

#include <random>

namespace Dxx
{
//! If both phi and theta are 0, then unlimited directions are generated.
//! If theta is 0, then directions within phi radians from the X axis are generated.
//! If both phi and theta are not 0, then directions within phi radians from X in the XY plane and within theta radians from X in
//! the XZ plane are generated.
//!
//! @param  phi     Max angle from X axis (Valid range is [0, pi], default: 0)
//! @param  theta   Max angle from X axis in radians in the XZ plane (Valid range is [0, pi], default: 0)

RandomDirection::RandomDirection(float phi /*= 0.0f*/, float theta /*= 0.0f*/)
    : phi_((phi == 0.0f && theta == 0.0f) ? DirectX::XM_PI : phi)
    , theta_(theta)
{
    assert_limits(0.0f, theta, DirectX::XM_PI);
    assert_limits(0.0f, phi, DirectX::XM_PI);
}

DirectX::XMFLOAT3 RandomDirection::convert(float u, float v) const
{
    // Source: http://mathworld.wolfram.com/SpherePointPicking.html
    //
    //      To obtain points such that any small area on the sphere is expected to contain the same number of points
    //      (right figure above), choose U and V to be random variates on (0,1). Then
    //
    //          theta = 2pi u
    //          phi = acos(2v - 1)

    DirectX::XMFLOAT3 d;
    float sp, cp;
    float st, ct;

    //  if theta is 0, then generate directions in a cone around the X axis
    if (theta_ == 0.0f)
    {
        float t = DirectX::XM_2PI * u;
        MyMath::fsincos(t, &st, &ct);

        cp = 1.0f - (1.0f - cos(phi_)) * v;
        sp = sqrtf(1.0f - cp * cp);
        d  = { cp, ct * sp, st * sp };
    }

    // Otherwise, generate directions in a section around the X axis limited by phi in the XY plane and theta in the XZ plane
    else
    {
        float t = theta_ * (2.0f * u - 1.0f);
        MyMath::fsincos(t, &st, &ct);

        cp = sin(phi_) * (2.0f * v - 1.0f);
        sp = sqrtf(1.0f - cp * cp);
        d  = { ct * sp, st * sp, cp };
    }

    return d;
}

DirectX::XMFLOAT4 RandomOrientation::convert(DirectX::XMFLOAT3 const & axis, float angle) const
{
    DirectX::XMVECTOR axis_simd(DirectX::XMLoadFloat3(&axis));
    DirectX::XMVECTOR q_simd = DirectX::XMQuaternionRotationAxis(axis_simd, angle);

    DirectX::XMFLOAT4 q;
    DirectX::XMStoreFloat4(&q, q_simd);

    return q;
}
} // namespace Dxx
