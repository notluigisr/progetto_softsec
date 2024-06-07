static int oneway_diff(struct cache_entry **src, struct unpack_trees_options *o)
{
	struct cache_entry *idx = src[0];
	struct cache_entry *tree = src[1];
	struct oneway_unpack_data *cbdata = o->unpack_data;
	struct rev_info *revs = cbdata->revs;

	if (idx && ce_stage(idx))
		skip_same_name(idx, o);

	
	if (tree == o->df_conflict_entry)
		tree = NULL;

	if (ce_path_match(idx ? idx : tree, revs->prune_data))
		do_oneway_diff(o, idx, tree);

	return 0;
}