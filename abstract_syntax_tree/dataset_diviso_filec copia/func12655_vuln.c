int mesg_make_query (u_char *qname, uint16_t qtype, uint16_t qclass,
		     uint32_t id, int rd, u_char *buf, int buflen) {
	char *fn = "STR";
	u_char *ucp;
	int i, written_len;
	Mesg_Hdr *hdr;

	if (T.debug > 4)
		syslog (LOG_DEBUG, "STR", fn,
			string_rtype (qtype), id);

	hdr = (Mesg_Hdr *) buf;

	
	hdr->id = id;
	hdr->opcode = OP_QUERY;
	hdr->rcode = RC_OK;
	hdr->rd = rd;
	hdr->qr = hdr->aa = hdr->tc = hdr->ra = hdr->zero = 0;
	hdr->qdcnt = ntohs (1);
	hdr->ancnt = hdr->nscnt = hdr->arcnt = ntohs (0);

	written_len = sizeof (Mesg_Hdr);
	ucp = (u_char *) (hdr + 1);

	
	if (T.debug > 4)
		syslog (LOG_DEBUG, "STR", fn, ucp - buf);

	i = dname_copy (qname, ucp, buflen - written_len);
	if (i < 0)
		return -1;

	written_len += i;
	ucp += i;

	
	if (T.debug > 4)
		syslog (LOG_DEBUG, "STR",
			fn, ucp - buf);

	written_len += sizeof (uint16_t) * 2;
	if (written_len > buflen)
		return -1;

	PUTSHORT (qtype, ucp);
	PUTSHORT (qclass, ucp);

	return written_len;
}