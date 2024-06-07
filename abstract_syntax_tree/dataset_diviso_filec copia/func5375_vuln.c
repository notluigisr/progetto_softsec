static void print_header(void)
{
	if (!cgi_waspost()) {
		printf("STR");
	}
	printf("STR");

	if (!include_html("STR")) {
		printf("STR");
		printf("STR");
	}
}