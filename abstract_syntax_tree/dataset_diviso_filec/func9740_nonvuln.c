TPMI_ALG_KDF_Marshal(TPMI_ALG_KDF *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;
    written += TPM_ALG_ID_Marshal(source, buffer, size);
    return written;
}