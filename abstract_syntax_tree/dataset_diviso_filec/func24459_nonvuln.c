static SDL_INLINE void BG_Blended(const TTF_Image *image, Uint32 *destination, Sint32 srcskip, Uint32 dstskip, Uint8 fg_alpha)
{
    const Uint8 *src    = image->buffer;
    Uint32      *dst    = destination;
    Uint32       width  = image->width;
    Uint32       height = image->rows;

    Uint32 tmp;

    while (height--) {
        
        DUFFS_LOOP4(
            tmp     = fg_alpha * (*src++);
            *dst++ |= DIVIDE_BY_255(tmp) << 24;
        , width);
        
        src += srcskip;
        dst  = (Uint32 *)((Uint8 *)dst + dstskip);
    }
}