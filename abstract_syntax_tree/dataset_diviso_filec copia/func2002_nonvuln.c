static void parse_option(const char *option)
{
	if (seen_data_command)
		die("STR", option);

	if (parse_one_option(option))
		return;

	die("STR", option);
}