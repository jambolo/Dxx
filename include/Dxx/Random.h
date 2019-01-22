#pragma once

#if !defined(DXX_RANDOM_H)
#define DXX_RANDOM_H

#include "Misc/Random.h"
#include <DirectXMath.h>

namespace Dxx
{
//! A LCG pseudo-random number generator that generates directions.

class RandomDirection
{
public:

    using Seed  = uint32_t;             //!< The type of the seed value.
    using State = RandomFloat::State;   //!< The type of the state.

    //! Constructor.
    RandomDirection(Seed seed);

    //! Returns a unit vector with a random direction.
    DirectX::XMFLOAT3 operator ()();

    //! Returns a unit vector with a random direction limited to a cone centered on the X axis.
    DirectX::XMFLOAT3 operator ()(float a);

    //! Returns a unit vector with a random direction limited to a pyramid centered on the X axis.
    DirectX::XMFLOAT3 operator ()(float a, float b);

    //! Sets the state.
    void setState(State const & state);

    //! Returns the current state.
    State state() const;

private:
    RandomFloat rng_;
};

//! A LCG pseudo-random number generator that generates orientations.

class RandomOrientation
{
public:

    using Seed  = uint32_t;             //!< The type of the seed value.
    using State = RandomFloat::State;   //!< The type of the state.

    //! Constructor.
    RandomOrientation(Seed seed);

    //! Returns a random orientation.
    DirectX::XMFLOAT4 operator ()();

    //! Sets the state.
    void setState(State const & state);

    //! Returns the current state.
    State state() const;

private:
    RandomFloat rng_;
};
} // namespace Dxx

#endif // !defined(DXX_RANDOM_H)
