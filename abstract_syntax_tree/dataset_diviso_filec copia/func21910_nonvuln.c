TPMS_RSA_PARMS_Marshal(TPMS_RSA_PARMS *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;

    written += TPMT_SYM_DEF_OBJECT_Marshal(&source->symmetric, buffer, size);
    written += TPMT_RSA_SCHEME_Marshal(&source->scheme, buffer, size);
    written += TPMI_RSA_KEY_BITS_Marshal(&source->keyBits, buffer, size);
    written += UINT32_Marshal(&source->exponent, buffer, size);
    return written;
}