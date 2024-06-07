recv_and_process_client_pkt(void )
{
	ssize_t          size;
	
	len_and_sockaddr *to;
	struct sockaddr  *from;
	msg_t            msg;
	uint8_t          query_status;
	l_fixedpt_t      query_xmttime;

	to = get_sock_lsa(G_listen_fd);
	from = xzalloc(to->len);

	size = recv_from_to(G_listen_fd, &msg, sizeof(msg), MSG_DONTWAIT, from, &to->u.sa, to->len);
	if (size != NTP_MSGSIZE_NOAUTH && size != NTP_MSGSIZE) {
		char *addr;
		if (size < 0) {
			if (errno == EAGAIN)
				goto bail;
			bb_perror_msg_and_die("STR");
		}
		addr = xmalloc_sockaddr2dotted_noport(from);
		bb_error_msg("STR", addr, (int)size);
		free(addr);
		goto bail;
	}

	query_status = msg.m_status;
	query_xmttime = msg.m_xmttime;

	
	memset(&msg, 0, sizeof(msg));
	msg.m_status = G.stratum < MAXSTRAT ? (G.ntp_status & LI_MASK) : LI_ALARM;
	msg.m_status |= (query_status & VERSION_MASK);
	msg.m_status |= ((query_status & MODE_MASK) == MODE_CLIENT) ?
			MODE_SERVER : MODE_SYM_PAS;
	msg.m_stratum = G.stratum;
	msg.m_ppoll = G.poll_exp;
	msg.m_precision_exp = G_precision_exp;
	
	msg.m_rectime = d_to_lfp(G.cur_time);
	msg.m_xmttime = d_to_lfp(gettime1900d()); 
	if (G.peer_cnt == 0) {
		
		G.reftime = G.cur_time;
	}
	msg.m_reftime = d_to_lfp(G.reftime);
	msg.m_orgtime = query_xmttime;
	msg.m_rootdelay = d_to_sfp(G.rootdelay);

	msg.m_rootdisp = d_to_sfp(G.rootdisp);
	
	msg.m_refid = G.refid; 

	
	do_sendto(G_listen_fd,
		 &to->u.sa,  from,  to->len,
		&msg, size);

 bail:
	free(to);
	free(from);
}