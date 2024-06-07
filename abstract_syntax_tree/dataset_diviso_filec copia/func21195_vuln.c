rdpdr_process(STREAM s)
{
	uint32 handle;
	uint16 vmin;
	uint16 component;
	uint16 pakid;

#if WITH_DEBUG_RDP5
	printf("STR");
	hexdump(s->p, s->end - s->p);
#endif

	in_uint16(s, component);
	in_uint16(s, pakid);

	if (component == RDPDR_CTYP_CORE)
	{
		switch (pakid)
		{
			case PAKID_CORE_DEVICE_IOREQUEST:
				rdpdr_process_irp(s);
				break;

			case PAKID_CORE_SERVER_ANNOUNCE:
				
				in_uint8s(s, 2);	
				in_uint16_le(s, vmin);	
				in_uint32_le(s, g_client_id);	

				
				if (vmin < 0x000c)
					g_client_id = 0x815ed39d;	
				g_epoch++;

				rdpdr_send_client_announce_reply();
				rdpdr_send_client_name_request();
				break;

			case PAKID_CORE_CLIENTID_CONFIRM:
				rdpdr_send_client_device_list_announce();
				break;

			case PAKID_CORE_DEVICE_REPLY:
				in_uint32(s, handle);
#if WITH_DEBUG_RDP5
				DEBUG(("STR", handle));
#endif
				break;

			case PAKID_CORE_SERVER_CAPABILITY:
				rdpdr_send_client_capability_response();
				break;

			default:
				unimpl("STR", pakid, component);
				break;

		}
	}
	else if (component == RDPDR_CTYP_PRN)
	{
		if (pakid == PAKID_PRN_CACHE_DATA)
			printercache_process(s);
	}
	else
		unimpl("STR", component);
}