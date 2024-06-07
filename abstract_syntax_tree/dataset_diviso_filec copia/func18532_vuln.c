static inline key_ref_t __key_update(key_ref_t key_ref,
				     struct key_preparsed_payload *prep)
{
	struct key *key = key_ref_to_ptr(key_ref);
	int ret;

	
	ret = key_permission(key_ref, KEY_NEED_WRITE);
	if (ret < 0)
		goto error;

	ret = -EEXIST;
	if (!key->type->update)
		goto error;

	down_write(&key->sem);

	ret = key->type->update(key, prep);
	if (ret == 0)
		
		clear_bit(KEY_FLAG_NEGATIVE, &key->flags);

	up_write(&key->sem);

	if (ret < 0)
		goto error;
out:
	return key_ref;

error:
	key_put(key);
	key_ref = ERR_PTR(ret);
	goto out;
}