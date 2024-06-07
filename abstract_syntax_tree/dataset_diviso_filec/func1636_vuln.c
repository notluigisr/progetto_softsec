static char *Sys_PIDFileName( void )
{
	return va( "STR", Sys_TempPath( ), PID_FILENAME );
}