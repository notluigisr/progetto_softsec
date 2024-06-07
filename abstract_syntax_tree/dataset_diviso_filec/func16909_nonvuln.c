
static SDL_INLINE FT_UInt get_char_index(TTF_Font *font, Uint32 ch)
{
    Uint32 cache_index_size = sizeof (font->cache_index) / sizeof (font->cache_index[0]);

    if (ch < cache_index_size) {
        FT_UInt idx = font->cache_index[ch];
        if (idx) {
            return idx;
        }
        idx = FT_Get_Char_Index(font->face, ch);
        font->cache_index[ch] = idx;
        return idx;
    }

    return FT_Get_Char_Index(font->face, ch);