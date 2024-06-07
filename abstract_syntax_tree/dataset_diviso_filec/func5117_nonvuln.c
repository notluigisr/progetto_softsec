static BOOL rdp_read_order_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	int i;
	UINT16 orderFlags;
	BYTE orderSupport[32];
	UINT16 orderSupportExFlags;
	BOOL BitmapCacheV3Enabled = FALSE;
	BOOL FrameMarkerCommandEnabled = FALSE;

	if (length < 88)
		return FALSE;

	Stream_Seek(s, 16);                         
	Stream_Seek_UINT32(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Read_UINT16(s, orderFlags);          
	Stream_Read(s, orderSupport, 32);           
	Stream_Seek_UINT16(s);                      
	Stream_Read_UINT16(s, orderSupportExFlags); 
	Stream_Seek_UINT32(s);                      
	Stream_Seek_UINT32(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      
	Stream_Seek_UINT16(s);                      

	for (i = 0; i < 32; i++)
	{
		if (orderSupport[i] == FALSE)
			settings->OrderSupport[i] = FALSE;
	}

	if (orderFlags & ORDER_FLAGS_EXTRA_SUPPORT)
	{
		if (orderSupportExFlags & CACHE_BITMAP_V3_SUPPORT)
			BitmapCacheV3Enabled = TRUE;

		if (orderSupportExFlags & ALTSEC_FRAME_MARKER_SUPPORT)
			FrameMarkerCommandEnabled = TRUE;
	}

	if (settings->BitmapCacheV3Enabled && BitmapCacheV3Enabled)
		settings->BitmapCacheVersion = 3;
	else
		settings->BitmapCacheV3Enabled = FALSE;

	if (settings->FrameMarkerCommandEnabled && !FrameMarkerCommandEnabled)
		settings->FrameMarkerCommandEnabled = FALSE;

	return TRUE;
}