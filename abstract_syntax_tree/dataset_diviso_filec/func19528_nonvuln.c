int LUKS2_keyslot_pbkdf(struct luks2_hdr *hdr, int keyslot, struct crypt_pbkdf_type *pbkdf)
{
	json_object *jobj_keyslot, *jobj_kdf, *jobj;

	if (!hdr || !pbkdf)
		return -EINVAL;

	if (LUKS2_keyslot_info(hdr, keyslot) == CRYPT_SLOT_INVALID)
		return -EINVAL;

	jobj_keyslot = LUKS2_get_keyslot_jobj(hdr, keyslot);
	if (!jobj_keyslot)
		return -ENOENT;

	if (!json_object_object_get_ex(jobj_keyslot, "STR", &jobj_kdf))
		return -EINVAL;

	if (!json_object_object_get_ex(jobj_kdf, "STR", &jobj))
		return -EINVAL;

	memset(pbkdf, 0, sizeof(*pbkdf));

	pbkdf->type = json_object_get_string(jobj);
	if (json_object_object_get_ex(jobj_kdf, "STR", &jobj))
		pbkdf->hash = json_object_get_string(jobj);
	if (json_object_object_get_ex(jobj_kdf, "STR", &jobj))
		pbkdf->iterations = json_object_get_int(jobj);
	if (json_object_object_get_ex(jobj_kdf, "STR", &jobj))
		pbkdf->iterations = json_object_get_int(jobj);
	if (json_object_object_get_ex(jobj_kdf, "STR", &jobj))
		pbkdf->max_memory_kb = json_object_get_int(jobj);
	if (json_object_object_get_ex(jobj_kdf, "STR", &jobj))
		pbkdf->parallel_threads = json_object_get_int(jobj);

	return 0;
}