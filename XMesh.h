/** @file *//********************************************************************************************************

                                                       XMesh.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Dxx/XMesh.h#14 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif
#include <boost/noncopyable.hpp>
#include <d3d9.h>
#include <d3dx9.h>
#include <memory>
#include <vector>

namespace Dxx
{
//! A mesh loaded from a .X file.
//
//! @ingroup	D3dx
//!

class XMesh : public boost::noncopyable
{
public:

    // Constructor
    XMesh(std::auto_ptr<ID3DXMesh> qMesh,
          ID3DXBuffer const * pMaterialBuffer, int numMaterials,
          ID3DXBuffer const * pAdjacencyBuffer,
          IDirect3DDevice11 * pD3dDevice);

    // Destructor
    virtual ~XMesh();

    //! Renders the mesh. Returns a result code.
    HRESULT Draw();

    //! Loads an .X file creating an XMesh. Returns a pointer to the new mesh.
    static std::auto_ptr<XMesh> Create(char const * pFilename, IDirect3DDevice11 * pD3dDevice);

private:

    typedef std::vector<D3DMATERIAL9>         MaterialList;     //!< A list of materials
    typedef std::vector<IDirect3DTexture11 *>  TextureList;      //!< A list of textures
    typedef std::vector<D3DXATTRIBUTERANGE>   AttributeList;    //!< A list of attributes

    IDirect3DDevice11 * pD3dDevice_;         //!< The device this mesh is associated with
    ID3DXMesh * pMesh_;                 //!< The mesh.
    MaterialList materials_;            //!< The materials used by the mesh.
    TextureList textures_;                  //!< The textures used by the mesh.
    AttributeList attributes_;              //!< The mesh's attributes.
};
} // namespace Dxx
