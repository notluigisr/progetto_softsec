static int CheckAlgo(int first, int second, int* id, int* version, int* blockSz)
{
    *id      = ALGO_ID_E;
    *version = PKCS5;   
    if (blockSz) *blockSz = 8; 

    if (first == 1) {
        switch (second) {
#if !defined(NO_SHA)
    #ifndef NO_RC4
        case PBE_SHA1_RC4_128:
            *id = PBE_SHA1_RC4_128;
            *version = PKCS12v1;
            return 0;
    #endif
    #ifndef NO_DES3
        case PBE_SHA1_DES3:
            *id = PBE_SHA1_DES3;
            *version = PKCS12v1;
            if (blockSz) *blockSz = DES_BLOCK_SIZE;
            return 0;
        case PBE_SHA1_DES:
            *id = PBE_SHA1_DES;
            *version = PKCS12v1;
            if (blockSz) *blockSz = DES_BLOCK_SIZE;
            return 0;
    #endif
    #ifdef WC_RC2
        case PBE_SHA1_40RC2_CBC:
            *id = PBE_SHA1_40RC2_CBC;
            *version = PKCS12v1;
            if (blockSz) *blockSz = RC2_BLOCK_SIZE;
            return 0;
    #endif
#endif 
        default:
            return ALGO_ID_E;
        }
    }

    if (first != PKCS5)
        return ASN_INPUT_E;  

    if (second == PBES2) {
        *version = PKCS5v2;
        return 0;
    }

    switch (second) {
#ifndef NO_DES3
    #ifndef NO_MD5
    case 3:                   
        *id = PBE_MD5_DES;
        if (blockSz) *blockSz = DES_BLOCK_SIZE;
        return 0;
    #endif
    #ifndef NO_SHA
    case 10:
        *id = PBE_SHA1_DES;
        if (blockSz) *blockSz = DES_BLOCK_SIZE;
        return 0;
    #endif
#endif 
    default:
        return ALGO_ID_E;

    }
}