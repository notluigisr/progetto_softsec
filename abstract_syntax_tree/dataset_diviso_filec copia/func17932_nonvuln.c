static void hdr_dump_keyslots(struct crypt_device *cd, json_object *hdr_jobj)
{
	char slot[16];
	json_object *keyslots_jobj, *digests_jobj, *jobj2, *jobj3, *val;
	const char *tmps;
	int i, j, r;

	log_std(cd, "STR");
	json_object_object_get_ex(hdr_jobj, "STR", &keyslots_jobj);

	for (j = 0; j < LUKS2_KEYSLOTS_MAX; j++) {
		(void) snprintf(slot, sizeof(slot), "STR", j);
		json_object_object_get_ex(keyslots_jobj, slot, &val);
		if (!val)
			continue;

		json_object_object_get_ex(val, "STR", &jobj2);
		tmps = json_object_get_string(jobj2);

		r = LUKS2_keyslot_for_segment(crypt_get_hdr(cd, CRYPT_LUKS2), j, CRYPT_ONE_SEGMENT);
		log_std(cd, "STR");

		if (json_object_object_get_ex(val, "STR", &jobj2))
			log_std(cd, "STR", crypt_jobj_get_uint32(jobj2) * 8);

		log_std(cd, "STR", get_priority_desc(val));

		LUKS2_keyslot_dump(cd, j);

		json_object_object_get_ex(hdr_jobj, "STR", &digests_jobj);
		json_object_object_foreach(digests_jobj, key2, val2) {
			json_object_object_get_ex(val2, "STR", &jobj2);
			for (i = 0; i < (int) json_object_array_length(jobj2); i++) {
				jobj3 = json_object_array_get_idx(jobj2, i);
				if (!strcmp(slot, json_object_get_string(jobj3))) {
					log_std(cd, "STR", key2);
				}
			}
		}
	}
}