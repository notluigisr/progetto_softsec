static void free_refmatch_inner(struct refmatch *info)
{
	if (info->first_ref)
		free(info->first_ref);
}