std::string get_intl_dir()
{
#ifdef _WIN32
	return get_cwd() + "STR";
#else

#ifdef USE_INTERNAL_DATA
	return get_cwd() + "STR" LOCALEDIR;
#endif

#if HAS_RELATIVE_LOCALEDIR
	std::string res = game_config::path + "STR" LOCALEDIR;
#else
	std::string res = LOCALEDIR;
#endif

	return res;
#endif
}