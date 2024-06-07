mon_getlist(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	req_ack(srcadr, inter, inpkt, INFO_ERR_NODATA);
}