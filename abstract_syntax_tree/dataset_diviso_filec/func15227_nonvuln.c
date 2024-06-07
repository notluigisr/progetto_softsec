int trio_vprint_ref TRIO_ARGS3((ref, format, arglist), trio_pointer_t ref, TRIO_CONST char* format,
                               va_list arglist)
{
	assert(VALID(format));

	return TrioFormatRef((trio_reference_t*)ref, format, arglist, NULL, NULL);
}