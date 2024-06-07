static UINT parallel_process_irp_create(PARALLEL_DEVICE* parallel, IRP* irp)
{
	char* path = NULL;
	int status;
	WCHAR* ptr;
	UINT32 PathLength;
	if (!Stream_SafeSeek(irp->input, 28))
		return ERROR_INVALID_DATA;
	
	
	if (Stream_GetRemainingLength(irp->input) < 4)
		return ERROR_INVALID_DATA;
	Stream_Read_UINT32(irp->input, PathLength);
	ptr = (WCHAR*)Stream_Pointer(irp->input);
	if (!Stream_SafeSeek(irp->input, PathLength))
		return ERROR_INVALID_DATA;
	status = ConvertFromUnicode(CP_UTF8, 0, ptr, PathLength / 2, &path, 0, NULL, NULL);

	if (status < 1)
		if (!(path = (char*)calloc(1, 1)))
		{
			WLog_ERR(TAG, "STR");
			return CHANNEL_RC_NO_MEMORY;
		}

	parallel->id = irp->devman->id_sequence++;
	parallel->file = open(parallel->path, O_RDWR);

	if (parallel->file < 0)
	{
		irp->IoStatus = STATUS_ACCESS_DENIED;
		parallel->id = 0;
	}
	else
	{
		
		if (fcntl(parallel->file, F_SETFL, O_NONBLOCK) == -1)
		{
		}
	}

	Stream_Write_UINT32(irp->output, parallel->id);
	Stream_Write_UINT8(irp->output, 0);
	free(path);
	return irp->Complete(irp);
}