static inline int sctp_cacc_skip_3_1_f(struct sctp_transport *transport,
				       int count_of_newacks)
{
	if (count_of_newacks < 2 &&
			(transport && !transport->cacc.cacc_saw_newack))
		return 1;
	return 0;
}