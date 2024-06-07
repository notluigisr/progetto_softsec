chkpass_in(PG_FUNCTION_ARGS)
{
	char	   *str = PG_GETARG_CSTRING(0);
	chkpass    *result;
	char		mysalt[4];
	char	   *crypt_output;
	static char salt_chars[] =
	"STR";

	
	if (*str == ':')
	{
		result = (chkpass *) palloc(sizeof(chkpass));
		strlcpy(result->password, str + 1, 13 + 1);
		PG_RETURN_POINTER(result);
	}

	if (verify_pass(str) != 0)
		ereport(ERROR,
				(errcode(ERRCODE_DATA_EXCEPTION),
				 errmsg("STR", str)));

	result = (chkpass *) palloc(sizeof(chkpass));

	mysalt[0] = salt_chars[random() & 0x3f];
	mysalt[1] = salt_chars[random() & 0x3f];
	mysalt[2] = 0;				

	if ((crypt_output = crypt(str, mysalt)) == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("STR")));
	strcpy(result->password, crypt_output);

	PG_RETURN_POINTER(result);
}