TPMU_PUBLIC_ID_Marshal(TPMU_PUBLIC_ID *source, BYTE **buffer, INT32 *size, UINT32 selector)
{
    UINT16 written = 0;

    switch (selector) {
#if ALG_KEYEDHASH
      case TPM_ALG_KEYEDHASH:
	written += TPM2B_DIGEST_Marshal(&source->keyedHash, buffer, size);
	break;
#endif
#if ALG_SYMCIPHER
      case TPM_ALG_SYMCIPHER:
	written += TPM2B_DIGEST_Marshal(&source->sym, buffer, size);
	break;
#endif
#if ALG_RSA
      case TPM_ALG_RSA:
	written += TPM2B_PUBLIC_KEY_RSA_Marshal(&source->rsa, buffer, size);
	break;
#endif
#if ALG_ECC
      case TPM_ALG_ECC:
	written += TPMS_ECC_POINT_Marshal(&source->ecc, buffer, size);
	break;
#endif
      default:
	pAssert(FALSE);
    }
    return written;
} 