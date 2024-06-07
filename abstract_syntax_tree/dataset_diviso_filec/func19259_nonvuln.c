static inline int __sctp_state(const struct sctp_association *asoc,
			       sctp_state_t state)
{
	return asoc->state == state;
}