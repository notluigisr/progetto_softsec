int UnTraditionalEnc(byte* key, word32 keySz, byte* out, word32* outSz,
        const char* password, int passwordSz, int vPKCS, int vAlgo,
        byte* salt, word32 saltSz, int itt, WC_RNG* rng, void* heap)
{
    return TraditionalEnc(key, keySz, out, outSz, password, passwordSz,
                vPKCS, vAlgo, 0, salt, saltSz, itt, rng, heap);
}