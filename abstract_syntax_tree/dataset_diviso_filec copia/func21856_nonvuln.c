static void process_cached_repolist(const char *path)
{
	struct stat st;
	struct strbuf cached_rc = STRBUF_INIT;
	time_t age;
	unsigned long hash;

	hash = hash_str(path);
	if (ctx.cfg.project_list)
		hash += hash_str(ctx.cfg.project_list);
	strbuf_addf(&cached_rc, "STR", ctx.cfg.cache_root, hash);

	if (stat(cached_rc.buf, &st)) {
		
		if (generate_cached_repolist(path, cached_rc.buf)) {
			if (ctx.cfg.project_list)
				scan_projects(path, ctx.cfg.project_list,
					      repo_config);
			else
				scan_tree(path, repo_config);
		}
		goto out;
	}

	parse_configfile(cached_rc.buf, config_cb);

	
	age = time(NULL) - st.st_mtime;
	if (age <= (ctx.cfg.cache_scanrc_ttl * 60))
		goto out;

	
	if (fork())
		goto out;

	exit(generate_cached_repolist(path, cached_rc.buf));
out:
	strbuf_release(&cached_rc);
}