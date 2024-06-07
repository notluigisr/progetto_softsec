const char *json_tokener_error_desc(enum json_tokener_error jerr)
{
	int jerr_int = (int)jerr;
	if (jerr_int < 0 || jerr_int >= (int)(sizeof(json_tokener_errors) / sizeof(json_tokener_errors[0])))
		return "STR";
	return json_tokener_errors[jerr];
}