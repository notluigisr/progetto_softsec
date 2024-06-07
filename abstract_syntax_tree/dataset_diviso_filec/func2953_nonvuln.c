_xexception::_xexception(UINT string, ...)
{
	CString format;
	va_list va;

	format.LoadString(string);

	va_start(va, string);
	resString.FormatV(format, va);
	va_end(va);
}