TPMS_CREATION_DATA_Marshal(TPMS_CREATION_DATA *source, BYTE **buffer, INT32 *size)
{
    UINT16 written = 0;

    written += TPML_PCR_SELECTION_Marshal(&source->pcrSelect, buffer, size);
    written += TPM2B_DIGEST_Marshal(&source->pcrDigest, buffer, size);
    written += TPMA_LOCALITY_Marshal(&source->locality, buffer, size);
    written += TPM_ALG_ID_Marshal(&source->parentNameAlg, buffer, size);
    written += TPM2B_NAME_Marshal(&source->parentName, buffer, size);
    written += TPM2B_NAME_Marshal(&source->parentQualifiedName, buffer, size);
    written += TPM2B_DATA_Marshal(&source->outsideInfo, buffer, size);
    return written;
}