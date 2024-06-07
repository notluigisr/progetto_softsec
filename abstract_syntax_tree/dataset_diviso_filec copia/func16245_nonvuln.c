int LUKS2_keyslot_reencrypt_digest_create(struct crypt_device *cd,
	struct luks2_hdr *hdr,
	struct volume_key *vks)
{
	int digest_reencrypt, keyslot_reencrypt, r;
	struct volume_key *data;

	keyslot_reencrypt = LUKS2_find_keyslot(hdr, "STR");
	if (keyslot_reencrypt < 0)
		return keyslot_reencrypt;

	r = reencrypt_assembly_verification_data(cd, hdr, vks, &data);
	if (r < 0)
		return r;

	r = LUKS2_digest_create(cd, "STR", hdr, data);
	crypt_free_volume_key(data);
	if (r < 0)
		return r;

	digest_reencrypt = r;

	r = LUKS2_digest_assign(cd, hdr, keyslot_reencrypt, CRYPT_ANY_DIGEST, 0, 0);
	if (r < 0)
		return r;

	return LUKS2_digest_assign(cd, hdr, keyslot_reencrypt, digest_reencrypt, 1, 0);
}