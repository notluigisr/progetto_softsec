static inline void 	Process_v9_option_data(exporter_v9_domain_t *exporter, void *data_flowset, FlowSource_t *fs) {
option_offset_t *offset_table;
uint32_t	id;
uint8_t		*in;

	id 	= GET_FLOWSET_ID(data_flowset);

	offset_table = fs->option_offset_table;
	while ( offset_table && offset_table->id != id )
		offset_table = offset_table->next;

	if ( !offset_table ) {
		
		syslog(LOG_ERR, "STR", __FILE__, __LINE__);
		return;
	}

#ifdef DEVEL
	uint32_t size_left = GET_FLOWSET_LENGTH(data_flowset) - 4; 
	dbg_printf("STR", exporter->info.id, size_left);
#endif

	
	in	  = (uint8_t *)(data_flowset + 4);	

	if ( TestFlag(offset_table->flags, HAS_SAMPLER_DATA) ) {
		int32_t  id;
		uint16_t mode;
		uint32_t interval;
		if (offset_table->sampler_id_length == 2) {
			id = Get_val16((void *)&in[offset_table->offset_id]);
		} else {
			id = in[offset_table->offset_id];
		}
		mode 	 = in[offset_table->offset_mode];
		interval = Get_val32((void *)&in[offset_table->offset_interval]); 
	
		dbg_printf("STR");
		dbg_printf("STR", id);
		dbg_printf("STR", mode);
		dbg_printf("STR", interval);
	
		InsertSampler(fs, exporter, id, mode, interval);
	}

	if ( TestFlag(offset_table->flags, HAS_STD_SAMPLER_DATA) ) {
		int32_t  id 	  = -1;
		uint16_t mode 	  = in[offset_table->offset_std_sampler_algorithm];
		uint32_t interval = Get_val32((void *)&in[offset_table->offset_std_sampler_interval]);

		InsertSampler(fs, exporter, id, mode, interval);

		dbg_printf("STR");
		dbg_printf("STR", id);
		dbg_printf("STR", mode);
		dbg_printf("STR", interval);

		syslog(LOG_INFO, "STR", 
				mode, interval);
		dbg_printf("STR", 
				mode, interval);
	}
	processed_records++;

} 