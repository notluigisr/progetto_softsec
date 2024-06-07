static struct aead_request *macsec_alloc_req(struct crypto_aead *tfm,
					     unsigned char **iv,
					     struct scatterlist **sg)
{
	size_t size, iv_offset, sg_offset;
	struct aead_request *req;
	void *tmp;

	size = sizeof(struct aead_request) + crypto_aead_reqsize(tfm);
	iv_offset = size;
	size += GCM_AES_IV_LEN;

	size = ALIGN(size, __alignof__(struct scatterlist));
	sg_offset = size;
	size += sizeof(struct scatterlist) * (MAX_SKB_FRAGS + 1);

	tmp = kmalloc(size, GFP_ATOMIC);
	if (!tmp)
		return NULL;

	*iv = (unsigned char *)(tmp + iv_offset);
	*sg = (struct scatterlist *)(tmp + sg_offset);
	req = tmp;

	aead_request_set_tfm(req, tfm);

	return req;
}