process_secondary_order(STREAM s)
{
	
	uint16 length;
	uint16 flags;
	uint8 type;
	uint8 *next_order;

	in_uint16_le(s, length);
	in_uint16_le(s, flags);	
	in_uint8(s, type);

	next_order = s->p + (sint16) length + 7;

	switch (type)
	{
		case RDP_ORDER_RAW_BMPCACHE:
			process_raw_bmpcache(s);
			break;

		case RDP_ORDER_COLCACHE:
			process_colcache(s);
			break;

		case RDP_ORDER_BMPCACHE:
			process_bmpcache(s);
			break;

		case RDP_ORDER_FONTCACHE:
			process_fontcache(s);
			break;

		case RDP_ORDER_RAW_BMPCACHE2:
			process_bmpcache2(s, flags, False);	
			break;

		case RDP_ORDER_BMPCACHE2:
			process_bmpcache2(s, flags, True);	
			break;

		case RDP_ORDER_BRUSHCACHE:
			process_brushcache(s, flags);
			break;

		default:
			logger(Graphics, Warning,
			       "STR", type);
	}

	s->p = next_order;
}