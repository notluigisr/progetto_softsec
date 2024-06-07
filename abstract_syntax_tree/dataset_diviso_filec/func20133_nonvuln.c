BOOL IsVolumeClassFilterRegistered ()
{
	UNICODE_STRING name;
	NTSTATUS status;
	BOOL registered = FALSE;

	PKEY_VALUE_PARTIAL_INFORMATION data;

	RtlInitUnicodeString (&name, L"STR");
	status = TCReadRegistryKey (&name, L"STR", &data);

	if (NT_SUCCESS (status))
	{
		if (data->Type == REG_MULTI_SZ && data->DataLength >= 9 * sizeof (wchar_t))
		{
			
			ULONG i;
			for (i = 0; i <= data->DataLength - 9 * sizeof (wchar_t); ++i)
			{
				if (memcmp (data->Data + i, L"STR", 9 * sizeof (wchar_t)) == 0)
				{
					Dump ("STR");
					registered = TRUE;
					break;
				}
			}
		}

		TCfree (data);
	}

	return registered;
}