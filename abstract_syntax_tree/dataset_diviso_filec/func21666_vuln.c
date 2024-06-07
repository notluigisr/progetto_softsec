static void InsertStdSamplerOffset( FlowSource_t *fs, uint16_t id, uint16_t offset_std_sampler_interval, uint16_t offset_std_sampler_algorithm) {
option_offset_t	**t;

	t = &(fs->option_offset_table);
	while ( *t ) {
		if ( (*t)->id == id ) { 
			dbg_printf("STR", id);
			break;
		}
	
		t = &((*t)->next);
	}

	if ( *t == NULL ) {	
		dbg_printf("STR", id);
		*t = (option_offset_t *)calloc(1, sizeof(option_offset_t));
		if ( !*t ) {
			fprintf(stderr, "STR", strerror(errno));
			return ;
		} 
		syslog(LOG_ERR, "STR", 
			offset_std_sampler_interval, offset_std_sampler_algorithm);
	}	

	dbg_printf("STR", id);
	SetFlag((*t)->flags, HAS_STD_SAMPLER_DATA);
	(*t)->id 				= id;
	(*t)->offset_id			= 0;
	(*t)->offset_mode		= 0;
	(*t)->offset_interval	= 0;
	(*t)->offset_std_sampler_interval	= offset_std_sampler_interval;
	(*t)->offset_std_sampler_algorithm	= offset_std_sampler_algorithm;
	
} 