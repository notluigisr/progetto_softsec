static BOOL rdp_read_bitmap_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	BYTE drawingFlags;
	UINT16 desktopWidth;
	UINT16 desktopHeight;
	UINT16 desktopResizeFlag;
	UINT16 preferredBitsPerPixel;

	if (length < 28)
		return FALSE;

	Stream_Read_UINT16(s, preferredBitsPerPixel); 
	Stream_Seek_UINT16(s);                        
	Stream_Seek_UINT16(s);                        
	Stream_Seek_UINT16(s);                        
	Stream_Read_UINT16(s, desktopWidth);          
	Stream_Read_UINT16(s, desktopHeight);         
	Stream_Seek_UINT16(s);                        
	Stream_Read_UINT16(s, desktopResizeFlag);     
	Stream_Seek_UINT16(s);                        
	Stream_Seek_UINT8(s);                         
	Stream_Read_UINT8(s, drawingFlags);           
	Stream_Seek_UINT16(s);                        
	Stream_Seek_UINT16(s);                        

	if (!settings->ServerMode && (preferredBitsPerPixel != settings->ColorDepth))
	{
		
		settings->ColorDepth = preferredBitsPerPixel;
	}

	if (desktopResizeFlag == FALSE)
		settings->DesktopResize = FALSE;

	if (!settings->ServerMode && settings->DesktopResize)
	{
		
		settings->DesktopWidth = desktopWidth;
		settings->DesktopHeight = desktopHeight;
	}

	if (settings->DrawAllowSkipAlpha)
		settings->DrawAllowSkipAlpha = (drawingFlags & DRAW_ALLOW_SKIP_ALPHA) ? TRUE : FALSE;

	if (settings->DrawAllowDynamicColorFidelity)
		settings->DrawAllowDynamicColorFidelity =
		    (drawingFlags & DRAW_ALLOW_DYNAMIC_COLOR_FIDELITY) ? TRUE : FALSE;

	if (settings->DrawAllowColorSubsampling)
		settings->DrawAllowColorSubsampling =
		    (drawingFlags & DRAW_ALLOW_COLOR_SUBSAMPLING) ? TRUE : FALSE;

	return TRUE;
}