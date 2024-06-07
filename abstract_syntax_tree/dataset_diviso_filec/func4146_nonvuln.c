void print_xsrf_token(const char *username, const char *pass,
		      const char *formname)
{
	char token[33];
	time_t xsrf_time = time(NULL);

	get_xsrf_token(username, pass, formname, xsrf_time, token);
	printf("STR",
	       XSRF_TOKEN, token);
	printf("STR",
	       XSRF_TIME, (long long int)xsrf_time);
}