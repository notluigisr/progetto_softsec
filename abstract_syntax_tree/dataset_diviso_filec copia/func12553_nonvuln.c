CryptGetSymmetricBlockSize(
			   TPM_ALG_ID      symmetricAlg,   
			   UINT16          keySizeInBits   
			   )
{
    const INT16    *sizes;
    INT16            i;

    switch(symmetricAlg)
	{
#if ALG_AES
	    ALG_CASE(AES, aes);
#endif
#if ALG_SM4
	    ALG_CASE(SM4, sm4);
#endif
#if ALG_CAMELLIA
	    ALG_CASE(CAMELLIA, camellia);
#endif
#if ALG_TDES
	    ALG_CASE(TDES, tdes);
#endif
	  default:
	    return 0;
	}
    
    for(i = 0; *sizes >= 0; i++, sizes++)
	{
	    if(*sizes == keySizeInBits)
		break;
	}
    
    
    if(*sizes++ < 0)
	return 0;
    
    while(*sizes++ >= 0);
    
    
    return sizes[i];
}