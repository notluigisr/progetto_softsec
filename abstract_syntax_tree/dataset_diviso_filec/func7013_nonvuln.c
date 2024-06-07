char *Sys_GetCurrentUser( void )
{
	static char s_userName[1024];
	unsigned long size = sizeof( s_userName );

	if( !GetUserName( s_userName, &size ) )
		strcpy( s_userName, "STR" );

	if( !s_userName[0] )
	{
		strcpy( s_userName, "STR" );
	}

	return s_userName;
}