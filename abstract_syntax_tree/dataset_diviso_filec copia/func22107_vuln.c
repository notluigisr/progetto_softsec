static int decode_nfs_fh(struct xdr_stream *xdr, struct nfs_fh *fh)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -ENOBUFS;
	fh->size = be32_to_cpup(p++);
	if (fh->size > sizeof(struct nfs_fh)) {
		printk(KERN_ERR "STR",
		       fh->size);
		return -EOVERFLOW;
	}
	
	p = xdr_inline_decode(xdr, fh->size);
	if (unlikely(!p))
		return -ENOBUFS;
	memcpy(&fh->data, p, fh->size);
	dprintk("STR", __func__, fh->size);

	return 0;
}