sctp_disposition_t sctp_sf_discard_chunk(struct net *net,
					 const struct sctp_endpoint *ep,
					 const struct sctp_association *asoc,
					 const sctp_subtype_t type,
					 void *arg,
					 sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk = arg;

	
	if (!sctp_chunk_length_valid(chunk, sizeof(sctp_chunkhdr_t)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	pr_debug("STR", __func__, type.chunk);

	return SCTP_DISPOSITION_DISCARD;
}