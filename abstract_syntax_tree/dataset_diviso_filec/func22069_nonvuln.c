void dhcp_add_option_uint8(struct dhcp_packet *packet, uint8_t code,
							uint8_t data)
{
	uint8_t option[6];

	if (check_option(code, sizeof(data)) == OPTION_UNKNOWN)
		return;

	option[OPT_CODE] = code;
	option[OPT_LEN] = sizeof(data);
	option[OPT_DATA] = data;

	dhcp_add_binary_option(packet, option);
}