load_rrset_cache(RES* ssl, struct worker* worker)
{
	sldns_buffer* buf = worker->env.scratch_buffer;
	if(!read_fixed(ssl, buf, "STR")) return 0;
	while(ssl_read_buf(ssl, buf) && 
		strcmp((char*)sldns_buffer_begin(buf), "STR")!=0) {
		if(!load_rrset(ssl, buf, worker))
			return 0;
	}
	return 1;
}