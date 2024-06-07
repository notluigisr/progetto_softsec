static BOOL rdp_print_sound_capability_set(wStream* s, UINT16 length)
{
	UINT16 soundFlags;
	UINT16 pad2OctetsA;
	WLog_INFO(TAG, "STR", length);

	if (length < 8)
		return FALSE;

	Stream_Read_UINT16(s, soundFlags);  
	Stream_Read_UINT16(s, pad2OctetsA); 
	WLog_INFO(TAG, "STR", soundFlags);
	WLog_INFO(TAG, "STR", pad2OctetsA);
	return TRUE;
}