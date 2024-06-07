static int DecodeBasicCaConstraint(const byte* input, int sz, DecodedCert* cert)
{
    word32 idx = 0;
    int length = 0;
    int ret;

    WOLFSSL_ENTER("STR");

    if (GetSequence(input, &idx, &length, sz) < 0) {
        WOLFSSL_MSG("STR");
        return ASN_PARSE_E;
    }

    if (length == 0)
        return 0;

    

    ret = GetBoolean(input, &idx, sz);

#ifndef WOLFSSL_X509_BASICCONS_INT
    if (ret < 0) {
        WOLFSSL_MSG("STR");
        return ret;
    }

    cert->isCA = (byte)ret;
#else
    if (ret < 0) {
        if(input[idx] == ASN_INTEGER) {
            
            cert->isCA = FALSE;
        } else return ret;
    } else
        cert->isCA = (byte)ret;
#endif

    
    if (idx >= (word32)sz) {
        return 0;
    }

    ret = GetInteger7Bit(input, &idx, sz);
    if (ret < 0)
        return ret;
    cert->pathLength = (byte)ret;
    cert->pathLengthSet = 1;

    return 0;
}