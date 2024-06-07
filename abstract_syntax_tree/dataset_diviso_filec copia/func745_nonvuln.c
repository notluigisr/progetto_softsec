static void cache_size(struct cacheinfo *this_leaf, struct device_node *np)
{
	const char *propname;
	int ct_idx;

	ct_idx = get_cacheinfo_idx(this_leaf->type);
	propname = cache_type_info[ct_idx].size_prop;

	of_property_read_u32(np, propname, &this_leaf->size);
}