int crypt_activate_by_token(struct crypt_device *cd,
	const char *name, int token, void *usrptr, uint32_t flags)
{
	return crypt_activate_by_token_pin(cd, name, NULL, token, NULL, 0, usrptr, flags);
}