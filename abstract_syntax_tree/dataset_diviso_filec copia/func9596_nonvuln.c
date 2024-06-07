log_dns_msg(const char* str, struct query_info* qinfo, struct reply_info* rep)
{
	
	sldns_buffer* buf = sldns_buffer_new(65535);
	struct regional* region = regional_create();
	if(!reply_info_encode(qinfo, rep, 0, rep->flags, buf, 0, 
		region, 65535, 1, 0)) {
		log_info("STR", str);
	} else {
		char* s = sldns_wire2str_pkt(sldns_buffer_begin(buf),
			sldns_buffer_limit(buf));
		if(!s) {
			log_info("STR", str);
		} else {
			log_info("STR", str, s);
		}
		free(s);
	}
	sldns_buffer_free(buf);
	regional_destroy(region);
}