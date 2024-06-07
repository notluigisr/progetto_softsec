pubkey_get_npkey (pubkey_algo_t algo)
{
  switch (algo)
    {
    case PUBKEY_ALGO_RSA:
    case PUBKEY_ALGO_RSA_E:
    case PUBKEY_ALGO_RSA_S:     return 2;
    case PUBKEY_ALGO_ELGAMAL_E: return 3;
    case PUBKEY_ALGO_DSA:       return 4;
    case PUBKEY_ALGO_ECDH:      return 3;
    case PUBKEY_ALGO_ECDSA:     return 2;
    case PUBKEY_ALGO_ELGAMAL:   return 3;
    case PUBKEY_ALGO_EDDSA:     return 2;
    }
  return 0;
}