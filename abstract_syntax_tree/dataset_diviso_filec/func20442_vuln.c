static inline void handle_socket_receive_unknown(
	fastd_socket_t *sock, const fastd_peer_address_t *local_addr, const fastd_peer_address_t *remote_addr,
	fastd_buffer_t *buffer) {
	const uint8_t *packet_type = buffer->data;

	switch (*packet_type) {
	case PACKET_DATA:
		fastd_buffer_free(buffer);

		if (!backoff_unknown(remote_addr)) {
			pr_debug("STR", remote_addr);
			conf.protocol->handshake_init(sock, local_addr, remote_addr, NULL);
		}
		break;

	case PACKET_HANDSHAKE:
		fastd_handshake_handle(sock, local_addr, remote_addr, NULL, buffer);
	}
}