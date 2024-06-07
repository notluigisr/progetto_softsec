zfont_mark_glyph_name(const gs_memory_t *mem, gs_glyph glyph, void *ignore_data)
{
    return (glyph >= gs_c_min_std_encoding_glyph || glyph == GS_NO_GLYPH ? false :
            name_mark_index(mem, (uint) glyph));
}