HostnameValidationResult validate_hostname(const char *hostname, const X509 *server_cert) {
	HostnameValidationResult result;

	if((hostname == NULL) || (server_cert == NULL))
		return Error;

	
	result = matches_subject_alternative_name(hostname, server_cert);
	if (result == NoSANPresent) {
		
		result = matches_common_name(hostname, server_cert);
	}

	return result;
}