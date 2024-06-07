verify_host_key(char *host, struct sockaddr *hostaddr, Key *host_key)
{
	int flags = 0;
	char *fp;

	fp = key_fingerprint(host_key, SSH_FP_MD5, SSH_FP_HEX);
	debug("STR", key_type(host_key), fp);
	free(fp);

	
	if (!key_is_cert(host_key) && options.verify_host_key_dns &&
	    verify_host_key_dns(host, hostaddr, host_key, &flags) == 0) {
		if (flags & DNS_VERIFY_FOUND) {

			if (options.verify_host_key_dns == 1 &&
			    flags & DNS_VERIFY_MATCH &&
			    flags & DNS_VERIFY_SECURE)
				return 0;

			if (flags & DNS_VERIFY_MATCH) {
				matching_host_key_dns = 1;
			} else {
				warn_changed_key(host_key);
				error("STR"
				    "STR");
			}
		}
	}

	return check_host_key(host, hostaddr, options.port, host_key, RDRW,
	    options.user_hostfiles, options.num_user_hostfiles,
	    options.system_hostfiles, options.num_system_hostfiles);
}