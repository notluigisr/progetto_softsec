TPMU_ASYM_SCHEME_Marshal(TPMU_ASYM_SCHEME  *source, BYTE **buffer, INT32 *size, UINT32 selector)
{
    UINT16 written = 0;

    switch (selector) {
#if ALG_ECDH
      case TPM_ALG_ECDH:
	written += TPMS_KEY_SCHEME_ECDH_Marshal(&source->ecdh, buffer, size);
	break;
#endif
#if ALG_ECMQV
      case TPM_ALG_ECMQV:
	written += TPMS_KEY_SCHEME_ECMQV_Marshal(&source->ecmqv, buffer, size);
	break;
#endif
#if ALG_RSASSA
      case TPM_ALG_RSASSA:
	written += TPMS_SIG_SCHEME_RSASSA_Marshal(&source->rsassa, buffer, size);
	break;
#endif
#if ALG_RSAPSS
      case TPM_ALG_RSAPSS:
	written += TPMS_SIG_SCHEME_RSAPSS_Marshal(&source->rsapss, buffer, size);
	break;
#endif
#if ALG_ECDSA
      case TPM_ALG_ECDSA:
	written += TPMS_SIG_SCHEME_ECDSA_Marshal(&source->ecdsa, buffer, size);
	break;
#endif
#if ALG_ECDAA
      case TPM_ALG_ECDAA:
	written += TPMS_SIG_SCHEME_ECDAA_Marshal(&source->ecdaa, buffer, size);
	break;
#endif
#if ALG_SM2
      case TPM_ALG_SM2:
	written += TPMS_SIG_SCHEME_SM2_Marshal(&source->sm2, buffer, size);
	break;
#endif
#if ALG_ECSCHNORR
      case TPM_ALG_ECSCHNORR:
	written += TPMS_SIG_SCHEME_ECSCHNORR_Marshal(&source->ecschnorr, buffer, size);
	break;
#endif
#if ALG_RSAES
      case TPM_ALG_RSAES:
	written += TPMS_ENC_SCHEME_RSAES_Marshal(&source->rsaes, buffer, size);
	break;
#endif
#if ALG_OAEP
      case TPM_ALG_OAEP:
	written += TPMS_ENC_SCHEME_OAEP_Marshal(&source->oaep, buffer, size);
	break;
#endif
      case TPM_ALG_NULL:
	break;
      default:
	pAssert(FALSE);
    }
    return written;
}