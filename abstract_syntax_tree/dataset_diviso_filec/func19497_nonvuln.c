do_setclr_trap(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt,
	int set
	)
{
	register struct conf_trap *ct;
	register endpt *linter;
	int res;
	sockaddr_u laddr;

	
	ZERO_SOCK(&laddr);
	AF(&laddr) = AF(srcadr);
	SET_PORT(&laddr, NTP_PORT);

	
	if (INFO_NITEMS(inpkt->err_nitems) > 1) {
		msyslog(LOG_ERR, "STR");
		req_ack(srcadr, inter, inpkt, INFO_ERR_FMT);
		return;
	}
	ct = (struct conf_trap *)&inpkt->u;

	
	if (ct->local_address == 0) {
		linter = any_interface;
	} else {
		if (IS_IPV4(&laddr))
			NSRCADR(&laddr) = ct->local_address;
		else
			SOCK_ADDR6(&laddr) = ct->local_address6;
		linter = findinterface(&laddr);
		if (NULL == linter) {
			req_ack(srcadr, inter, inpkt, INFO_ERR_NODATA);
			return;
		}
	}

	if (IS_IPV4(&laddr))
		NSRCADR(&laddr) = ct->trap_address;
	else
		SOCK_ADDR6(&laddr) = ct->trap_address6;
	if (ct->trap_port)
		NSRCPORT(&laddr) = ct->trap_port;
	else
		SET_PORT(&laddr, TRAPPORT);

	if (set) {
		res = ctlsettrap(&laddr, linter, 0,
				 INFO_VERSION(inpkt->rm_vn_mode));
	} else {
		res = ctlclrtrap(&laddr, linter, 0);
	}

	if (!res) {
		req_ack(srcadr, inter, inpkt, INFO_ERR_NODATA);
	} else {
		req_ack(srcadr, inter, inpkt, INFO_OKAY);
	}
	return;
}