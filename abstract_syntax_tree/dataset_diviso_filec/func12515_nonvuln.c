const char *gf_filter_get_id(GF_Filter *filter)
{
	if (filter) return filter->id;
	return NULL;
}