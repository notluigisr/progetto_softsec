TPMS_SIGNATURE_ECDSA_Unmarshal(TPMS_SIGNATURE_ECDSA *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;
     
    if (rc == TPM_RC_SUCCESS) {
	rc = TPMS_SIGNATURE_ECC_Unmarshal(target, buffer, size);
    }
    return rc;
}