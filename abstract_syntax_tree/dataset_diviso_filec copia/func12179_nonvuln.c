bool tipc_link_is_reset(struct tipc_link *l)
{
	return l->state & (LINK_RESET | LINK_FAILINGOVER | LINK_ESTABLISHING);
}