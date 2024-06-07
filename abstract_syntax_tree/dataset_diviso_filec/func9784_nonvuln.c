static int DecodePolicyConstraints(const byte* input, int sz, DecodedCert* cert)
{
    word32 idx = 0;
    int length = 0;
    int skipLength = 0;
    int ret;
    byte tag;

    WOLFSSL_ENTER("STR");

    if (GetSequence(input, &idx, &length, sz) < 0) {
        WOLFSSL_MSG("STR");
        return ASN_PARSE_E;
    }

    if (length == 0)
        return ASN_PARSE_E;

    if (GetASNTag(input, &idx, &tag, sz) < 0) {
        WOLFSSL_MSG("STR");
        return ASN_PARSE_E;
    }

    if (tag == (ASN_CONTEXT_SPECIFIC | 0)) {
        
        cert->extPolicyConstRxpSet = 1;
    }
    else if (tag == (ASN_CONTEXT_SPECIFIC | 1)) {
        
        cert->extPolicyConstIpmSet = 1;
    }
    else {
        WOLFSSL_MSG("STR");
        return ASN_PARSE_E;
    }

    ret = GetLength(input, &idx, &skipLength, sz);
    if (ret < 0) {
        WOLFSSL_MSG("STR");
        return ret;
    }
    if (skipLength > 1) {
        WOLFSSL_MSG("STR");
        return BUFFER_E;
    }
    cert->policyConstSkip = input[idx];

    return 0;
}