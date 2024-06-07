rpmRC hdrblobInit(const void *uh, size_t uc,
		rpmTagVal regionTag, int exact_size,
		struct hdrblob_s *blob, char **emsg)
{
    rpmRC rc = RPMRC_FAIL;

    memset(blob, 0, sizeof(*blob));
    blob->ei = (int32_t *) uh; 
    blob->il = ntohl(blob->ei[0]);
    blob->dl = ntohl(blob->ei[1]);
    blob->pe = (entryInfo) &(blob->ei[2]);
    blob->pvlen = sizeof(blob->il) + sizeof(blob->dl) +
		  (blob->il * sizeof(*blob->pe)) + blob->dl;
    blob->dataStart = (uint8_t *) (blob->pe + blob->il);
    blob->dataEnd = blob->dataStart + blob->dl;

    
    if (blob->pvlen >= headerMaxbytes || (uc && blob->pvlen != uc)) {
	rasprintf(emsg, _("STR"),
			blob->pvlen, blob->il, blob->dl);
	goto exit;
    }

    if (hdrblobVerifyRegion(regionTag, exact_size, blob, emsg) == RPMRC_FAIL)
	goto exit;

    
    if (hdrblobVerifyInfo(blob, emsg))
	goto exit;

    rc = RPMRC_OK;

exit:
    return rc;
}