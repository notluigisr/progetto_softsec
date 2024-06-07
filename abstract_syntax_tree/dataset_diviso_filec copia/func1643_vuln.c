UINT rdpgfx_read_rect16(wStream* s, RECTANGLE_16* rect16)
{
	if (Stream_GetRemainingLength(s) < 8)
	{
		WLog_ERR(TAG, "STR");
		return ERROR_INVALID_DATA;
	}

	Stream_Read_UINT16(s, rect16->left);   
	Stream_Read_UINT16(s, rect16->top);    
	Stream_Read_UINT16(s, rect16->right);  
	Stream_Read_UINT16(s, rect16->bottom); 
	return CHANNEL_RC_OK;
}