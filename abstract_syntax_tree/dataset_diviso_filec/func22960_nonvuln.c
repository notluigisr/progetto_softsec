static int decode_attr_owner(struct xdr_stream *xdr, uint32_t *bitmap,
		const struct nfs_server *server, uint32_t *uid, int may_sleep)
{
	uint32_t len;
	__be32 *p;
	int ret = 0;

	*uid = -2;
	if (unlikely(bitmap[1] & (FATTR4_WORD1_OWNER - 1U)))
		return -EIO;
	if (likely(bitmap[1] & FATTR4_WORD1_OWNER)) {
		p = xdr_inline_decode(xdr, 4);
		if (unlikely(!p))
			goto out_overflow;
		len = be32_to_cpup(p);
		p = xdr_inline_decode(xdr, len);
		if (unlikely(!p))
			goto out_overflow;
		if (!may_sleep) {
			
		} else if (len < XDR_MAX_NETOBJ) {
			if (nfs_map_name_to_uid(server, (char *)p, len, uid) == 0)
				ret = NFS_ATTR_FATTR_OWNER;
			else
				dprintk("STR",
						__func__);
		} else
			dprintk("STR",
					__func__, len);
		bitmap[1] &= ~FATTR4_WORD1_OWNER;
	}
	dprintk("STR", __func__, (int)*uid);
	return ret;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}