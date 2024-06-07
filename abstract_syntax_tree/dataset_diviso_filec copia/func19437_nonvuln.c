bighash(
	BIGNUM	*bn,		
	BIGNUM	*bk		
	)
{
	EVP_MD_CTX ctx;		
	u_char dgst[EVP_MAX_MD_SIZE]; 
	u_char	*ptr;		
	u_int	len;

	len = BN_num_bytes(bn);
	ptr = emalloc(len);
	BN_bn2bin(bn, ptr);
	EVP_DigestInit(&ctx, EVP_md5());
	EVP_DigestUpdate(&ctx, ptr, len);
	EVP_DigestFinal(&ctx, dgst, &len);
	BN_bin2bn(dgst, len, bk);
	free(ptr);
}