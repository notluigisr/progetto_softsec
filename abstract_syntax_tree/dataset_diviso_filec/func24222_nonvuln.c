nfsd4_encode_read(struct nfsd4_compoundres *resp, __be32 nfserr,
		  struct nfsd4_read *read)
{
	unsigned long maxcount;
	struct xdr_stream *xdr = &resp->xdr;
	struct file *file = read->rd_filp;
	int starting_len = xdr->buf->len;
	struct raparms *ra = NULL;
	__be32 *p;

	if (nfserr)
		goto out;

	p = xdr_reserve_space(xdr, 8); 
	if (!p) {
		WARN_ON_ONCE(test_bit(RQ_SPLICE_OK, &resp->rqstp->rq_flags));
		nfserr = nfserr_resource;
		goto out;
	}
	if (resp->xdr.buf->page_len &&
	    test_bit(RQ_SPLICE_OK, &resp->rqstp->rq_flags)) {
		WARN_ON_ONCE(1);
		nfserr = nfserr_resource;
		goto out;
	}
	xdr_commit_encode(xdr);

	maxcount = svc_max_payload(resp->rqstp);
	maxcount = min_t(unsigned long, maxcount,
			 (xdr->buf->buflen - xdr->buf->len));
	maxcount = min_t(unsigned long, maxcount, read->rd_length);

	if (read->rd_tmp_file)
		ra = nfsd_init_raparms(file);

	if (file->f_op->splice_read &&
	    test_bit(RQ_SPLICE_OK, &resp->rqstp->rq_flags))
		nfserr = nfsd4_encode_splice_read(resp, read, file, maxcount);
	else
		nfserr = nfsd4_encode_readv(resp, read, file, maxcount);

	if (ra)
		nfsd_put_raparams(file, ra);

	if (nfserr)
		xdr_truncate_encode(xdr, starting_len);

out:
	if (file)
		fput(file);
	return nfserr;
}