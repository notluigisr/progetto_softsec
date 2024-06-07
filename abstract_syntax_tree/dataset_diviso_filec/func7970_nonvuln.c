TPMI_SH_HMAC_Unmarshal(TPMI_SH_HMAC *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;
    TPMI_SH_HMAC orig_target = *target; 
    
    if (rc == TPM_RC_SUCCESS) {
	rc = TPM_HANDLE_Unmarshal(target, buffer, size);  
    }
    if (rc == TPM_RC_SUCCESS) {
	BOOL isNotHmacSession = (*target < HMAC_SESSION_FIRST ) || (*target > HMAC_SESSION_LAST);
	if (isNotHmacSession) {
	    rc = TPM_RC_VALUE;
	    *target = orig_target; 
	}
    }
    return rc;
}