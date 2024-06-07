static void remove_translation_table(FlowSource_t *fs, exporter_ipfix_domain_t *exporter, uint16_t id) {
input_translation_t *table, *parent;

	syslog(LOG_INFO, "STR", 
			exporter->info.id, id);

	parent = NULL;
	table = exporter->input_translation_table;
	while ( table && ( table->id != id ) ) {
		parent = table;
		table = table->next;
	}

	if ( table == NULL ) {
		syslog(LOG_ERR, "STR", 
				exporter->info.id, id);
		return;
	}

	dbg_printf("STR", exporter->info.id, table->id);

	
	if (exporter->current_table == table)
		exporter->current_table = NULL;

	if ( parent ) {
		
		parent->next = table->next;
	} else {
		
		exporter->input_translation_table = NULL;
	}

	RemoveExtensionMap(fs, table->extension_info.map);
	free(table->sequence);
	free(table->extension_info.map);
	free(table);

} 