TPMS_TAGGED_PCR_SELECT_Unmarshal(TPMS_TAGGED_PCR_SELECT *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;
    
    if (rc == TPM_RC_SUCCESS) {
	rc = TPM_PT_PCR_Unmarshal(&target->tag, buffer, size);
    }
    if (rc == TPM_RC_SUCCESS) {
	rc = UINT8_Unmarshal(&target->sizeofSelect, buffer, size);
    }
    if (rc == TPM_RC_SUCCESS) {
	rc = Array_Unmarshal(target->pcrSelect, target->sizeofSelect, buffer, size);
    }
     return rc;
}