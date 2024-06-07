set_clock_fudge(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	register struct conf_fudge *cf;
	register int items;
	struct refclockstat clock_stat;
	sockaddr_u addr;
	l_fp ltmp;

	ZERO(addr);
	ZERO(clock_stat);
	items = INFO_NITEMS(inpkt->err_nitems);
	cf = (struct conf_fudge *)&inpkt->u;

	while (items-- > 0) {
		AF(&addr) = AF_INET;
		NSRCADR(&addr) = cf->clockadr;
#ifdef ISC_PLATFORM_HAVESALEN
		addr.sa.sa_len = SOCKLEN(&addr);
#endif
		SET_PORT(&addr, NTP_PORT);
		if (!ISREFCLOCKADR(&addr) || NULL ==
		    findexistingpeer(&addr, NULL, NULL, -1, 0)) {
			req_ack(srcadr, inter, inpkt, INFO_ERR_NODATA);
			return;
		}

		switch(ntohl(cf->which)) {
		    case FUDGE_TIME1:
			NTOHL_FP(&cf->fudgetime, &ltmp);
			LFPTOD(&ltmp, clock_stat.fudgetime1);
			clock_stat.haveflags = CLK_HAVETIME1;
			break;
		    case FUDGE_TIME2:
			NTOHL_FP(&cf->fudgetime, &ltmp);
			LFPTOD(&ltmp, clock_stat.fudgetime2);
			clock_stat.haveflags = CLK_HAVETIME2;
			break;
		    case FUDGE_VAL1:
			clock_stat.fudgeval1 = ntohl(cf->fudgeval_flags);
			clock_stat.haveflags = CLK_HAVEVAL1;
			break;
		    case FUDGE_VAL2:
			clock_stat.fudgeval2 = ntohl(cf->fudgeval_flags);
			clock_stat.haveflags = CLK_HAVEVAL2;
			break;
		    case FUDGE_FLAGS:
			clock_stat.flags = (u_char) (ntohl(cf->fudgeval_flags) & 0xf);
			clock_stat.haveflags =
				(CLK_HAVEFLAG1|CLK_HAVEFLAG2|CLK_HAVEFLAG3|CLK_HAVEFLAG4);
			break;
		    default:
			msyslog(LOG_ERR, "STR");
			req_ack(srcadr, inter, inpkt, INFO_ERR_FMT);
			return;
		}

		refclock_control(&addr, &clock_stat, (struct refclockstat *)0);
	}

	req_ack(srcadr, inter, inpkt, INFO_OKAY);
}