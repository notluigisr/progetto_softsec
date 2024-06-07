static int drbg_kcapi_hash(struct drbg_state *drbg, const unsigned char *key,
			   unsigned char *outval, const struct list_head *in)
{
	struct sdesc *sdesc = (struct sdesc *)drbg->priv_data;
	struct drbg_string *input = NULL;

	if (key)
		crypto_shash_setkey(sdesc->shash.tfm, key, drbg_statelen(drbg));
	crypto_shash_init(&sdesc->shash);
	list_for_each_entry(input, in, list)
		crypto_shash_update(&sdesc->shash, input->buf, input->len);
	return crypto_shash_final(&sdesc->shash, outval);
}