#include <sdlpp/Gui/Surface.h>
#include <sdlpp/Gui/Window.h>
#include <sdlpp/Core/Logging.h>

namespace sdl
{

rad::Ref<Surface> Surface::Create(int width, int height, SDL_PixelFormat format)
{
    SDL_Surface* handle = SDL_CreateSurface(width, height, format);
    if (handle)
    {
        return RAD_NEW Surface(handle, true);
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_CreateSurface failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<Surface> Surface::CreateFormPixels(
    int width, int height, SDL_PixelFormat format, void* pixels, int pitch)
{
    SDL_Surface* handle = SDL_CreateSurfaceFrom(width, height, format, pixels, pitch);
    if (handle)
    {
        return RAD_NEW Surface(handle, true);
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_CreateSurfaceFrom failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<Surface> Surface::CreateFromBMP(SDL_IOStream* src, SDL_bool closeio)
{
    SDL_Surface* handle = SDL_LoadBMP_IO(src, closeio);
    if (handle)
    {
        return RAD_NEW Surface(handle, true);
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_LoadBMP_IO failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<Surface> Surface::CreateFromBMP(const char* file)
{
    SDL_Surface* handle = SDL_LoadBMP(file);
    if (handle)
    {
        return RAD_NEW Surface(handle, true);
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_LoadBMP_IO failed: {}", SDL_GetError());
        return nullptr;
    }
}

Surface::Surface(SDL_Surface* handle, bool isManaged) :
    m_handle(handle),
    m_isManaged(isManaged)
{
    m_propID = SDL_GetSurfaceProperties(m_handle);
    if (m_propID == 0)
    {
        RAD_LOG(GetLogger(), err, "SDL_GetSurfaceProperties failed: {}", SDL_GetError());
    }
}

Surface::~Surface()
{
    Destroy();
}

void Surface::Destroy()
{
    if (m_handle && m_isManaged)
    {
        SDL_DestroySurface(m_handle);
        m_handle = nullptr;
    }
}

bool Surface::SaveBMP(SDL_IOStream* dst, SDL_bool closeio)
{
    SDL_bool result = SDL_SaveBMP_IO(m_handle, dst, closeio);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SaveBMP_IO failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::SaveBMP(const char* file)
{
    SDL_bool result = SDL_SaveBMP(m_handle, file);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SaveBMP failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::SetColorSpace(SDL_Colorspace colorspace)
{
    SDL_bool result = SDL_SetSurfaceColorspace(m_handle, colorspace);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceColorspace failed: {}", SDL_GetError());
        return false;
    }
}

SDL_Colorspace Surface::GetColorSpace(SDL_Colorspace* colorspace)
{
    return SDL_GetSurfaceColorspace(m_handle);
}

bool Surface::SetPalette(SDL_Palette* palette)
{
    SDL_bool result = SDL_SetSurfacePalette(m_handle, palette);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfacePalette failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::Lock()
{
    SDL_bool result = SDL_LockSurface(m_handle);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_LockSurface failed: {}", SDL_GetError());
        return false;
    }
}

void Surface::Unlock()
{
    SDL_UnlockSurface(m_handle);
}

bool Surface::SetRLE(int flag)
{
    SDL_bool result = SDL_SetSurfaceRLE(m_handle, flag);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceRLE failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::HasRLE()
{
    return (SDL_SurfaceHasRLE(m_handle) == SDL_TRUE);
}

bool Surface::SetColorKey(int flag, Uint32 key)
{
    SDL_bool result = SDL_SetSurfaceColorKey(m_handle, flag, key);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceColorKey failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::HasColorKey()
{
    return (SDL_SurfaceHasColorKey(m_handle) == SDL_TRUE);
}

bool Surface::GetColorKey(Uint32* key)
{
    SDL_bool result = SDL_GetSurfaceColorKey(m_handle, key);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_GetSurfaceColorKey failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::SetColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_bool result = SDL_SetSurfaceColorMod(m_handle, r, g, b);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceColorMod failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::GetColorMod(Uint8* r, Uint8* g, Uint8* b)
{
    SDL_bool result = SDL_GetSurfaceColorMod(m_handle, r, g, b);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_GetSurfaceColorMod failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::SetAlphaMode(Uint8 alpha)
{
    SDL_bool result = SDL_SetSurfaceAlphaMod(m_handle, alpha);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceAlphaMod failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::GetAlphaMode(Uint8* alpha)
{
    SDL_bool result = SDL_GetSurfaceAlphaMod(m_handle, alpha);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_GetSurfaceAlphaMod failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::SetBlendMode(SDL_BlendMode blendMode)
{
    SDL_bool result = SDL_SetSurfaceBlendMode(m_handle, blendMode);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceBlendMode failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::GetBlendMode(SDL_BlendMode* blendMode)
{
    SDL_bool result = SDL_GetSurfaceBlendMode(m_handle, blendMode);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_GetSurfaceBlendMode failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::SetClipRect(const SDL_Rect* rect)
{
    SDL_bool result = SDL_SetSurfaceClipRect(m_handle, rect);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_SetSurfaceClipRect failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::DisableClipping()
{
    return SetClipRect(nullptr);
}

bool Surface::GetClipRect(SDL_Rect* rect)
{
    SDL_bool result = SDL_GetSurfaceClipRect(m_handle, rect);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_GetSurfaceClipRect failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::Flip(SDL_FlipMode flip)
{
    SDL_bool result = SDL_FlipSurface(m_handle, flip);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_FlipSurface failed: {}", SDL_GetError());
        return false;
    }
}

rad::Ref<Surface> Surface::Duplicate()
{
    SDL_Surface* handle = SDL_DuplicateSurface(m_handle);
    if (handle)
    {
        return rad::Ref<Surface>(RAD_NEW Surface(handle, true));
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_DuplicateSurface failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<Surface> Surface::Convert(SDL_PixelFormat format)
{
    SDL_Surface* handle = SDL_ConvertSurface(m_handle, format);
    if (handle)
    {
        return rad::Ref<Surface>(RAD_NEW Surface(handle, true));
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_ConvertSurface failed: {}", SDL_GetError());
        return nullptr;
    }
}

rad::Ref<Surface> Surface::Convert(
    SDL_PixelFormat format, SDL_Palette* palette, SDL_Colorspace colorspace, SDL_PropertiesID props)
{
    SDL_Surface* handle = SDL_ConvertSurfaceAndColorspace(
        m_handle, format, palette, colorspace, props);
    if (handle)
    {
        return rad::Ref<Surface>(RAD_NEW Surface(handle, true));
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_ConvertSurfaceFormatAndColorspace failed: {}", SDL_GetError());
        return nullptr;
    }
}

bool Surface::PremultiplyAlpha(bool linear)
{
    SDL_bool result = SDL_PremultiplySurfaceAlpha(m_handle, linear ? SDL_TRUE : SDL_FALSE);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_PremultiplySurfaceAlpha failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::Clear(float r, float g, float b, float a)
{
    SDL_bool result = SDL_ClearSurface(m_handle, r, g, b, a);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_ClearSurface failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::FillRect(const SDL_Rect* rect, Uint32 color)
{
    SDL_bool result = SDL_FillSurfaceRect(m_handle, rect, color);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_FillSurfaceRect failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::FillRects(const SDL_Rect* rects, int count, Uint32 color)
{
    SDL_bool result = SDL_FillSurfaceRects(m_handle, rects, count, color);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_FillSurfaceRects failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::Blit(Surface* src, const SDL_Rect* srcRect, Surface* dst, SDL_Rect* dstRect)
{
    SDL_bool result = SDL_BlitSurface(src->GetHandle(), srcRect, dst->GetHandle(), dstRect);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_BlitSurface failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::BlitUnchecked(Surface* src, const SDL_Rect* srcRect, Surface* dst, const SDL_Rect* dstRect)
{
    SDL_bool result = SDL_BlitSurfaceUnchecked(
        src->GetHandle(), srcRect, dst->GetHandle(), dstRect);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_BlitSurfaceUnchecked failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::BlitScaled(Surface* src, const SDL_Rect* srcRect,
    Surface* dst, SDL_Rect* dstRect, SDL_ScaleMode scaleMode)
{
    SDL_bool result = SDL_BlitSurfaceScaled(src->GetHandle(), srcRect, dst->GetHandle(), dstRect, scaleMode);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_BlitSurfaceScaled failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::BlitUncheckedScaled(Surface* src, const SDL_Rect* srcRect,
    Surface* dst, SDL_Rect* dstRect, SDL_ScaleMode scaleMode)
{
    SDL_bool result = SDL_BlitSurfaceUncheckedScaled(
        src->GetHandle(), srcRect, dst->GetHandle(), dstRect, scaleMode);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_BlitSurfaceUncheckedScaled failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::BlitTiled(Surface* src, const SDL_Rect* srcRect, Surface* dst, SDL_Rect* dstRect)
{
    SDL_bool result = SDL_BlitSurfaceTiled(src->GetHandle(), srcRect, dst->GetHandle(), dstRect);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_BlitSurfaceTiled failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::BlitTiledWithScale(Surface* src, const SDL_Rect* srcRect,
    float scale, SDL_ScaleMode scaleMode,
    Surface* dst, const SDL_Rect* dstRect)
{
    SDL_bool result = SDL_BlitSurfaceTiledWithScale(src->GetHandle(), srcRect, scale, scaleMode,
        dst->GetHandle(), dstRect);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_BlitSurfaceTiledWithScale failed: {}", SDL_GetError());
        return false;
    }
}

bool Surface::Blit9Grid(Surface* src, const SDL_Rect* srcRect,
    int cornerSize, float scale, SDL_ScaleMode scaleMode,
    SDL_Surface* dst, const SDL_Rect* dstRect)
{
    return false;
}

bool Surface::ReadPixel(int x, int y, Uint8* r, Uint8* g, Uint8* b, Uint8* a)
{
    SDL_bool result = SDL_ReadSurfacePixel(m_handle, x, y, r, g, b, a);
    if (result == SDL_TRUE)
    {
        return true;
    }
    else
    {
        RAD_LOG(GetLogger(), err, "SDL_ReadSurfacePixel failed: {}", SDL_GetError());
        return false;
    }
}

} // namespace sdl
