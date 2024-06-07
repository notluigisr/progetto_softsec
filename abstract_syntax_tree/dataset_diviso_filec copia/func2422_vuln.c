static __inline__ void scm_set_cred(struct scm_cookie *scm,
				    struct pid *pid, const struct cred *cred)
{
	scm->pid  = get_pid(pid);
	scm->cred = get_cred(cred);
	cred_to_ucred(pid, cred, &scm->creds);
}