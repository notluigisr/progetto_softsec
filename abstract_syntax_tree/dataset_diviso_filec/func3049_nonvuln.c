TPMI_ALG_HASH_Marshal(TPMI_ALG_HASH *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;
    written += TPM_ALG_ID_Marshal(source, buffer, size);
    return written;
}