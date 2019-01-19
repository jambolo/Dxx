/** @file *//********************************************************************************************************

                                                      XMesh.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/XMesh.cpp#10 $

    $NoKeywords: $

********************************************************************************************************************/

#include "PrecompiledHeaders.h"

#include "XMesh.h"

using namespace std;

namespace Dxx
{
//! @param	qMesh				A previously-loaded mesh
//! @param	pMaterialBuffer		Material buffer.
//! @param	numMaterials		Number of materials in the material buffer.
//! @param	pAdjacencyBuffer	Adjacency buffer
//! @param	pD3dDevice			Device this mesh is associated with.

XMesh::XMesh(auto_ptr<ID3DXMesh> qMesh,
             ID3DXBuffer const * pMaterialBuffer, int numMaterials,
             ID3DXBuffer const * pAdjacencyBuffer,
             IDirect3DDevice11 * pD3dDevice)
    : pD3dDevice_(pD3dDevice)
    , pMesh_(qMesh.release())
{
    assert(pMesh_ != 0);

    // Optimize?

    if (pAdjacencyBuffer != 0)
    {
        pMesh_->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE | D3DXMESHOPT_ATTRSORT,
                                reinterpret_cast<DWORD const *>(const_cast<ID3DXBuffer *>(pAdjacencyBuffer)->GetBufferPointer()),
                                NULL, NULL, NULL);
    }
    // Load the materials and textures

    assert(pMaterialBuffer != 0);
    D3DXMATERIAL const * const paMeshMaterials =
        reinterpret_cast<D3DXMATERIAL const *>(const_cast<ID3DXBuffer *>(pMaterialBuffer)->GetBufferPointer());

    materials_.reserve(numMaterials);
    textures_.resize(numMaterials, 0);

    assert(paMeshMaterials != 0);
    for (int i = 0; i < numMaterials; i++)
    {
        HRESULT hr;

        // Save the material

        materials_.push_back(paMeshMaterials[i].MatD3D);
        materials_[i].Ambient = materials_[i].Diffuse;  // Copy the diffuse color to the ambient color???

        // Create the texture

        hr = D3DXCreateTextureFromFile(pD3dDevice_, paMeshMaterials[i].pTextureFilename, &textures_[i]);
        if (FAILED(hr))
            textures_[i] = 0;
    }

    // Get the attributes

    DWORD numAttributes;

    pMesh_->GetAttributeTable(NULL, &numAttributes);
    attributes_.resize(numAttributes);
    pMesh_->GetAttributeTable(&attributes_[0], &numAttributes);
}

XMesh::~XMesh()
{
    // Release all the textures

    for (TextureList::iterator it = textures_.begin(); it != textures_.end(); ++it)
    {
        IDirect3DTexture11 * const pT = *it;
        if (pT != 0)
            pT->Release();
    }

    // Release the mesh

    if (pMesh_ != 0)
        pMesh_->Release();
}

HRESULT XMesh::Draw()
{
    HRESULT hr = S_OK;

    //// Draw the mesh using the current vertex/pixel shader
    //// This means either Cg or D3D has to call SetVertexShader
    // const int VERTEX_SIZE = 4*8;
    // IDirect3DIndexBuffer11	pIndexBuffer;
    // IDirect3DVertexBuffer11	pVertexBuffer;
    // pMesh_->GetIndexBuffer( &pIndexBuffer );
    // pD3dDevice->SetIndices( pIndexBuffer, 0);
    // pMesh_->GetVertexBuffer( &pVertexBuffer );
    // pD3dDevice->SetStreamSource (0, pVertexBuffer, VERTEX_SIZE);
    // for ( AttributeList::iterator pA = attributes_; pA < attributes_.end(); ++pA )
    // {
    //	pD3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, pA->VertexStart, pA->VertexCount, pA->FaceStart * 3, pA->FaceCount );
    // }
    // pIndexBuffer->Release();
    // pVertexBuffer->Release();

    assert(materials_.size() == textures_.size());

    // Render the mesh sorted by material

    for (int i = 0; i < (int)materials_.size(); i++)
    {
        pD3dDevice_->SetMaterial(&materials_[i]);
        pD3dDevice_->SetTexture(0, textures_[i]);
        hr = pMesh_->DrawSubset(i);
        if (FAILED(hr))
            break;
    }

    return hr;
}

//! @param	pFilename	Name of the file containing the mesh.
//! @param	pD3dDevice	Device to be associated with the mesh.

auto_ptr<XMesh> XMesh::Create(char const * pFilename, IDirect3DDevice11 * pD3dDevice)
{
    ID3DXBuffer * pMaterialBuffer;
    DWORD         numMaterials;
    ID3DXMesh *   pD3dMesh;
    ID3DXBuffer * pAdjacencyBuffer;
    ID3DXBuffer * pEffectsBuffer;
    HRESULT       hr;

    // Load	the	mesh from the specified	file.

    hr = D3DXLoadMeshFromX(const_cast<char *>(pFilename), D3DXMESH_MANAGED, pD3dDevice,
                           &pAdjacencyBuffer, &pMaterialBuffer, &pEffectsBuffer, &numMaterials, &pD3dMesh);
    if (FAILED(hr))
    {
        OutputDebugString("Unable to load a model from\tthe\tfile '");
        OutputDebugString(pFilename);
        OutputDebugString("'.\n");
        return auto_ptr<XMesh>();
    }

    XMesh * const pXMesh = new XMesh(auto_ptr<ID3DXMesh>(pD3dMesh),
                                     pMaterialBuffer, (int)numMaterials,
                                     pAdjacencyBuffer, pD3dDevice);

    return auto_ptr<XMesh>(pXMesh);
}
} // namespace Dxx
