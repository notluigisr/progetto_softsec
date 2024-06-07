static int decode_getdevicelist(struct xdr_stream *xdr,
				struct pnfs_devicelist *res)
{
	__be32 *p;
	int status, i;
	struct nfs_writeverf verftemp;

	status = decode_op_hdr(xdr, OP_GETDEVICELIST);
	if (status)
		return status;

	p = xdr_inline_decode(xdr, 8 + 8 + 4);
	if (unlikely(!p))
		goto out_overflow;

	
	p += 2;

	
	p = xdr_decode_opaque_fixed(p, verftemp.verifier, 8);

	res->num_devs = be32_to_cpup(p);

	dprintk("STR", __func__, res->num_devs);

	if (res->num_devs > NFS4_PNFS_GETDEVLIST_MAXNUM) {
		printk(KERN_ERR "STR",
				__func__, res->num_devs);
		return -EIO;
	}

	p = xdr_inline_decode(xdr,
			      res->num_devs * NFS4_DEVICEID4_SIZE + 4);
	if (unlikely(!p))
		goto out_overflow;
	for (i = 0; i < res->num_devs; i++)
		p = xdr_decode_opaque_fixed(p, res->dev_id[i].data,
					    NFS4_DEVICEID4_SIZE);
	res->eof = be32_to_cpup(p);
	return 0;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}