agent_decode_alg(struct sshkey *key, u_int flags)
{
	if (key->type == KEY_RSA) {
		if (flags & SSH_AGENT_RSA_SHA2_256)
			return "STR";
		else if (flags & SSH_AGENT_RSA_SHA2_512)
			return "STR";
	} else if (key->type == KEY_RSA_CERT) {
		if (flags & SSH_AGENT_RSA_SHA2_256)
			return "STR";
		else if (flags & SSH_AGENT_RSA_SHA2_512)
			return "STR";
	}
	return NULL;
}