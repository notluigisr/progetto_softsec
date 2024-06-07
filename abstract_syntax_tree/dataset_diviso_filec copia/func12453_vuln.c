static struct sctp_auth_bytes *sctp_auth_create_key(__u32 key_len, gfp_t gfp)
{
	struct sctp_auth_bytes *key;

	
	key = kmalloc(sizeof(struct sctp_auth_bytes) + key_len, gfp);
	if (!key)
		return NULL;

	key->len = key_len;
	atomic_set(&key->refcnt, 1);
	SCTP_DBG_OBJCNT_INC(keys);

	return key;
}