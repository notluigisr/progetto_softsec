static json_object *reencrypt_make_hot_segments_forward(struct crypt_device *cd,
		struct luks2_hdr *hdr,
		struct luks2_reencrypt *rh,
		uint64_t device_size,
		uint64_t data_offset)
{
	json_object *jobj_segs_hot, *jobj_reenc_seg, *jobj_old_seg, *jobj_new_seg;
	uint64_t fixed_length, tmp = rh->offset + rh->length;
	unsigned int sg = 0;

	jobj_segs_hot = json_object_new_object();
	if (!jobj_segs_hot)
		return NULL;

	if (rh->offset) {
		jobj_new_seg = reencrypt_make_segment_new(cd, hdr, rh, data_offset, 0, 0, &rh->offset);
		if (!jobj_new_seg)
			goto err;
		json_object_object_add_by_uint(jobj_segs_hot, sg++, jobj_new_seg);
	}

	jobj_reenc_seg = reencrypt_make_segment_reencrypt(cd, hdr, rh, data_offset, rh->offset, rh->offset, &rh->length);
	if (!jobj_reenc_seg)
		goto err;

	json_object_object_add_by_uint(jobj_segs_hot, sg++, jobj_reenc_seg);

	if (tmp < device_size) {
		fixed_length = device_size - tmp;
		jobj_old_seg = reencrypt_make_segment_old(cd, hdr, rh, data_offset + rh->data_shift, rh->offset + rh->length, rh->fixed_length ? &fixed_length : NULL);
		if (!jobj_old_seg)
			goto err;
		json_object_object_add_by_uint(jobj_segs_hot, sg, jobj_old_seg);
	}

	return jobj_segs_hot;
err:
	json_object_put(jobj_segs_hot);
	return NULL;
}