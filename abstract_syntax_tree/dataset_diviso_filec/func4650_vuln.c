static __inline__ void ipv6_select_ident(struct frag_hdr *fhdr)
{
	static u32 ipv6_fragmentation_id = 1;
	static DEFINE_SPINLOCK(ip6_id_lock);

	spin_lock_bh(&ip6_id_lock);
	fhdr->identification = htonl(ipv6_fragmentation_id);
	if (++ipv6_fragmentation_id == 0)
		ipv6_fragmentation_id = 1;
	spin_unlock_bh(&ip6_id_lock);
}