static input_translation_t *add_translation_table(exporter_ipfix_domain_t *exporter, uint16_t id) {
input_translation_t **table;

	table = &(exporter->input_translation_table);
	while ( *table ) {
		table = &((*table)->next);
	}

	
	
	*table = calloc(1, sizeof(input_translation_t));
	if ( !(*table) ) {
			syslog(LOG_ERR, "STR", __FILE__, __LINE__, strerror (errno));
			return NULL;
	}
	(*table)->sequence = calloc(cache.max_ipfix_elements, sizeof(sequence_map_t));
	if ( !(*table)->sequence ) {
			syslog(LOG_ERR, "STR", __FILE__, __LINE__, strerror (errno));
			return NULL;
	}

	(*table)->id   = id;
	(*table)->next = NULL;

	dbg_printf("STR", exporter->info.id, id);

	return *table;

} 