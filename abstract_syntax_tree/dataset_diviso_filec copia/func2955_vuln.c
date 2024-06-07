static void relocate_single_git_dir_into_superproject(const char *prefix,
						      const char *path)
{
	char *old_git_dir = NULL, *real_old_git_dir = NULL, *real_new_git_dir = NULL;
	const char *new_git_dir;
	const struct submodule *sub;

	if (submodule_uses_worktrees(path))
		die(_("STR"
		      "STR"), path);

	old_git_dir = xstrfmt("STR", path);
	if (read_gitfile(old_git_dir))
		
		return;

	real_old_git_dir = real_pathdup(old_git_dir, 1);

	sub = submodule_from_path(null_sha1, path);
	if (!sub)
		die(_("STR"), path);

	new_git_dir = git_path("STR", sub->name);
	if (safe_create_leading_directories_const(new_git_dir) < 0)
		die(_("STR"), new_git_dir);
	real_new_git_dir = real_pathdup(new_git_dir, 1);

	fprintf(stderr, _("STR"),
		get_super_prefix_or_empty(), path,
		real_old_git_dir, real_new_git_dir);

	relocate_gitdir(path, real_old_git_dir, real_new_git_dir);

	free(old_git_dir);
	free(real_old_git_dir);
	free(real_new_git_dir);
}