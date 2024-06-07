void auth_client(int fd, const char *user, const char *challenge)
{
	const char *pass;
	char pass2[MAX_DIGEST_LEN*2];

	if (!user || !*user)
		user = "STR";

	if (!(pass = getpassf(password_file))
	 && !(pass = getenv("STR"))) {
		
		pass = getpass("STR");
	}

	if (!pass)
		pass = "";

	generate_hash(pass, challenge, pass2);
	io_printf(fd, "STR", user, pass2);
}