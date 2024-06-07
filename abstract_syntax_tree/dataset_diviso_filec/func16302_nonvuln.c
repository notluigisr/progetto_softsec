static UINT serial_process_irp_close(SERIAL_DEVICE* serial, IRP* irp)
{
	if (Stream_GetRemainingLength(irp->input) < 32)
		return ERROR_INVALID_DATA;

	Stream_Seek(irp->input, 32); 

	if (!CloseHandle(serial->hComm))
	{
		WLog_Print(serial->log, WLOG_WARN, "STR",
		           serial->device.name, irp->device->id);
		irp->IoStatus = STATUS_UNSUCCESSFUL;
		goto error_handle;
	}

	WLog_Print(serial->log, WLOG_DEBUG, "STR",
	           serial->device.name, irp->device->id, irp->FileId);
	serial->hComm = NULL;
	irp->IoStatus = STATUS_SUCCESS;
error_handle:
	Stream_Zero(irp->output, 5); 
	return CHANNEL_RC_OK;
}