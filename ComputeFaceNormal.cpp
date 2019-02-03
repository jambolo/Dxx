#include "D3dx.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace Dxx
{
//! @param	v0,v1,v2	Vertexes. The order of the vertexes is important. They should be clockwise.
//! @param	pN			Location to store the normal (if not nullptr)
//!
//! @return     The face normal

XMFLOAT3 ComputeFaceNormal(XMFLOAT3 const & v0,
                           XMFLOAT3 const & v1,
                           XMFLOAT3 const & v2,
                           XMFLOAT3 *       pN /*= nullptr*/)
{
    XMVECTOR v0_simd(XMLoadFloat3(&v0));
    XMVECTOR v1_simd(XMLoadFloat3(&v1));
    XMVECTOR v2_simd(XMLoadFloat3(&v2));

    XMVECTOR v0v1_simd(v1_simd - v0_simd);
    XMVECTOR v1v2_simd(v2_simd - v1_simd);

    XMVECTOR normal_simd = XMVector3Normalize(XMVector3Cross(v0v1_simd, v1v2_simd));

    XMFLOAT3 normal;
    if (!pN)
        pN = &normal;

    XMStoreFloat3(pN, normal_simd);
    return *pN;
}

//! @param	z1		Z of the +X vertex
//! @param	z2		Z of the +Y vertex
//! @param	z3		Z of the -X vertex
//! @param	z4		Z of the -Y vertex
//! @param	scale	Ratio of Sxy / Sz, where Sxy is the distance between vertices and Sz scales the specified Z
//!					values to the actual Z values.
//! @param	pN		Where to put the normal (if not nullptr)

XMFLOAT3 ComputeGridNormal(float      z1,
                           float      z2,
                           float      z3,
                           float      z4,
                           float      scale,
                           XMFLOAT3 * pN /*= nullptr*/)
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
//	Since N is normalized in the end, (2 * s) can be removed from the component values:
//
//	Nx = Cz - Az
//	Ny = Dz - Bz
//	Nz = 2 * s
//	N = normalize( N )
//
    XMVECTOR normal_simd = XMVectorSet(z3 - z1, z4 - z2, 2.0f * scale, 0.0f);
    normal_simd = XMVector3Normalize(normal_simd);

    XMFLOAT3 normal;
    if (!pN)
        pN = &normal;

    XMStoreFloat3(pN, normal_simd);
    return *pN;
}
} // namespace Dxx
