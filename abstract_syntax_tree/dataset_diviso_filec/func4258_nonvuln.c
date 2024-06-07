static BOOL rdp_read_draw_nine_grid_cache_capability_set(wStream* s, UINT16 length,
                                                         rdpSettings* settings)
{
	UINT32 drawNineGridSupportLevel;

	if (length < 12)
		return FALSE;

	Stream_Read_UINT32(s, drawNineGridSupportLevel);        
	Stream_Read_UINT16(s, settings->DrawNineGridCacheSize); 
	Stream_Read_UINT16(s,
	                   settings->DrawNineGridCacheEntries); 

	if ((drawNineGridSupportLevel & DRAW_NINEGRID_SUPPORTED) ||
	    (drawNineGridSupportLevel & DRAW_NINEGRID_SUPPORTED_V2))
		settings->DrawNineGridEnabled = TRUE;

	return TRUE;
}