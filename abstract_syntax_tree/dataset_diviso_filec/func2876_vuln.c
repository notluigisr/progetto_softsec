BnGeneratePrimeForRSA(
		      bigNum          prime,          
		      
		      UINT32          bits,           
		      UINT32          exponent,       
		      RAND_STATE      *rand           
		      )
{
    BOOL            found = FALSE;
    
    
    pAssert(prime->allocated >= BITS_TO_CRYPT_WORDS(bits));
    
    pAssert((bits % 32) == 0);
    
    prime->size = BITS_TO_CRYPT_WORDS(bits);
    
    while(!found)
	{
	    
	    
	    
	    
	
	    switch (DRBG_GetSeedCompatLevel(rand)) {
	    case SEED_COMPAT_LEVEL_ORIGINAL:
		DRBG_Generate(rand, (BYTE *)prime->d, (UINT16)BITS_TO_BYTES(bits));
		if (g_inFailureMode)
		    return TPM_RC_FAILURE;
		break;
	    
            case SEED_COMPAT_LEVEL_RSA_PRIME_ADJUST_FIX:
		if(!BnGetRandomBits(prime, bits, rand))                              
		    return TPM_RC_FAILURE;
                break;
            default:
                FAIL(FATAL_ERROR_INTERNAL);
	    }
	    RsaAdjustPrimeCandidate(prime, DRBG_GetSeedCompatLevel(rand));
	
	    found = RsaCheckPrime(prime, exponent, rand) == TPM_RC_SUCCESS;
	}
    return TPM_RC_SUCCESS;
}