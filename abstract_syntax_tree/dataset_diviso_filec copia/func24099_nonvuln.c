static BOOL rdg_send_channel_create(rdpRdg* rdg)
{
	wStream* s = NULL;
	BOOL status = FALSE;
	WCHAR* serverName = NULL;
	int serverNameLen =
	    ConvertToUnicode(CP_UTF8, 0, rdg->settings->ServerHostname, -1, &serverName, 0);
	UINT32 packetSize = 16 + ((UINT32)serverNameLen) * 2;

	if ((serverNameLen < 0) || (serverNameLen > UINT16_MAX / 2))
		goto fail;

	s = Stream_New(NULL, packetSize);

	if (!s)
		goto fail;

	Stream_Write_UINT16(s, PKT_TYPE_CHANNEL_CREATE); 
	Stream_Write_UINT16(s, 0);                       
	Stream_Write_UINT32(s, packetSize);              
	Stream_Write_UINT8(s, 1);                        
	Stream_Write_UINT8(s, 0);                        
	Stream_Write_UINT16(s, (UINT16)rdg->settings->ServerPort); 
	Stream_Write_UINT16(s, 3);                                 
	Stream_Write_UINT16(s, (UINT16)serverNameLen * 2);
	Stream_Write_UTF16_String(s, serverName, (size_t)serverNameLen);
	Stream_SealLength(s);
	status = rdg_write_packet(rdg, s);
fail:
	free(serverName);
	Stream_Free(s, TRUE);

	if (status)
		rdg->state = RDG_CLIENT_STATE_CHANNEL_CREATE;

	return status;
}