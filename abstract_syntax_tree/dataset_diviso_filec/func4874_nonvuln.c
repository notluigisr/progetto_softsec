static int nfs4_xdr_dec_close(struct rpc_rqst *rqstp, struct xdr_stream *xdr,
			      struct nfs_closeres *res)
{
	struct compound_hdr hdr;
	int status;

	status = decode_compound_hdr(xdr, &hdr);
	if (status)
		goto out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	if (status)
		goto out;
	status = decode_putfh(xdr);
	if (status)
		goto out;
	status = decode_close(xdr, res);
	if (status != 0)
		goto out;
	
	decode_getfattr(xdr, res->fattr, res->server,
			!RPC_IS_ASYNC(rqstp->rq_task));
out:
	return status;
}