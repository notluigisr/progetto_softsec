SWTPM_NVRAM_CheckHeader(unsigned char *data, uint32_t length,
                        uint32_t *dataoffset, uint16_t *hdrflags,
                        uint8_t *hdrversion, bool quiet)
{
    blobheader *bh = (blobheader *)data;

    if (length < sizeof(bh)) {
        if (!quiet)
            logprintf(STDERR_FILENO,
                      "STR", length);
        return TPM_BAD_PARAMETER;
    }

    if (ntohl(bh->totlen) != length) {
        if (!quiet)
            logprintf(STDERR_FILENO,
                      "STR",
                      htonl(bh->totlen), length);
        return TPM_BAD_PARAMETER;
    }

    if (bh->min_version > BLOB_HEADER_VERSION) {
        if (!quiet)
            logprintf(STDERR_FILENO,
                      "STR"
                      "STR", bh->min_version,
                      BLOB_HEADER_VERSION);
        return TPM_BAD_VERSION;
    }

    *hdrversion = bh->version;
    *dataoffset = ntohs(bh->hdrsize);
    *hdrflags = ntohs(bh->flags);

    return TPM_SUCCESS;
}