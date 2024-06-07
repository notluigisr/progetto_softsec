int wc_DsaKeyToParamsDer(DsaKey* key, byte* output, word32 inLen)
{
    if (!key || !output)
        return BAD_FUNC_ARG;

    return DsaKeyIntsToDer(key, output, inLen, DSA_PARAM_INTS, 0);
}