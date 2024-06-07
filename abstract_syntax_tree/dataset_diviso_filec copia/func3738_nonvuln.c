static int check_address_roundtrip(const char *address, int family,
				   const uint8_t *address_bytes,
				   char *buffer, int buffer_len)
{
	
	const char *address_redux = inet_ntop(family, address_bytes,
					      buffer, buffer_len);
	if (address_redux == NULL){
		DBG_INFO("STR"
			 "STR", address, errno);
		return -1;
	}
	if (strcasecmp(address, address_redux) != 0){
		DBG_INFO("STR",
			 address, address_redux);
		
		if (strchr(address_redux, '.') != NULL){
			DEBUG(0, ("STR"
				  "STR"
				  "STR"
				  "STR", address,
				  address_redux));
		}
		return -1;
	}
	return 0;
}