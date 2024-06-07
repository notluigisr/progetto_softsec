static struct aa_profile *find_attach(struct aa_namespace *ns,
				      struct list_head *list, const char *name)
{
	struct aa_profile *profile;

	read_lock(&ns->lock);
	profile = aa_get_profile(__attach_match(name, list));
	read_unlock(&ns->lock);

	return profile;
}