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
	    
	    
	    
	    
	
	    if (1) {
		DRBG_Generate(rand, (BYTE *)prime->d, (UINT16)BITS_TO_BYTES(bits));
		if (g_inFailureMode)
		    return TPM_RC_FAILURE;
	    } else {
		if(!BnGetRandomBits(prime, bits, rand))                              
		    return TPM_RC_FAILURE;
	    }
	    RsaAdjustPrimeCandidate(prime);
	
	    found = RsaCheckPrime(prime, exponent, rand) == TPM_RC_SUCCESS;
	}
    return TPM_RC_SUCCESS;
}