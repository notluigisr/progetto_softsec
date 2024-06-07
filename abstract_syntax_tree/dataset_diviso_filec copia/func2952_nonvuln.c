TPMI_CAMELLIA_KEY_BITS_Unmarshal(TPMI_CAMELLIA_KEY_BITS *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;
    TPMI_CAMELLIA_KEY_BITS orig_target = *target; 

    if (rc == TPM_RC_SUCCESS) {
	rc = TPM_KEY_BITS_Unmarshal(target, buffer, size);  
    }
    if (rc == TPM_RC_SUCCESS) {
	switch (*target) {
	  case 128:
	    break;
	  default:
	    rc = TPM_RC_VALUE;
	    *target = orig_target; 
	}
    }
    return rc;
}