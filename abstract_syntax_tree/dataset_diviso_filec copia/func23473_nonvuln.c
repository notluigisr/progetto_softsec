static void fpm_parent_resources_use(struct fpm_child_s *child) 
{
	fpm_stdio_parent_use_pipes(child);
	fpm_child_link(child);
}