static BOOL update_read_draw_gdiplus_first_order(wStream* s,
                                                 DRAW_GDIPLUS_FIRST_ORDER* draw_gdiplus_first)
{
	if (Stream_GetRemainingLength(s) < 11)
		return FALSE;

	Stream_Seek_UINT8(s);                                      
	Stream_Read_UINT16(s, draw_gdiplus_first->cbSize);         
	Stream_Read_UINT32(s, draw_gdiplus_first->cbTotalSize);    
	Stream_Read_UINT32(s, draw_gdiplus_first->cbTotalEmfSize); 
	return Stream_SafeSeek(s, draw_gdiplus_first->cbSize);     
}