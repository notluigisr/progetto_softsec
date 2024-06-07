static int ipc_has_perm(struct kern_ipc_perm *ipc_perms,
			u32 perms)
{
	struct ipc_security_struct *isec;
	struct common_audit_data ad;
	struct selinux_audit_data sad = {0,};
	u32 sid = current_sid();

	isec = ipc_perms->security;

	COMMON_AUDIT_DATA_INIT(&ad, IPC);
	ad.selinux_audit_data = &sad;
	ad.u.ipc_id = ipc_perms->key;

	return avc_has_perm(sid, isec->sid, isec->sclass, perms, &ad);
}