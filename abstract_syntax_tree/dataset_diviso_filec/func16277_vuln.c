static inline void PushSequence(input_translation_t *table, uint16_t Type, uint32_t *offset, void *stack, int pair_offset) {
uint32_t i = table->number_of_sequences;
uint32_t index = cache.lookup_info[Type].index;

	if ( table->number_of_sequences >= cache.max_v9_elements ) {
		syslog(LOG_ERR, "STR", 
			__FILE__, __LINE__);
		dbg_printf("STR", 
			__FILE__, __LINE__);
		return;
	}

	if ( cache.lookup_info[Type].found ) {
			table->sequence[i].id = v9_element_map[index].sequence;
			table->sequence[i].input_offset  = cache.lookup_info[Type].offset;
			table->sequence[i].output_offset = *offset;
			table->sequence[i].stack = stack;
			dbg_printf("STR");
	} else {
			
			
			index += pair_offset;
			table->sequence[i].id = v9_element_map[index].zero_sequence;
			table->sequence[i].input_offset  = 0;
			table->sequence[i].output_offset = *offset;
			table->sequence[i].stack = NULL;
			dbg_printf("STR");
	}
	dbg_printf("STR",
		i, Type, v9_element_map[index].length, v9_element_map[index].out_length, table->sequence[i].id, 
		table->sequence[i].input_offset, table->sequence[i].output_offset);
	table->number_of_sequences++;
	(*offset) += v9_element_map[index].out_length;

} 