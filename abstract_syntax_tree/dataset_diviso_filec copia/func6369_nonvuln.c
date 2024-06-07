static void receive_packet(node_t *n, vpn_packet_t *packet) {
	ifdebug(TRAFFIC) logger(LOG_DEBUG, "STR",
			   packet->len, n->name, n->hostname);

	route(n, packet);
}