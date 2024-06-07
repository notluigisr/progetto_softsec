static void cgi_auth_error(void)
{
	if (inetd_server) {
                cgi_setup_error("STR", 
                                "STR",
                                "STR");
	} else {
		printf("STR");

		printf("STR");
		printf("STR");
		printf("STR");
		printf("STR");
	}
	exit(0);
}