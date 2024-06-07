nfsd4_encode_getdeviceinfo(struct nfsd4_compoundres *resp, __be32 nfserr,
		struct nfsd4_getdeviceinfo *gdev)
{
	struct xdr_stream *xdr = &resp->xdr;
	const struct nfsd4_layout_ops *ops =
		nfsd4_layout_ops[gdev->gd_layout_type];
	u32 starting_len = xdr->buf->len, needed_len;
	__be32 *p;

	dprintk("STR", __func__, be32_to_cpu(nfserr));
	if (nfserr)
		goto out;

	nfserr = nfserr_resource;
	p = xdr_reserve_space(xdr, 4);
	if (!p)
		goto out;

	*p++ = cpu_to_be32(gdev->gd_layout_type);

	
	if (gdev->gd_maxcount != 0) {
		nfserr = ops->encode_getdeviceinfo(xdr, gdev);
		if (nfserr) {
			
			if (xdr->buf->len + 4 > gdev->gd_maxcount)
				goto toosmall;
			goto out;
		}
	}

	nfserr = nfserr_resource;
	if (gdev->gd_notify_types) {
		p = xdr_reserve_space(xdr, 4 + 4);
		if (!p)
			goto out;
		*p++ = cpu_to_be32(1);			
		*p++ = cpu_to_be32(gdev->gd_notify_types);
	} else {
		p = xdr_reserve_space(xdr, 4);
		if (!p)
			goto out;
		*p++ = 0;
	}

	nfserr = 0;
out:
	kfree(gdev->gd_device);
	dprintk("STR", __func__, be32_to_cpu(nfserr));
	return nfserr;

toosmall:
	dprintk("STR", __func__);
	needed_len = xdr->buf->len + 4 ;
	xdr_truncate_encode(xdr, starting_len);
	p = xdr_reserve_space(xdr, 4);
	if (!p) {
		nfserr = nfserr_resource;
	} else {
		*p++ = cpu_to_be32(needed_len);
		nfserr = nfserr_toosmall;
	}
	goto out;
}