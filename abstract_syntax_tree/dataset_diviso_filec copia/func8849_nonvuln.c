untrust_key(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	do_trustkey(srcadr, inter, inpkt, 0);
}