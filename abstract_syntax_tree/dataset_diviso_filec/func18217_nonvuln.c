crypt_keyslot_info LUKS2_keyslot_info(struct luks2_hdr *hdr, int keyslot)
{
	if(keyslot >= LUKS2_KEYSLOTS_MAX || keyslot < 0)
		return CRYPT_SLOT_INVALID;

	if (!LUKS2_get_keyslot_jobj(hdr, keyslot))
		return CRYPT_SLOT_INACTIVE;

	if (LUKS2_digest_by_keyslot(hdr, keyslot) < 0 ||
	    LUKS2_keyslot_unbound(hdr, keyslot))
		return CRYPT_SLOT_UNBOUND;

	if (LUKS2_keyslot_active_count(hdr, CRYPT_DEFAULT_SEGMENT) == 1 &&
	    !LUKS2_keyslot_for_segment(hdr, keyslot, CRYPT_DEFAULT_SEGMENT))
		return CRYPT_SLOT_ACTIVE_LAST;

	return CRYPT_SLOT_ACTIVE;
}