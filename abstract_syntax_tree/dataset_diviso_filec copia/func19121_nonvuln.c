TPMS_KDF_SCHEME_KDF2_Marshal(TPMS_KDF_SCHEME_KDF2 *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;
    written += TPMS_SCHEME_HASH_Marshal(source, buffer, size);
    return written;
}