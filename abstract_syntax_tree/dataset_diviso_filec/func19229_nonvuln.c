static void *get_match_data(int id)
{
	assert((size_t) id < ARRAY_SIZE(infos));
	return infos[id].match_data;
}