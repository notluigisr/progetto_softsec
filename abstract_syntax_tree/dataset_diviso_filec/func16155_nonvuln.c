skip_ttl_rdata(sldns_buffer* pkt) 
{
	uint16_t rdatalen;
	if(sldns_buffer_remaining(pkt) < 6) 
		return 0;
	sldns_buffer_skip(pkt, 4); 
	rdatalen = sldns_buffer_read_u16(pkt);
	if(sldns_buffer_remaining(pkt) < rdatalen)
		return 0;
	sldns_buffer_skip(pkt, (ssize_t)rdatalen);
	return 1;
}