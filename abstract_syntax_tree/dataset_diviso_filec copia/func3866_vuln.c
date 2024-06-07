static inline exporter_v9_domain_t *GetExporter(FlowSource_t *fs, uint32_t exporter_id) {

char ipstr[IP_STRING_LEN];
exporter_v9_domain_t **e = (exporter_v9_domain_t **)&(fs->exporter_data);

	while ( *e ) {
		if ( (*e)->info.id == exporter_id && (*e)->info.version == 9 && 
			 (*e)->info.ip.v6[0] == fs->ip.v6[0] && (*e)->info.ip.v6[1] == fs->ip.v6[1]) 
			return *e;
		e = &((*e)->next);
	}

	if ( fs->sa_family == AF_INET ) {
		uint32_t _ip = htonl(fs->ip.v4);
		inet_ntop(AF_INET, &_ip, ipstr, sizeof(ipstr));
	} else if ( fs->sa_family == AF_INET6 ) {
		uint64_t _ip[2];
		_ip[0] = htonll(fs->ip.v6[0]);
		_ip[1] = htonll(fs->ip.v6[1]);
		inet_ntop(AF_INET6, &_ip, ipstr, sizeof(ipstr));
	} else {
		strncpy(ipstr, "STR", IP_STRING_LEN);
	}

	
	*e = (exporter_v9_domain_t *)malloc(sizeof(exporter_v9_domain_t));
	if ( !(*e)) {
		syslog(LOG_ERR, "STR", __FILE__, __LINE__, strerror (errno));
		return NULL;
	}
	memset((void *)(*e), 0, sizeof(exporter_v9_domain_t));
	(*e)->info.header.type  = ExporterInfoRecordType;
	(*e)->info.header.size  = sizeof(exporter_info_record_t);
	(*e)->info.version 		= 9;
	(*e)->info.id 			= exporter_id;
	(*e)->info.ip			= fs->ip;
	(*e)->info.sa_family	= fs->sa_family;
	(*e)->info.sysid 		= 0;

	(*e)->first	 			= 1;
	(*e)->sequence_failure	= 0;

	(*e)->sampler 	 = NULL;
	(*e)->next	 	 = NULL;

	FlushInfoExporter(fs, &((*e)->info));

	dbg_printf("STR", 
		(*e)->info.sysid, exporter_id, ipstr);
	syslog(LOG_INFO, "STR", 
		(*e)->info.sysid, exporter_id, ipstr);


	return (*e);

} 