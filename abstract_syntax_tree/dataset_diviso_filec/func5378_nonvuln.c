uint8_t *dhcp_get_option(struct dhcp_packet *packet, uint16_t packet_len, int code)
{
	int len, rem;
	uint8_t *optionptr, *options_end;
	size_t options_len;
	uint8_t overload = 0;

	
	optionptr = packet->options;
	rem = sizeof(packet->options);
	options_len = packet_len - (sizeof(*packet) - sizeof(packet->options));
	options_end = optionptr + options_len - 1;

	while (1) {
		if ((rem <= 0) && (optionptr + OPT_CODE > options_end))
			
			return NULL;

		if (optionptr[OPT_CODE] == DHCP_PADDING) {
			rem--;
			optionptr++;

			continue;
		}

		if (optionptr[OPT_CODE] == DHCP_END) {
			if (overload & FILE_FIELD) {
				overload &= ~FILE_FIELD;

				optionptr = packet->file;
				rem = sizeof(packet->file);

				continue;
			} else if (overload & SNAME_FIELD) {
				overload &= ~SNAME_FIELD;

				optionptr = packet->sname;
				rem = sizeof(packet->sname);

				continue;
			}

			break;
		}

		if (optionptr + OPT_LEN > options_end) {
			
			return NULL;
		}

		len = 2 + optionptr[OPT_LEN];

		rem -= len;
		if (rem < 0)
			continue; 

		if (optionptr[OPT_CODE] == code) {
			if (optionptr + len > options_end) {
				
				return NULL;
			} else {
				return optionptr + OPT_DATA;
			}
		}

		if (optionptr[OPT_CODE] == DHCP_OPTION_OVERLOAD)
			overload |= optionptr[OPT_DATA];

		optionptr += len;
	}

	return NULL;
}