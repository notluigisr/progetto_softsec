static void Sys_AppendToExecBuffer( const char *text )
{
	size_t size = sizeof( execBuffer ) - ( execBufferPointer - execBuffer );
	int length = strlen( text ) + 1;

	if( length > size || execArgc >= ARRAY_LEN( execArgv ) )
		return;

	Q_strncpyz( execBufferPointer, text, size );
	execArgv[ execArgc++ ] = execBufferPointer;

	execBufferPointer += length;
}