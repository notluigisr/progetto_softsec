list_restrict(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	struct info_restrict *ir;

	DPRINTF(3, ("STR"));

	ir = (struct info_restrict *)prepare_pkt(srcadr, inter, inpkt,
	    v6sizeof(struct info_restrict));
	
	
	list_restrict4(restrictlist4, &ir);
	if (client_v6_capable)
		list_restrict6(restrictlist6, &ir);
	flush_pkt();
}