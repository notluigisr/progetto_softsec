TPML_DIGEST_VALUES_Marshal(TPML_DIGEST_VALUES *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;
    UINT32 i;
    
    written += UINT32_Marshal(&source->count, buffer, size);
    for (i = 0 ; i < source->count ; i++) {
	written += TPMT_HA_Marshal(&source->digests[i], buffer, size);
    }
    return written;
}