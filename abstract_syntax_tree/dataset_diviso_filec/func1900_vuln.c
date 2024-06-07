u32 ip_idents_reserve(u32 hash, int segs)
{
	u32 *p_tstamp = ip_tstamps + hash % IP_IDENTS_SZ;
	atomic_t *p_id = ip_idents + hash % IP_IDENTS_SZ;
	u32 old = READ_ONCE(*p_tstamp);
	u32 now = (u32)jiffies;
	u32 delta = 0;

	if (old != now && cmpxchg(p_tstamp, old, now) == old)
		delta = prandom_u32_max(now - old);

	
	return atomic_add_return(segs + delta, p_id) - segs;
}