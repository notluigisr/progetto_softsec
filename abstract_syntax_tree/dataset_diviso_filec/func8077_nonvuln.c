int wc_MakeNtruCert(Cert* cert, byte* derBuffer, word32 derSz,
                  const byte* ntruKey, word16 keySz, WC_RNG* rng)
{
    return MakeAnyCert(cert, derBuffer, derSz, NULL, NULL, rng, NULL,
            ntruKey, keySz, NULL, NULL);
}