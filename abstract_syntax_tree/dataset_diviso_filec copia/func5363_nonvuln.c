int rdp_recv_data_pdu(rdpRdp* rdp, STREAM* s)
{
	BYTE type;
	UINT16 length;
	UINT32 share_id;
	BYTE compressed_type;
	UINT16 compressed_len;
	UINT32 roff;
	UINT32 rlen;
	STREAM* comp_stream;

	if (!rdp_read_share_data_header(s, &length, &type, &share_id, &compressed_type, &compressed_len))
		return -1;

	comp_stream = s;

	if (compressed_type & PACKET_COMPRESSED)
	{
		if (stream_get_left(s) < compressed_len - 18)
		{
			printf("STR", compressed_len);
			return -1;	
		}
		if (decompress_rdp(rdp->mppc_dec, s->p, compressed_len - 18, compressed_type, &roff, &rlen))
		{
			comp_stream = stream_new(0);
			comp_stream->data = rdp->mppc_dec->history_buf + roff;
			comp_stream->p = comp_stream->data;
			comp_stream->size = rlen;
		}
		else
		{
			printf("STR");
			return -1;
		}
		stream_seek(s, compressed_len - 18);
	}

#ifdef WITH_DEBUG_RDP
	
		DEBUG_RDP("STR",
				type < ARRAYSIZE(DATA_PDU_TYPE_STRINGS) ? DATA_PDU_TYPE_STRINGS[type] : "STR", type, length);
#endif

	switch (type)
	{
		case DATA_PDU_TYPE_UPDATE:
			if (!update_recv(rdp->update, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_CONTROL:
			if (!rdp_recv_server_control_pdu(rdp, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_POINTER:
			if (!update_recv_pointer(rdp->update, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_INPUT:
			break;

		case DATA_PDU_TYPE_SYNCHRONIZE:
			if (!rdp_recv_synchronize_pdu(rdp, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_REFRESH_RECT:
			break;

		case DATA_PDU_TYPE_PLAY_SOUND:
			if (!update_recv_play_sound(rdp->update, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_SUPPRESS_OUTPUT:
			break;

		case DATA_PDU_TYPE_SHUTDOWN_REQUEST:
			break;

		case DATA_PDU_TYPE_SHUTDOWN_DENIED:
			break;

		case DATA_PDU_TYPE_SAVE_SESSION_INFO:
			if(!rdp_recv_save_session_info(rdp, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_FONT_LIST:
			break;

		case DATA_PDU_TYPE_FONT_MAP:
			if(!rdp_recv_font_map_pdu(rdp, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_SET_KEYBOARD_INDICATORS:
			break;

		case DATA_PDU_TYPE_BITMAP_CACHE_PERSISTENT_LIST:
			break;

		case DATA_PDU_TYPE_BITMAP_CACHE_ERROR:
			break;

		case DATA_PDU_TYPE_SET_KEYBOARD_IME_STATUS:
			break;

		case DATA_PDU_TYPE_OFFSCREEN_CACHE_ERROR:
			break;

		case DATA_PDU_TYPE_SET_ERROR_INFO:
			if (!rdp_recv_set_error_info_data_pdu(rdp, comp_stream))
				return -1;
			break;

		case DATA_PDU_TYPE_DRAW_NINEGRID_ERROR:
			break;

		case DATA_PDU_TYPE_DRAW_GDIPLUS_ERROR:
			break;

		case DATA_PDU_TYPE_ARC_STATUS:
			break;

		case DATA_PDU_TYPE_STATUS_INFO:
			break;

		case DATA_PDU_TYPE_MONITOR_LAYOUT:
			break;

		default:
			break;
	}

	if (comp_stream != s)
	{
		stream_detach(comp_stream);
		stream_free(comp_stream);
	}

	return 0;
}