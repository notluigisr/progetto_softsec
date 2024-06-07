static inline void *crypto_ahash_ctx(struct crypto_ahash *tfm)
{
	return crypto_tfm_ctx(crypto_ahash_tfm(tfm));
}