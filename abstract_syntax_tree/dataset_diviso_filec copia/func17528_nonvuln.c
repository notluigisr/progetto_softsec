static void set_match(int id, const char *match)
{
	assert((size_t) id < ARRAY_SIZE(infos));
	infos[id].match = match;
}