/** @file *//********************************************************************************************************

                                                      Random.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/Random.h#3 $

    $NoKeywords: $

 *********************************************************************************************************************/

#pragma once

#include "Misc/Random.h"

namespace Dxx
{
//! A LCG pseudo-random number generator that generates directions.

class RandomDirection : private RandomFloat
{
public:

    using Seed  = uint32_t;                             //!< The type of the seed value.
    using State = RandomFloat::State;                   //!< The type of the state.

    //! Constructor.
    RandomDirection(Seed seed);

    //! Returns a unit vector with a random direction.
    D3DXVECTOR3 Get();

    //! Returns a unit vector with a random direction limited to a cone centered on the X axis.
    D3DXVECTOR3 Get(float a);

    //! Returns a unit vector with a random direction limited to a pyramid centered on the X axis.
    D3DXVECTOR3 Get(float a, float b);

    //! Sets the state.
    void SetState(State const & state);

    //! Returns the current state.
    State const & GetState() const;
};

//! A LCG pseudo-random number generator that generates orientations.

class RandomOrientation : private RandomFloat
{
public:

    using Seed  = uint32_t;                             //!< The type of the seed value.
    using State = RandomFloat::State;                   //!< The type of the state.

    //! Constructor.
    RandomOrientation(Seed seed);

    //! Returns a random orientation.
    D3DXQUATERNION Get();

    //! Sets the state.
    void SetState(State const & state);

    //! Returns the current state.
    State const & GetState() const;
};
} // namespace Dxx

// Inline functions

#include "Random.inl"
