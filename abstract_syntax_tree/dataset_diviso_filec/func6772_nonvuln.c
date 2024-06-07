SECURITY_STATUS nla_encrypt_public_key_hash(rdpNla* nla)
{
	SECURITY_STATUS status = SEC_E_INTERNAL_ERROR;
	WINPR_DIGEST_CTX* sha256 = NULL;
	BYTE* hash;

	WINPR_ASSERT(nla);

	const ULONG auth_data_length =
	    (nla->ContextSizes.cbSecurityTrailer + WINPR_SHA256_DIGEST_LENGTH);
	const BYTE* hashMagic = nla->server ? ServerClientHashMagic : ClientServerHashMagic;
	const size_t hashSize =
	    nla->server ? sizeof(ServerClientHashMagic) : sizeof(ClientServerHashMagic);

	if (!nla_sec_buffer_alloc(&nla->pubKeyAuth, auth_data_length))
	{
		status = SEC_E_INSUFFICIENT_MEMORY;
		goto out;
	}

	
	if (!(sha256 = winpr_Digest_New()))
		goto out;

	if (!winpr_Digest_Init(sha256, WINPR_MD_SHA256))
		goto out;

	
	if (!winpr_Digest_Update(sha256, hashMagic, hashSize))
		goto out;

	if (!nla_Digest_Update_From_SecBuffer(sha256, &nla->ClientNonce))
		goto out;

	
	if (!nla_Digest_Update_From_SecBuffer(sha256, &nla->PublicKey))
		goto out;

	hash = &((BYTE*)nla->pubKeyAuth.pvBuffer)[nla->ContextSizes.cbSecurityTrailer];
	if (!winpr_Digest_Final(sha256, hash, WINPR_SHA256_DIGEST_LENGTH))
		goto out;

	status = nla_encrypt(nla, &nla->pubKeyAuth, nla->ContextSizes.cbSecurityTrailer);
	if (status != SEC_E_OK)
		goto out;

out:
	winpr_Digest_Free(sha256);
	return status;
}