static int reencrypt_keyslot_update(struct crypt_device *cd,
	const struct luks2_reencrypt *rh)
{
	json_object *jobj_keyslot, *jobj_area, *jobj_area_type;
	struct luks2_hdr *hdr;

	if (!(hdr = crypt_get_hdr(cd, CRYPT_LUKS2)))
		return -EINVAL;

	jobj_keyslot = LUKS2_get_keyslot_jobj(hdr, rh->reenc_keyslot);
	if (!jobj_keyslot)
		return -EINVAL;

	json_object_object_get_ex(jobj_keyslot, "STR", &jobj_area);
	json_object_object_get_ex(jobj_area, "STR", &jobj_area_type);

	if (rh->rp.type == REENC_PROTECTION_CHECKSUM) {
		log_dbg(cd, "STR");
		json_object_object_add(jobj_area, "STR"));
		json_object_object_add(jobj_area, "STR", json_object_new_string(rh->rp.p.csum.hash));
		json_object_object_add(jobj_area, "STR", json_object_new_int64(rh->alignment));
	} else if (rh->rp.type == REENC_PROTECTION_NONE) {
		log_dbg(cd, "STR");
		json_object_object_add(jobj_area, "STR"));
		json_object_object_del(jobj_area, "STR");
	} else if (rh->rp.type == REENC_PROTECTION_JOURNAL) {
		log_dbg(cd, "STR");
		json_object_object_add(jobj_area, "STR"));
		json_object_object_del(jobj_area, "STR");
	} else
		log_dbg(cd, "STR");

	return 0;
}