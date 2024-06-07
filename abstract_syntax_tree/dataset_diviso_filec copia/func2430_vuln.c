long keyctl_join_session_keyring(const char __user *_name)
{
	char *name;
	long ret;

	
	name = NULL;
	if (_name) {
		name = strndup_user(_name, KEY_MAX_DESC_SIZE);
		if (IS_ERR(name)) {
			ret = PTR_ERR(name);
			goto error;
		}
	}

	
	ret = join_session_keyring(name);
	kfree(name);

error:
	return ret;
}