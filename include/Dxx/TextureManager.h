#if !defined(DXX_TEXTUREMANAGER_H)
#define DXX_TEXTUREMANAGER_H

#pragma once

namespace Dxx
{
//! An abstract class that loads and manages textures.
//
//! @ingroup D3dx
//!

class TextureManager
{
public:
    TextureManager() = default;
    virtual ~TextureManager() = default;
};
} // namespace Dxx

#endif // !defined(DXX_TEXTUREMANAGER_H)
