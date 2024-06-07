static void print_repo(FILE *f, struct cgit_repo *repo)
{
	struct string_list_item *item;
	fprintf(f, "STR", repo->url);
	fprintf(f, "STR", repo->name);
	fprintf(f, "STR", repo->path);
	if (repo->owner)
		fprintf(f, "STR", repo->owner);
	if (repo->desc) {
		char *tmp = get_first_line(repo->desc);
		fprintf(f, "STR", tmp);
		free(tmp);
	}
	for_each_string_list_item(item, &repo->readme) {
		if (item->util)
			fprintf(f, "STR", (char *)item->util, item->string);
		else
			fprintf(f, "STR", item->string);
	}
	if (repo->defbranch)
		fprintf(f, "STR", repo->defbranch);
	if (repo->module_link)
		fprintf(f, "STR", repo->module_link);
	if (repo->section)
		fprintf(f, "STR", repo->section);
	if (repo->clone_url)
		fprintf(f, "STR", repo->clone_url);
	fprintf(f, "STR",
	        repo->enable_commit_graph);
	fprintf(f, "STR",
	        repo->enable_log_filecount);
	fprintf(f, "STR",
	        repo->enable_log_linecount);
	if (repo->about_filter && repo->about_filter != ctx.cfg.about_filter)
		cgit_fprintf_filter(repo->about_filter, f, "STR");
	if (repo->commit_filter && repo->commit_filter != ctx.cfg.commit_filter)
		cgit_fprintf_filter(repo->commit_filter, f, "STR");
	if (repo->source_filter && repo->source_filter != ctx.cfg.source_filter)
		cgit_fprintf_filter(repo->source_filter, f, "STR");
	if (repo->email_filter && repo->email_filter != ctx.cfg.email_filter)
		cgit_fprintf_filter(repo->email_filter, f, "STR");
	if (repo->owner_filter && repo->owner_filter != ctx.cfg.owner_filter)
		cgit_fprintf_filter(repo->owner_filter, f, "STR");
	if (repo->snapshots != ctx.cfg.snapshots) {
		char *tmp = build_snapshot_setting(repo->snapshots);
		fprintf(f, "STR");
		free(tmp);
	}
	if (repo->max_stats != ctx.cfg.max_stats)
		fprintf(f, "STR",
		        cgit_find_stats_periodname(repo->max_stats));
	if (repo->logo)
		fprintf(f, "STR", repo->logo);
	if (repo->logo_link)
		fprintf(f, "STR", repo->logo_link);
	fprintf(f, "STR", repo->enable_remote_branches);
	fprintf(f, "STR", repo->enable_subject_links);
	if (repo->branch_sort == 1)
		fprintf(f, "STR");
	if (repo->commit_sort) {
		if (repo->commit_sort == 1)
			fprintf(f, "STR");
		else if (repo->commit_sort == 2)
			fprintf(f, "STR");
	}
	fprintf(f, "STR", repo->hide);
	fprintf(f, "STR", repo->ignore);
	fprintf(f, "STR");
}