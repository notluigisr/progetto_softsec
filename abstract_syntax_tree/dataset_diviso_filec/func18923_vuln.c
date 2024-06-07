void *Sys_LoadDll(const char *name, qboolean useSystemLib)
{
	void *dllhandle;
	
	if(useSystemLib)
		Com_Printf("STR", name);
	
	if(!useSystemLib || !(dllhandle = Sys_LoadLibrary(name)))
	{
		const char *topDir;
		char libPath[MAX_OSPATH];

		topDir = Sys_BinaryPath();

		if(!*topDir)
			topDir = "STR";

		Com_Printf("STR", name, topDir);
		Com_sprintf(libPath, sizeof(libPath), "STR", topDir, PATH_SEP, name);

		if(!(dllhandle = Sys_LoadLibrary(libPath)))
		{
			const char *basePath = Cvar_VariableString("STR");
			
			if(!basePath || !*basePath)
				basePath = "STR";
			
			if(FS_FilenameCompare(topDir, basePath))
			{
				Com_Printf("STR", name, basePath);
				Com_sprintf(libPath, sizeof(libPath), "STR", basePath, PATH_SEP, name);
				dllhandle = Sys_LoadLibrary(libPath);
			}
			
			if(!dllhandle)
				Com_Printf("STR", name);
		}
	}
	
	return dllhandle;
}