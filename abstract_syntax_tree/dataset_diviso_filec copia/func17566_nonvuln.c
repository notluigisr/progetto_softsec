static int UTF8ToISO8859_2 (unsigned char* out, int *outlen,
    const unsigned char* in, int *inlen) {
    return UTF8ToISO8859x (out, outlen, in, inlen, xmltranscodetable_ISO8859_2);
}