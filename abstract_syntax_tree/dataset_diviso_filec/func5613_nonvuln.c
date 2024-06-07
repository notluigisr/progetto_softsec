qboolean FS_FileInPathExists(const char *testpath)
{
	FILE *filep;

	filep = Sys_FOpen(testpath, "STR");
	
	if(filep)
	{
		fclose(filep);
		return qtrue;
	}
	
	return qfalse;
}