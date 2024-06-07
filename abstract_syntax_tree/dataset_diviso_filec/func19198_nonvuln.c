TRIO_PUBLIC int trio_asprintf TRIO_VARGS3((result, format, va_alist), char** result,
                                          TRIO_CONST char* format, TRIO_VA_DECL)
{
	va_list args;
	int status;
	trio_string_t* info;

	assert(VALID(format));

	*result = NULL;

	info = trio_xstring_duplicate("");
	if (info == NULL)
	{
		status = TRIO_ERROR_RETURN(TRIO_ENOMEM, 0);
	}
	else
	{
		TRIO_VA_START(args, format);
		status = TrioFormat(info, 0, TrioOutStreamStringDynamic, format, args, NULL, NULL);
		TRIO_VA_END(args);
		if (status >= 0)
		{
			trio_string_terminate(info);
			*result = trio_string_extract(info);
		}
		trio_string_destroy(info);
	}
	return status;
}