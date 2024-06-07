static UINT cliprdr_server_receive_temporary_directory(CliprdrServerContext* context, wStream* s,
                                                       const CLIPRDR_HEADER* header)
{
	size_t length;
	WCHAR* wszTempDir;
	CLIPRDR_TEMP_DIRECTORY tempDirectory;
	CliprdrServerPrivate* cliprdr = (CliprdrServerPrivate*)context->handle;
	size_t slength;
	UINT error = CHANNEL_RC_OK;

	WINPR_UNUSED(header);
	if ((slength = Stream_GetRemainingLength(s)) < 520)
	{
		WLog_ERR(TAG, "STR",
		         slength);
		return CHANNEL_RC_NO_MEMORY;
	}

	wszTempDir = (WCHAR*)Stream_Pointer(s);

	if (wszTempDir[260] != 0)
	{
		WLog_ERR(TAG, "STR");
		return ERROR_INVALID_DATA;
	}

	free(cliprdr->temporaryDirectory);
	cliprdr->temporaryDirectory = NULL;

	if (ConvertFromUnicode(CP_UTF8, 0, wszTempDir, -1, &(cliprdr->temporaryDirectory), 0, NULL,
	                       NULL) < 1)
	{
		WLog_ERR(TAG, "STR");
		return ERROR_INVALID_DATA;
	}

	length = strnlen(cliprdr->temporaryDirectory, 520);

	if (length > 519)
		length = 519;

	CopyMemory(tempDirectory.szTempDir, cliprdr->temporaryDirectory, length);
	tempDirectory.szTempDir[length] = '\0';
	WLog_DBG(TAG, "STR", cliprdr->temporaryDirectory);
	IFCALLRET(context->TempDirectory, error, context, &tempDirectory);

	if (error)
		WLog_ERR(TAG, "STR", error);

	return error;
}