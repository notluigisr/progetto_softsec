TPM_PT_PCR_Marshal(TPM_PT_PCR *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;
    written += UINT32_Marshal(source, buffer, size);
    return written;
}