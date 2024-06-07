qboolean Sys_PIDIsRunning( int pid )
{
	return kill( pid, 0 ) == 0;
}