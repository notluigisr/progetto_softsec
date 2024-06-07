static int rdp_recv_tpkt_pdu(rdpRdp* rdp, STREAM* s)
{
	UINT16 length;
	UINT16 pduType;
	UINT16 pduLength;
	UINT16 pduSource;
	UINT16 channelId;
	UINT16 securityFlags;
	BYTE* nextp;

	if (!rdp_read_header(rdp, s, &length, &channelId))
	{
		printf("STR");
		return -1;
	}

	if (rdp->settings->DisableEncryption)
	{
		if (!rdp_read_security_header(s, &securityFlags))
			return -1;

		if (securityFlags & (SEC_ENCRYPT | SEC_REDIRECTION_PKT))
		{
			if (!rdp_decrypt(rdp, s, length - 4, securityFlags))
			{
				printf("STR");
				return -1;
			}
		}

		if (securityFlags & SEC_REDIRECTION_PKT)
		{
			
			s->p -= 2;
			rdp_recv_enhanced_security_redirection_packet(rdp, s);
			return -1;
		}
	}

	if (channelId != MCS_GLOBAL_CHANNEL_ID)
	{
		if (!freerdp_channel_process(rdp->instance, s, channelId))
			return -1;
	}
	else
	{
		while (stream_get_left(s) > 3)
		{
			stream_get_mark(s, nextp);

			if (!rdp_read_share_control_header(s, &pduLength, &pduType, &pduSource))
				return -1;

			nextp += pduLength;

			rdp->settings->PduSource = pduSource;

			switch (pduType)
			{
				case PDU_TYPE_DATA:
					if (rdp_recv_data_pdu(rdp, s) < 0)
					{
						printf("STR");
						return -1;
					}
					break;

				case PDU_TYPE_DEACTIVATE_ALL:
					if (!rdp_recv_deactivate_all(rdp, s))
						return -1;
					break;

				case PDU_TYPE_SERVER_REDIRECTION:
					if (!rdp_recv_enhanced_security_redirection_packet(rdp, s))
						return -1;
					break;

				default:
					printf("STR", pduType);
					break;
			}
			stream_set_mark(s, nextp);
		}
	}

	return 0;
}