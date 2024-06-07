TPMT_SYM_DEF_OBJECT_Marshal(TPMT_SYM_DEF_OBJECT *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;

    written += TPMI_ALG_SYM_OBJECT_Marshal(&source->algorithm, buffer, size);
    written += TPMU_SYM_KEY_BITS_Marshal(&source->keyBits, buffer, size, source->algorithm);
    written += TPMU_SYM_MODE_Marshal(&source->mode, buffer, size, source->algorithm);
    return written;
}