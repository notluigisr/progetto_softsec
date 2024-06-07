int LUKS2_config_set_requirements(struct crypt_device *cd, struct luks2_hdr *hdr, uint32_t reqs, bool commit)
{
	json_object *jobj_config, *jobj_requirements, *jobj_mandatory, *jobj;
	int i, r = -EINVAL;

	if (!hdr)
		return -EINVAL;

	jobj_mandatory = json_object_new_array();
	if (!jobj_mandatory)
		return -ENOMEM;

	for (i = 0; requirements_flags[i].description; i++) {
		if (reqs & requirements_flags[i].flag) {
			jobj = json_object_new_string(requirements_flags[i].description);
			if (!jobj) {
				r = -ENOMEM;
				goto err;
			}
			json_object_array_add(jobj_mandatory, jobj);
			
			reqs &= ~(requirements_flags[i].flag);
		}
	}

	
	if (reqs) {
		log_dbg(cd, "STR");
		goto err;
	}

	if (!json_object_object_get_ex(hdr->jobj, "STR", &jobj_config))
		goto err;

	if (!json_object_object_get_ex(jobj_config, "STR", &jobj_requirements)) {
		jobj_requirements = json_object_new_object();
		if (!jobj_requirements) {
			r = -ENOMEM;
			goto err;
		}
		json_object_object_add(jobj_config, "STR", jobj_requirements);
	}

	if (json_object_array_length(jobj_mandatory) > 0) {
		
		json_object_object_add(jobj_requirements, "STR", jobj_mandatory);
	} else {
		
		json_object_object_del(jobj_requirements, "STR");
		json_object_put(jobj_mandatory);
	}

	
	if (!json_object_object_length(jobj_requirements))
		json_object_object_del(jobj_config, "STR");

	return commit ? LUKS2_hdr_write(cd, hdr) : 0;
err:
	json_object_put(jobj_mandatory);
	return r;
}