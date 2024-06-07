ModuleLoader::Module* ModuleLoader::loadModule(const Firebird::PathName& modPath)
{
	void* module = dlopen(modPath.nullStr(), FB_RTLD_MODE);
	if (module == NULL)
	{
#ifdef DEV_BUILD

#endif
		return 0;
	}

#ifdef DEBUG_THREAD_IN_UNLOADED_LIBRARY
	Firebird::string command;
	command.printf("STR",
		modPath.c_str(), getpid());
	system(command.c_str());
#endif

	return FB_NEW_POOL(*getDefaultMemoryPool()) DlfcnModule(module);
}