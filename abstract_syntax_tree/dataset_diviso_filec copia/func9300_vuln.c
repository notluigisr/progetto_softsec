static const sctp_sm_table_entry_t *sctp_chunk_event_lookup(sctp_cid_t cid,
							    sctp_state_t state)
{
	if (state > SCTP_STATE_MAX)
		return &bug;

	if (cid <= SCTP_CID_BASE_MAX)
		return &chunk_event_table[cid][state];

	if (sctp_prsctp_enable) {
		if (cid == SCTP_CID_FWD_TSN)
			return &prsctp_chunk_event_table[0][state];
	}

	if (sctp_addip_enable) {
		if (cid == SCTP_CID_ASCONF)
			return &addip_chunk_event_table[0][state];

		if (cid == SCTP_CID_ASCONF_ACK)
			return &addip_chunk_event_table[1][state];
	}

	return &chunk_event_table_unknown[state];
}