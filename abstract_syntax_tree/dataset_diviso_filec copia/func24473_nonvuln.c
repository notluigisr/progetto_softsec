static BOOL rdp_write_glyph_cache_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;
	if (settings->GlyphSupportLevel > UINT16_MAX)
		return FALSE;
	
	rdp_write_cache_definition(s, &(settings->GlyphCache[0])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[1])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[2])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[3])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[4])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[5])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[6])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[7])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[8])); 
	rdp_write_cache_definition(s, &(settings->GlyphCache[9])); 
	rdp_write_cache_definition(s, settings->FragCache);        
	Stream_Write_UINT16(s, (UINT16)settings->GlyphSupportLevel); 
	Stream_Write_UINT16(s, 0);                                 
	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_GLYPH_CACHE);
	return TRUE;
}