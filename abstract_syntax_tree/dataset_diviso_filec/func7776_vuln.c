static inline void handle_socket_receive_known(
	fastd_socket_t *sock, const fastd_peer_address_t *local_addr, const fastd_peer_address_t *remote_addr,
	fastd_peer_t *peer, fastd_buffer_t *buffer) {
	if (!fastd_peer_may_connect(peer)) {
		fastd_buffer_free(buffer);
		return;
	}

	const uint8_t *packet_type = buffer->data;

	switch (*packet_type) {
	case PACKET_DATA:
		if (!fastd_peer_is_established(peer) || !fastd_peer_address_equal(&peer->local_address, local_addr)) {
			fastd_buffer_free(buffer);

			if (!backoff_unknown(remote_addr)) {
				pr_debug("STR", peer, remote_addr);
				conf.protocol->handshake_init(sock, local_addr, remote_addr, NULL);
			}
			return;
		}

		conf.protocol->handle_recv(peer, buffer);
		break;

	case PACKET_HANDSHAKE:
		fastd_handshake_handle(sock, local_addr, remote_addr, peer, buffer);
	}
}