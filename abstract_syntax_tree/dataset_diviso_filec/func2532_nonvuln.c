static BOOL rdp_print_bitmap_codecs_capability_set(wStream* s, UINT16 length)
{
	GUID codecGuid;
	BYTE bitmapCodecCount;
	BYTE codecId;
	UINT16 codecPropertiesLength;
	UINT16 remainingLength;
	WLog_INFO(TAG, "STR", length);

	if (length < 5)
		return FALSE;

	Stream_Read_UINT8(s, bitmapCodecCount); 
	remainingLength = length - 5;
	WLog_INFO(TAG, "STR", bitmapCodecCount);

	while (bitmapCodecCount > 0)
	{
		if (remainingLength < 19)
			return FALSE;

		rdp_read_bitmap_codec_guid(s, &codecGuid); 
		Stream_Read_UINT8(s, codecId);             
		WLog_INFO(TAG, "STR");
		rdp_print_bitmap_codec_guid(&codecGuid);
		WLog_INFO(TAG, "STR", rdp_get_bitmap_codec_guid_name(&codecGuid));
		WLog_INFO(TAG, "STR", codecId);
		Stream_Read_UINT16(s, codecPropertiesLength); 
		WLog_INFO(TAG, "STR", codecPropertiesLength);
		remainingLength -= 19;

		if (remainingLength < codecPropertiesLength)
			return FALSE;

		Stream_Seek(s, codecPropertiesLength); 
		remainingLength -= codecPropertiesLength;
		bitmapCodecCount--;
	}

	return TRUE;
}