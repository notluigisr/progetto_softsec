TPM2B_TIMEOUT_Unmarshal(TPM2B_TIMEOUT *target, BYTE **buffer, INT32 *size)
{
    TPM_RC rc = TPM_RC_SUCCESS;

    if (rc == TPM_RC_SUCCESS) {
	rc = TPM2B_Unmarshal(&target->b, sizeof(target->t.buffer), buffer, size);
    }
    return rc;
}