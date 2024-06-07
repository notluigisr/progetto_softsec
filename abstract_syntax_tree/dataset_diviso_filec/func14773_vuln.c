static int rndis_set_response(struct rndis_params *params,
			      rndis_set_msg_type *buf)
{
	u32 BufLength, BufOffset;
	rndis_set_cmplt_type *resp;
	rndis_resp_t *r;

	r = rndis_add_response(params, sizeof(rndis_set_cmplt_type));
	if (!r)
		return -ENOMEM;
	resp = (rndis_set_cmplt_type *)r->buf;

	BufLength = le32_to_cpu(buf->InformationBufferLength);
	BufOffset = le32_to_cpu(buf->InformationBufferOffset);

#ifdef	VERBOSE_DEBUG
	pr_debug("STR", __func__, BufLength);
	pr_debug("STR", __func__, BufOffset);
	pr_debug("STR", __func__);

	for (i = 0; i < BufLength; i++) {
		pr_debug("STR", *(((u8 *) buf) + i + 8 + BufOffset));
	}

	pr_debug("STR");
#endif

	resp->MessageType = cpu_to_le32(RNDIS_MSG_SET_C);
	resp->MessageLength = cpu_to_le32(16);
	resp->RequestID = buf->RequestID; 
	if (gen_ndis_set_resp(params, le32_to_cpu(buf->OID),
			((u8 *)buf) + 8 + BufOffset, BufLength, r))
		resp->Status = cpu_to_le32(RNDIS_STATUS_NOT_SUPPORTED);
	else
		resp->Status = cpu_to_le32(RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	return 0;
}