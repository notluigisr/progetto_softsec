RsaAdjustPrimeCandidate(
			bigNum          prime,
			SEED_COMPAT_LEVEL seedCompatLevel  
			)
{
    switch (seedCompatLevel) {
    case SEED_COMPAT_LEVEL_ORIGINAL:
        RsaAdjustPrimeCandidate_PreRev155(prime);
        break;
    
    case SEED_COMPAT_LEVEL_RSA_PRIME_ADJUST_FIX:
        RsaAdjustPrimeCandidate_New(prime);
        break;
    default:
        FAIL(FATAL_ERROR_INTERNAL);
    }
}