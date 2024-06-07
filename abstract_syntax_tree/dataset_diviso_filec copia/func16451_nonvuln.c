static int ISO8859_16ToUTF8 (unsigned char* out, int *outlen,
    const unsigned char* in, int *inlen) {
    return ISO8859xToUTF8 (out, outlen, in, inlen, xmlunicodetable_ISO8859_16);
}