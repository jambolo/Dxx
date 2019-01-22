/** @file *//********************************************************************************************************

                                                     Random.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Random.cpp#4 $

    $NoKeywords: $

 *********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Random.h"

#include "Misc/Assert.h"
#include "MyMath/FastMath.h"
#include "MyMath/Constants.h"

#include <DirectXMath.h>

namespace Dxx
{
//!
//! @param	seed		Initial seed.

RandomDirection::RandomDirection(Seed seed)
    : rng_(seed)
{
}

DirectX::XMFLOAT3 RandomDirection::operator ()()
{
    float r = rng_(float(DirectX::XM_2PI));
    float t = rng_(float(DirectX::XM_2PI));

    float sr, cr, st, ct;

    MyMath::fsincos(r, &sr, &cr);
    MyMath::fsincos(t, &st, &ct);

    return { ct, cr * st, sr * st };
}

//! This function returns a random unit vector whose angle from the X axis is uniformly-distributed in range
//! [0,@a a).
//!
//! @param	a	The maximum angle (exclusive) in radians from the X axis.
//!
//! @return	A unit vector.

DirectX::XMFLOAT3 RandomDirection::operator ()(float a)
{
    float ca = cosf(a);
    float cr = 1.f - rng_(1.f - ca);
    float sr = sqrtf(1.f - cr * cr);
    float t  = rng_(float(DirectX::XM_2PI));

    float st, ct;

    MyMath::fsincos(t, &st, &ct);

    return { cr, ct * sr, st * sr };
}

//! This function returns a random unit vector whose angle from the XZ plane is uniformly-distributed in range
//! [-<i>a<i>,+<i>a</i>), and whose angle from the XY plane is
//! uniformly-distributed in range [-<i>b<i>,+<i>b</i>).

//! @param	a	The maximum angle in radians from the XZ plane. Valid range is (0, PI].
//! @param	b	The maximum angle in radians from the XY plane. Valid range is (0, PI/2].
//!
//! @return	A unit vector.

DirectX::XMFLOAT3 RandomDirection::operator ()(float a, float b)
{
    assert(a != 0.f);
    assert_limits(0.f, a, DirectX::XM_PI);
    assert(b != 0.f);
    assert_limits(0.f, b, DirectX::XM_PIDIV2);

    // Source: http://mathworld.wolfram.com/SpherePointPicking.html
    //
    // u = R(-1,1)
    // v = R(-1,1)
    // t = a * u
    // f = acos( b / (PI/2) * v )
    // v = [ cos(f) * cos(t), sin(f), cos(f) * sin(t) ]
    // v = [ cos(f) * cos(t), sqrt(1.-cos(f)*cos(f)), cos(f) * sin(t) ]
    // ct = cos(t)
    // st = sin(t)
    // cf = cos(f) = b / (PI/2) * v
    // sf = sin(f) = sqrt( 1. - cf*cf )
    // v = [ cf * ct, sf, cf * st ]

    float t = rng_(-a, a);
    float cf = rng_(-b, b) / DirectX::XM_PIDIV2;
    float sf = sqrtf(1.f - cf * cf);
    float       st, ct;

    MyMath::fsincos(t, &st, &ct);

    return { cf * ct, sf, cf * st };
}

//!
//! @param	state	New state.
void RandomDirection::setState(State const & state)
{
    rng_.setState(state);
}

RandomDirection::State RandomDirection::state() const
{
    return rng_.state();
}

//!
//! @param	seed		Initial seed.

RandomOrientation::RandomOrientation(Seed seed)
    : rng_(seed)
{
}

DirectX::XMFLOAT4 RandomOrientation::operator ()()
{
    float r = rng_(float(DirectX::XM_2PI));
    float t = rng_(float(DirectX::XM_2PI));

    float sr, cr, st, ct;

    MyMath::fsincos(r, &sr, &cr);
    MyMath::fsincos(t, &st, &ct);

    DirectX::XMFLOAT3 direction(ct, cr * st, sr * st);
    float             a = rng_(DirectX::XM_2PI);
    DirectX::XMVECTOR direction_simd(DirectX::XMLoadFloat3(&direction));

    DirectX::XMVECTOR q_simd = DirectX::XMQuaternionRotationAxis(direction_simd, a);

    DirectX::XMFLOAT4 q;
    DirectX::XMStoreFloat4(&q, q_simd);

    return q;
}

//!
//! @param	state	New state.
void RandomOrientation::setState(State const & state)
{
    rng_.setState(state);
}

RandomOrientation::State RandomOrientation::state() const
{
    return rng_.state();
}
} // namespace Dxx
