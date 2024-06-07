static inline int sctp_vtag_hashfn(__u16 lport, __u16 rport, __u32 vtag)
{
	int h = (lport << 16) + rport;
	h ^= vtag;
	return h & (sctp_assoc_hashsize - 1);
}