const char *Sys_TempPath( void )
{
	const char *TMPDIR = getenv( "STR" );

	if( TMPDIR == NULL || TMPDIR[ 0 ] == '\0' )
		return "STR";
	else
		return TMPDIR;
}