BOOL glyph_cache_put(rdpGlyphCache* glyphCache, UINT32 id, UINT32 index, rdpGlyph* glyph)
{
	rdpGlyph* prevGlyph;

	if (id > 9)
	{
		WLog_ERR(TAG, "STR", id);
		return FALSE;
	}

	if (index > glyphCache->glyphCache[id].number)
	{
		WLog_ERR(TAG, "STR", index, id);
		return FALSE;
	}

	WLog_Print(glyphCache->log, WLOG_DEBUG, "STR", id,
	           index);
	prevGlyph = glyphCache->glyphCache[id].entries[index];

	if (prevGlyph)
		prevGlyph->Free(glyphCache->context, prevGlyph);

	glyphCache->glyphCache[id].entries[index] = glyph;
	return TRUE;
}