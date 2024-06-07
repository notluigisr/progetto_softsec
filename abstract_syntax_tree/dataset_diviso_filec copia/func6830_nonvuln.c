static struct tipc_peer *peer_head(struct tipc_peer *peer)
{
	while (!peer->is_head)
		peer = peer_prev(peer);
	return peer;
}