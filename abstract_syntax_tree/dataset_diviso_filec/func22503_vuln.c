uint8_t* FAST_FUNC udhcp_get_option(struct dhcp_packet *packet, int code)
{
	uint8_t *optionptr;
	int len;
	int rem;
	int overload = 0;
	enum {
		FILE_FIELD101  = FILE_FIELD  * 0x101,
		SNAME_FIELD101 = SNAME_FIELD * 0x101,
	};

	
	optionptr = packet->options;
	rem = sizeof(packet->options);
	while (1) {
		if (rem <= 0) {
 complain:
			bb_error_msg("STR");
			return NULL;
		}

		
		if (optionptr[OPT_CODE] == DHCP_PADDING) {
			rem--;
			optionptr++;
			continue;
		}
		if (optionptr[OPT_CODE] == DHCP_END) {
			if ((overload & FILE_FIELD101) == FILE_FIELD) {
				
				overload |= FILE_FIELD101; 
				optionptr = packet->file;
				rem = sizeof(packet->file);
				continue;
			}
			if ((overload & SNAME_FIELD101) == SNAME_FIELD) {
				
				overload |= SNAME_FIELD101; 
				optionptr = packet->sname;
				rem = sizeof(packet->sname);
				continue;
			}
			break;
		}

		if (rem <= OPT_LEN)
			goto complain; 
		len = 2 + optionptr[OPT_LEN];
		rem -= len;
		if (rem < 0)
			goto complain; 

		if (optionptr[OPT_CODE] == code) {
			log_option("STR", optionptr);
			return optionptr + OPT_DATA;
		}

		if (optionptr[OPT_CODE] == DHCP_OPTION_OVERLOAD) {
			if (len >= 3)
				overload |= optionptr[OPT_DATA];
			
		}
		optionptr += len;
	}

	
	log3("STR", code);
	return NULL;
}