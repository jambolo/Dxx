/** @file *//********************************************************************************************************

                                                ComputeFaceNormal.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/ComputeFaceNormal.cpp#7 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "D3d.h"

namespace Dxx
{
//! @param	v0,v1,v2	Vertexes. The order of the vertexes is important. They should be clockwise.
//! @param	pN			Location to store the normal (overwriting a parameter is ok)

D3DXVECTOR3 * ComputeFaceNormal(D3DXVECTOR3 const & v0, D3DXVECTOR3 const & v1, D3DXVECTOR3 const & v2, D3DXVECTOR3 * pN)
{
    D3DXVECTOR3 v0v1, v0v2;

    D3DXVec3Subtract(&v0v1, &v1, &v0);
    D3DXVec3Subtract(&v0v2, &v2, &v0);

    D3DXVec3Cross(pN, &v0v1, &v0v2);

    D3DXVec3Normalize(pN, pN);

    return pN;
}

//! @param	z1		Z of the +X vertex
//! @param	z2		Z of the +Y vertex
//! @param	z3		Z of the -X vertex
//! @param	z4		Z of the -Y vertex
//! @param	scale	Ratio of Sxy / Sz, where Sxy is the distance between vertices and Sz scales the specified Z
//!					values to the actual Z values.
//! @param	pN		Where to put the normal

D3DXVECTOR3 * ComputeGridNormal(float z1, float z2, float z3, float z4, float scale, D3DXVECTOR3 * pN)
{
//	The 4 adjacent points in a uniform grid: A, B, C, D
//
//	   B
//	   |
//	C--0--A
//	   |
//	   D
//
//
//	The ratio of XY-scale to Z-scale: s = Sxy / Sz
//	The desired normal: N = cross(A,B) + cross(B,C) + cross(C,D) + cross(D,A), (then normalize)
//
//	Nx = 2 * s * (Cz - Az)
//	Ny = 2 * s * (Dz - Bz)
//	Nz = 4 * s^2
//	N = normalize( N )
//
//	Since N is normalized in the end, it can be divided by 2 * s:
//
//	Nx = Cz - Az
//	Ny = Dz - Bz
//	Nz = 2 * s
//	N = normalize( N )
//

    pN->x = z3 - z1;
    pN->y = z4 - z2;
    pN->z = 2.0f * scale;

    D3DXVec3Normalize(pN, pN);

    return pN;
}
} // namespace Dxx
