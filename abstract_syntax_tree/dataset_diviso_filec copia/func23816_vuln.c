static void remove_all_translation_tables(exporter_ipfix_domain_t *exporter) {
input_translation_t *table, *next;

	syslog(LOG_INFO, "STR", 
		exporter->info.id);

	table = exporter->input_translation_table;
	while ( table ) {
		next = table->next;

		dbg_printf("STR", exporter->info.id, table->id);

		free(table->sequence);
		free(table->extension_info.map);
		free(table);

		table = next;
	}

	
	exporter->input_translation_table = NULL;
	exporter->current_table = NULL;

} 