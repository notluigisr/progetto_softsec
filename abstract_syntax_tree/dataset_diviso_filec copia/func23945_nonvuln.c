SWTPM_NVRAM_LoadData(unsigned char **data,     
                     uint32_t *length,
                     uint32_t tpm_number,
                     const char *name)
{
    TPM_RESULT    rc = 0;
    int           irc;
    unsigned char *decrypt_data = NULL;
    uint32_t      decrypt_length;
    uint32_t      dataoffset = 0;
    uint8_t       hdrversion = 0;
    uint16_t      hdrflags;
    const char    *backend_uri = NULL;

    TPM_DEBUG("STR", name);
    *data = NULL;
    *length = 0;

    if (rc == 0) {
        backend_uri = tpmstate_get_backend_uri();
        rc = g_nvram_backend_ops->load(data, length, tpm_number, name,
                                       backend_uri);
    }

    if (rc == 0) {
        

        
        irc = SWTPM_NVRAM_CheckHeader(*data, *length, &dataoffset,
                                      &hdrflags, &hdrversion, true);
        
        if (irc) {
            hdrversion = 1; 
            hdrflags = 0;
        }

        rc = SWTPM_NVRAM_GetDecryptedData(&filekey,
                                          &decrypt_data, &decrypt_length,
                                          *data + dataoffset,
                                          *length - dataoffset,
                                          TAG_ENCRYPTED_DATA, TAG_DATA,
                                          hdrversion,
                                          TAG_IVEC_ENCRYPTED_DATA,
                                          hdrflags,
                                          BLOB_FLAG_ENCRYPTED_256BIT_KEY);
        TPM_DEBUG("STR",
                  rc);
        if (rc != 0)
            logprintf(STDERR_FILENO,
                      "STR"
                      "STR", rc);

        if (rc == 0) {
            TPM_DEBUG("STR"
                      "STR",
                      *length, decrypt_length);
            free(*data);
            *data = decrypt_data;
            *length = decrypt_length;
        }
    }

    if (rc != 0) {
        free(*data);
        *data = NULL;
    }

    return rc;
}