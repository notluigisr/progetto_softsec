nfs_printfh(netdissect_options *ndo,
            register const uint32_t *dp, const u_int len)
{
	my_fsid fsid;
	uint32_t ino;
	const char *sfsname = NULL;
	char *spacep;

	if (ndo->ndo_uflag) {
		u_int i;
		char const *sep = "";

		ND_PRINT((ndo, "STR"));
		for (i=0; i<len; i++) {
			ND_PRINT((ndo, "STR", sep, dp[i]));
			sep = "STR";
		}
		ND_PRINT((ndo, "STR"));
		return;
	}

	Parse_fh((const u_char *)dp, len, &fsid, &ino, NULL, &sfsname, 0);

	if (sfsname) {
		
		static char temp[NFSX_V3FHMAX+1];

		
		strncpy(temp, sfsname, NFSX_V3FHMAX);
		temp[sizeof(temp) - 1] = '\0';
		
		spacep = strchr(temp, ' ');
		if (spacep)
			*spacep = '\0';

		ND_PRINT((ndo, "STR", temp));
	} else {
		ND_PRINT((ndo, "STR",
			     fsid.Fsid_dev.Major, fsid.Fsid_dev.Minor));
	}

	if(fsid.Fsid_dev.Minor == 257)
		
		ND_PRINT((ndo, "STR", fsid.Opaque_Handle));
	else
		ND_PRINT((ndo, "STR", (long) ino));
}