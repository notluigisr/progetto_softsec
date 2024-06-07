static void free_filter(filter_rule *ex)
{
	if (ex->rflags & FILTRULE_PERDIR_MERGE)
		teardown_mergelist(ex);
	free(ex->pattern);
	free(ex);
}