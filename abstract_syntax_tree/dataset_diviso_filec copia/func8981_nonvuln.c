GF_Err dump_isom_cover_art(GF_ISOFile *file, char *inName, Bool is_final_name)
{
	const u8 *tag;
	FILE *t;
	u32 tag_len;
	GF_Err e = gf_isom_apple_get_tag(file, GF_ISOM_ITUNE_COVER_ART, &tag, &tag_len);
	if (e!=GF_OK) {
		if (e==GF_URL_ERROR) {
			M4_LOG(GF_LOG_WARNING, ("STR"));
			return GF_OK;
		}
		return e;
	}

	if (inName) {
		char szName[1024];
		if (is_final_name) {
			strcpy(szName, inName);
		} else {
			sprintf(szName, "STR");
		}
		t = gf_fopen(szName, "STR");
		if (!t) {
			M4_LOG(GF_LOG_ERROR, ("STR", szName));
			return GF_IO_ERR;
		}
	} else {
		t = stdout;
	}
	gf_fwrite(tag, tag_len & 0x7FFFFFFF, t);

	if (inName) gf_fclose(t);
	return GF_OK;
}