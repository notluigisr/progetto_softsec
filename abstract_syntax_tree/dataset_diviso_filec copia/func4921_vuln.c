static UINT serial_process_irp_write(SERIAL_DEVICE* serial, IRP* irp)
{
	UINT32 Length;
	UINT64 Offset;
	DWORD nbWritten = 0;

	if (Stream_GetRemainingLength(irp->input) < 32)
		return ERROR_INVALID_DATA;

	Stream_Read_UINT32(irp->input, Length); 
	Stream_Read_UINT64(irp->input, Offset); 
	Stream_Seek(irp->input, 20);            
	
	WLog_Print(serial->log, WLOG_DEBUG, "STR", Length,
	           serial->device.name);

	
	if (CommWriteFile(serial->hComm, Stream_Pointer(irp->input), Length, &nbWritten, NULL))
	{
		irp->IoStatus = STATUS_SUCCESS;
	}
	else
	{
		WLog_Print(serial->log, WLOG_DEBUG,
		           "STR",
		           serial->device.name, nbWritten, GetLastError());
		irp->IoStatus = _GetLastErrorToIoStatus(serial);
	}

	WLog_Print(serial->log, WLOG_DEBUG, "STR", nbWritten,
	           serial->device.name);
	Stream_Write_UINT32(irp->output, nbWritten); 
	Stream_Write_UINT8(irp->output, 0);          
	return CHANNEL_RC_OK;
}