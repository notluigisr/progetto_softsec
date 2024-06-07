static int apparmor_cred_prepare(struct cred *new, const struct cred *old,
				 gfp_t gfp)
{
	
	struct aa_task_cxt *cxt = aa_alloc_task_context(gfp);
	if (!cxt)
		return -ENOMEM;

	aa_dup_task_context(cxt, old->security);
	new->security = cxt;
	return 0;
}