void ntlm_print_negotiate_flags(UINT32 flags)
{
	int i;
	const char* str;
	WLog_INFO(TAG, "STR", flags);

	for (i = 31; i >= 0; i--)
	{
		if ((flags >> i) & 1)
		{
			str = NTLM_NEGOTIATE_STRINGS[(31 - i)];
			WLog_INFO(TAG, "STR", str, (31 - i));
		}
	}
}