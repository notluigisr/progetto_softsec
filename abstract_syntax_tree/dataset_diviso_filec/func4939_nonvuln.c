void show_submodule_summary(FILE *f, const char *path,
		const char *line_prefix,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset)
{
	struct rev_info rev;
	struct commit *left = NULL, *right = NULL;
	struct commit_list *merge_bases = NULL;

	show_submodule_header(f, path, line_prefix, one, two, dirty_submodule,
			      meta, reset, &left, &right, &merge_bases);

	
	if (!left || !right)
		goto out;

	
	if (prepare_submodule_summary(&rev, path, left, right, merge_bases)) {
		fprintf(f, "STR", line_prefix);
		goto out;
	}

	print_submodule_summary(&rev, f, line_prefix, del, add, reset);

out:
	if (merge_bases)
		free_commit_list(merge_bases);
	clear_commit_marks(left, ~0);
	clear_commit_marks(right, ~0);
}