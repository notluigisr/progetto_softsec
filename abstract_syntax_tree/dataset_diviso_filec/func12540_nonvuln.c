static void mon_update_local_domain(struct tipc_monitor *mon)
{
	struct tipc_peer *self = mon->self;
	struct tipc_mon_domain *cache = &mon->cache;
	struct tipc_mon_domain *dom = self->domain;
	struct tipc_peer *peer = self;
	u64 prev_up_map = dom->up_map;
	u16 member_cnt, i;
	bool diff;

	
	member_cnt = dom_size(mon->peer_cnt) - 1;
	self->applied = member_cnt;

	
	dom->len = dom_rec_len(dom, member_cnt);
	diff = dom->member_cnt != member_cnt;
	dom->member_cnt = member_cnt;
	for (i = 0; i < member_cnt; i++) {
		peer = peer_nxt(peer);
		diff |= dom->members[i] != peer->addr;
		dom->members[i] = peer->addr;
		map_set(&dom->up_map, i, peer->is_up);
		cache->members[i] = mon_cpu_to_le32(peer->addr);
	}
	diff |= dom->up_map != prev_up_map;
	if (!diff)
		return;
	dom->gen = ++mon->dom_gen;
	cache->len = mon_cpu_to_le16(dom->len);
	cache->gen = mon_cpu_to_le16(dom->gen);
	cache->member_cnt = mon_cpu_to_le16(member_cnt);
	cache->up_map = mon_cpu_to_le64(dom->up_map);
	mon_apply_domain(mon, self);
}