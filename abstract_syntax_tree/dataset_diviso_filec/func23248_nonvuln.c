static int smk_curacc_on_task(struct task_struct *p, int access)
{
	struct smk_audit_info ad;

	smk_ad_init(&ad, __func__, LSM_AUDIT_DATA_TASK);
	smk_ad_setfield_u_tsk(&ad, p);
	return smk_curacc(task_security(p), access, &ad);
}