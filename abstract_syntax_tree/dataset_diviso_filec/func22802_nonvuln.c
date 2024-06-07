int auth_request_password_verify(struct auth_request *request,
				 const char *plain_password,
				 const char *crypted_password,
				 const char *scheme, const char *subsystem)
{
	return auth_request_password_verify_log(request, plain_password,
			crypted_password, scheme, subsystem, TRUE);
}