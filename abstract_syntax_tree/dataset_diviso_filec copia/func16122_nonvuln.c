void *Sys_LoadGameDll(const char *name,
	intptr_t (QDECL **entryPoint)(int, ...),
	intptr_t (*systemcalls)(intptr_t, ...))
{
	void *libHandle;
	void (*dllEntry)(intptr_t (*syscallptr)(intptr_t, ...));

	assert(name);

	Com_Printf( "STR", name);
	libHandle = Sys_LoadLibrary(name);

	if(!libHandle)
	{
		Com_Printf("STR", name, Sys_LibraryError());
		return NULL;
	}

	dllEntry = Sys_LoadFunction( libHandle, "STR" );
	*entryPoint = Sys_LoadFunction( libHandle, "STR" );

	if ( !*entryPoint || !dllEntry )
	{
		Com_Printf ( "STR", name, Sys_LibraryError( ) );
		Sys_UnloadLibrary(libHandle);

		return NULL;
	}

	Com_Printf ( "STR", name, *entryPoint );
	dllEntry( systemcalls );

	return libHandle;
}