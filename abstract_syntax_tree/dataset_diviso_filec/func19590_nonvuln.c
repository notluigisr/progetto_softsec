GF_Err stsd_AddBox(GF_Box *s, GF_Box *a)
{
	GF_UnknownBox *def;
	GF_SampleDescriptionBox *ptr = (GF_SampleDescriptionBox *)s;
	if (!a) return GF_OK;

	if (gf_box_valid_in_parent(a, "STR")) {
		return gf_isom_box_add_default((GF_Box*)ptr, a);
	}
	switch (a->type) {
	
	
	case GF_ISOM_BOX_TYPE_UNKNOWN:
		def = (GF_UnknownBox *)a;
		
		if (def->dataSize < 8) {
			gf_isom_box_del(a);
			return GF_ISOM_INVALID_MEDIA;
		}
		return gf_isom_box_add_default((GF_Box*)ptr, a);

	default:
		GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("STR", gf_4cc_to_str(a->type)));
		return GF_ISOM_INVALID_FILE;
	}
}