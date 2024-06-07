int Init_IPFIX(void) {
int i;

	cache.lookup_info	    = (struct element_param_s *)calloc(65536, sizeof(struct element_param_s));
	cache.common_extensions = (uint32_t *)malloc((Max_num_extensions+1)*sizeof(uint32_t));
	if ( !cache.common_extensions || !cache.lookup_info ) {
		syslog(LOG_ERR, "STR", __FILE__, __LINE__, strerror (errno));
		return 0;
	}

	
	for (i=1; ipfix_element_map[i].id != 0; i++ ) {
		uint32_t Type = ipfix_element_map[i].id;
		
		
		if ( cache.lookup_info[Type].index == 0 ) 
			cache.lookup_info[Type].index  = i;
	}
	cache.max_ipfix_elements = i;

	syslog(LOG_DEBUG,"STR", cache.max_ipfix_elements);

	return 1;

} 