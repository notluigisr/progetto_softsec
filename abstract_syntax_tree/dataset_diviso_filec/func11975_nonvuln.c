static void rdp_print_bitmap_codec_guid(const GUID* guid)
{
	WLog_INFO(TAG,
	          "STR" PRIX8
	          "STR",
	          guid->Data1, guid->Data2, guid->Data3, guid->Data4[0], guid->Data4[1], guid->Data4[2],
	          guid->Data4[3], guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]);
}