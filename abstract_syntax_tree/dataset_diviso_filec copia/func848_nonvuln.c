static void *aead_bind(const char *name, u32 type, u32 mask)
{
	struct aead_tfm *tfm;
	struct crypto_aead *aead;
	struct crypto_skcipher *null_tfm;

	tfm = kzalloc(sizeof(*tfm), GFP_KERNEL);
	if (!tfm)
		return ERR_PTR(-ENOMEM);

	aead = crypto_alloc_aead(name, type, mask);
	if (IS_ERR(aead)) {
		kfree(tfm);
		return ERR_CAST(aead);
	}

	null_tfm = crypto_get_default_null_skcipher2();
	if (IS_ERR(null_tfm)) {
		crypto_free_aead(aead);
		kfree(tfm);
		return ERR_CAST(null_tfm);
	}

	tfm->aead = aead;
	tfm->null_tfm = null_tfm;

	return tfm;
}