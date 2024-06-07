TPMA_NV_Unmarshal(TPMA_NV *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;

    if (rc == TPM_RC_SUCCESS) {
	rc = UINT32_Unmarshal((UINT32 *)target, buffer, size);  
    }
    if (rc == TPM_RC_SUCCESS) {
	if (*target & TPMA_NV_RESERVED) {
	    rc = TPM_RC_RESERVED_BITS;
	}
    }
    return rc;
}