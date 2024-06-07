rdp_loop(RD_BOOL * deactivated, uint32 * ext_disc_reason)
{
	uint8 type;
	RD_BOOL cont = True;
	STREAM s;

	while (cont)
	{
		s = rdp_recv(&type);
		if (s == NULL)
			return False;
		switch (type)
		{
			case RDP_PDU_DEMAND_ACTIVE:
				process_demand_active(s);
				*deactivated = False;
				break;
			case RDP_PDU_DEACTIVATE:
				DEBUG(("STR"));
				*deactivated = True;
				break;
			case RDP_PDU_REDIRECT:
				return process_redirect_pdu(s, False);
				break;
			case RDP_PDU_ENHANCED_REDIRECT:
				return process_redirect_pdu(s, True);
				break;
			case RDP_PDU_DATA:
				
				if (g_password[0] != '\0')
					memset(g_password, 0, sizeof(g_password));

				process_data_pdu(s, ext_disc_reason);
				break;
			case 0:
				break;
			default:
				unimpl("STR", type);
		}
		cont = g_next_packet < s->end;
	}
	return True;
}