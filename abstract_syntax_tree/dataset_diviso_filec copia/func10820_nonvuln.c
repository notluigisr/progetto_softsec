static void sctp_transport_destroy(struct sctp_transport *transport)
{
	SCTP_ASSERT(transport->dead, "STR", return);

	if (transport->asoc)
		sctp_association_put(transport->asoc);

	sctp_packet_free(&transport->packet);

	dst_release(transport->dst);
	kfree(transport);
	SCTP_DBG_OBJCNT_DEC(transport);
}