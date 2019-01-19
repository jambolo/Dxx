/** @file *//********************************************************************************************************

                                                     Random.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Random.cpp#4 $

    $NoKeywords: $

 *********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "Random.h"

namespace Dxx
{
//!
//! @param	seed		Initial seed.

RandomDirection::RandomDirection(Seed seed)
    : RandomFloat(seed)
{
}

DirectX::XMFLOAT4 RandomDirection::Get()
{
    float const r = RandomFloat::Get(float(Math::TWO_PI));
    float const t = RandomFloat::Get(float(Math::TWO_PI));

    float sr, cr, st, ct;

    Math::fsincos(r, &sr, &cr);
    Math::fsincos(t, &st, &ct);

    return DirectX::XMFLOAT4(ct, cr * st, sr * st);
}

//! This function returns a random unit vector whose angle from the X axis is uniformly-distributed in range
//! [0,@a a).
//!
//! @param	a	The maximum angle (exclusive) in radians from the X axis.
//!
//! @return	A unit vector.

DirectX::XMFLOAT4 RandomDirection::Get(float a)
{
    float const ca = cosf(a);
    float const cr = 1.f - RandomFloat::Get(1.f - ca);
    float const sr = sqrtf(1.f - cr * cr);
    float const t  = RandomFloat::Get(float(Math::TWO_PI));

    float st, ct;

    Math::fsincos(t, &st, &ct);

    return DirectX::XMFLOAT4(cr, ct * sr, st * sr);
}

//! This function returns a random unit vector whose angle from the XZ plane is uniformly-distributed in range
//! [-<i>a<i>,+<i>a</i>), and whose angle from the XY plane is
//! uniformly-distributed in range [-<i>b<i>,+<i>b</i>).

//! @param	a	The maximum angle in radians from the XZ plane. Valid range is (0, PI].
//! @param	b	The maximum angle in radians from the XY plane. Valid range is (0, PI/2].
//!
//! @return	A unit vector.

DirectX::XMFLOAT4 RandomDirection::Get(float a, float b)
{
    assert(a != 0.f);
    assert_limits(0.f, a, Math::PI);
    assert(b != 0.f);
    assert_limits(0.f, b, Math::PI_OVER_2);

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

    float const t = RandomFloat::Get(-a, a);
    float const cf = RandomFloat::Get(-b, b) / float(Math::PI_OVER_2);
    float const sf = sqrtf(1.f - cf * cf);
    float       st, ct;

    Math::fsincos(t, &st, &ct);

    return DirectX::XMFLOAT4(cf * ct, sf, cf * st);
}

//!
//! @param	state	New state.
void RandomDirection::SetState(State const & state)
{
    RandomFloat::SetState(state);
}

RandomDirection::State const & RandomDirection::GetState() const
{
    return RandomFloat::GetState();
}

//!
//! @param	seed		Initial seed.

RandomOrientation::RandomOrientation(Seed seed)
    : RandomFloat(seed)
{
}

DirectX::XMFLOAT4 RandomOrientation::Get()
{
    float const r = RandomFloat::Get(float(Math::TWO_PI));
    float const t = RandomFloat::Get(float(Math::TWO_PI));

    float sr, cr, st, ct;

    Math::fsincos(r, &sr, &cr);
    Math::fsincos(t, &st, &ct);

    DirectX::XMFLOAT4 const direction = DirectX::XMFLOAT4(ct, cr * st, sr * st);
    float const       a         = RandomFloat::Get(float(Math::TWO_PI));
    DirectX::XMFLOAT4    q;

    D3DXQuaternionRotationAxis(&q, &direction, a);

    return q;
}

//!
//! @param	state	New state.
void RandomOrientation::SetState(State const & state)
{
    RandomFloat::SetState(state);
}

RandomOrientation::State const & RandomOrientation::GetState() const
{
    return RandomFloat::GetState();
}
} // namespace Dxx
