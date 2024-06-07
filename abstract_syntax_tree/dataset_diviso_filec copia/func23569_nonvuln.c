Bool gf_filter_is_supported_source(GF_Filter *filter, const char *url, const char *parent_url)
{
	GF_Err e;
	Bool is_supported = GF_FALSE;
	gf_fs_load_source_dest_internal(filter->session, url, NULL, parent_url, &e, NULL, filter, GF_TRUE, GF_TRUE, &is_supported);
	return is_supported;
}