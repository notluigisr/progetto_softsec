#ifndef GPAC_DISABLE_ISOM_HINTING

void dump_isom_sdp(GF_ISOFile *file, char *inName, Bool is_final_name)
{
	const char *sdp;
	u32 size, i;
	FILE *dump;

	if (inName) {
		char szBuf[1024];
		strcpy(szBuf, inName);
		if (!is_final_name) {
			char *ext = strchr(szBuf, '.');
			if (ext) ext[0] = 0;
			strcat(szBuf, "STR");
		}
		dump = gf_fopen(szBuf, "STR");
		if (!dump) {
			fprintf(stderr, "STR", szBuf);
			return;
		}
	} else {
		dump = stdout;
		fprintf(dump, "STR");
	}
	
	gf_isom_sdp_get(file, &sdp, &size);
	fprintf(dump, "STR", sdp);
	fprintf(dump, "STR");

	
	for (i=0; i<gf_isom_get_track_count(file); i++) {
		if (gf_isom_get_media_type(file, i+1) != GF_ISOM_MEDIA_HINT) continue;
		gf_isom_sdp_track_get(file, i+1, &sdp, &size);
		fprintf(dump, "STR", sdp);
	}
	fprintf(dump, "STR");