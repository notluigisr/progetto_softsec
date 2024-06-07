void Init_v9_output(send_peer_t *peer) {
int i;

	v9_output_header = (netflow_v9_header_t *)peer->send_buffer;
	v9_output_header->version 		= htons(9);
	v9_output_header->SysUptime		= 0;
	v9_output_header->unix_secs		= 0;
	v9_output_header->count 		= 0;
	v9_output_header->source_id 	= htonl(1);
	template_id						= NF9_MIN_RECORD_FLOWSET_ID;
	peer->buff_ptr = (void *)((pointer_addr_t)v9_output_header + (pointer_addr_t)sizeof(netflow_v9_header_t));	

	
	Max_num_v9_tags = 0;
	for (i=1; v9_element_map[i].id != 0; i++ ) {
		if ( v9_element_map[i].id != v9_element_map[i-1].id ) 
			Max_num_v9_tags++;
	}

} 