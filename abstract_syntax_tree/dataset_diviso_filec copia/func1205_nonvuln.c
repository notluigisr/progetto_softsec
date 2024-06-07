static rpmRC headerVerify(rpmKeyring keyring, rpmVSFlags vsflags,
			  const void * uh, size_t uc, char ** msg)
{
    char *buf = NULL;
    int32_t * ei = (int32_t *) uh;
    int32_t il = ntohl(ei[0]);
    int32_t dl = ntohl(ei[1]);
    entryInfo pe = (entryInfo) &ei[2];
    int32_t pvlen = sizeof(il) + sizeof(dl) + (il * sizeof(*pe)) + dl;
    unsigned char * dataStart = (unsigned char *) (pe + il);
    struct indexEntry_s entry;
    int32_t ril = 0;
    int32_t rdl = 0;
    rpmRC rc = RPMRC_FAIL;	

    
    if (uc > 0 && pvlen != uc) {
	rasprintf(&buf, _("STR"),
		(int)uc, (int)il, (int)dl);
	goto exit;
    }

    
    rc = headerVerifyRegion(RPMTAG_HEADERIMMUTABLE,
			    &entry, il, dl, pe, dataStart,
			    &ril, &rdl, &buf);

    
    if (rc == RPMRC_OK) {
	rc = headerSigVerify(keyring, vsflags,
			     il, dl, ril, rdl,
			     pe, dataStart, &buf);
    }

exit:
    
    if (rc == RPMRC_NOTFOUND) {
	int xx = headerVerifyInfo(ril-1, dl, pe+1, &entry.info, 0);
	if (xx != -1) {
	    rasprintf(&buf,
		_("STR"),
		xx+1, entry.info.tag, entry.info.type,
		entry.info.offset, entry.info.count);
	    rc = RPMRC_FAIL;
	} else {
	    rasprintf(&buf, "STR");
	    rc = RPMRC_OK;
	}
    }

    if (msg) 
	*msg = buf;
    else
	free(buf);

    return rc;
}