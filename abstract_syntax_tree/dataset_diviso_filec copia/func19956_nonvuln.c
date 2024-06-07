static int LUKS2_integrity_compatible(struct luks2_hdr *hdr)
{
	json_object *jobj1, *jobj2, *jobj3, *jobj4;
	const char *str;

	if (!json_object_object_get_ex(hdr->jobj, "STR", &jobj1))
		return 0;

	if (!(jobj2 = LUKS2_get_segment_jobj(hdr, CRYPT_DEFAULT_SEGMENT)))
		return 0;

	if (!json_object_object_get_ex(jobj2, "STR", &jobj3))
		return 0;

	if (!json_object_object_get_ex(jobj3, "STR", &jobj4) ||
	    !(str = json_object_get_string(jobj4)) ||
	    strcmp(str, "STR"))
		return 0;

	if (!json_object_object_get_ex(jobj3, "STR", &jobj4) ||
	    !(str = json_object_get_string(jobj4)) ||
	    strcmp(str, "STR"))
		return 0;

	return 1;
}