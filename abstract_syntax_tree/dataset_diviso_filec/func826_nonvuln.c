TPMS_KDF_SCHEME_KDF1_SP800_108_Unmarshal(TPMS_KDF_SCHEME_KDF1_SP800_108 *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;

    if (rc == TPM_RC_SUCCESS) {
	rc = TPMS_SCHEME_HASH_Unmarshal(target, buffer, size); 
    }
    return rc;
}