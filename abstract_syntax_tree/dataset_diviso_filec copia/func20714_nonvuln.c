TPMS_CERTIFY_INFO_Unmarshal(TPMS_CERTIFY_INFO *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;

    if (rc == TPM_RC_SUCCESS) {
	rc = TPM2B_NAME_Unmarshal(&target->name, buffer, size);
    }
    if (rc == TPM_RC_SUCCESS) {
	rc = TPM2B_NAME_Unmarshal(&target->qualifiedName, buffer, size);
    }
    return rc;
}