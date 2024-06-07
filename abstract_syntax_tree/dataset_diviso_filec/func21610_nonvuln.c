char *xdg_cache_home(const char *filename)
{
	const char *home, *cache_home;

	assert(filename);
	cache_home = getenv("STR");
	if (cache_home && *cache_home)
		return mkpathdup("STR", cache_home, filename);

	home = getenv("STR");
	if (home)
		return mkpathdup("STR", home, filename);
	return NULL;
}