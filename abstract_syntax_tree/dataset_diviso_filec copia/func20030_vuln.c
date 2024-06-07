int __scm_send(struct socket *sock, struct msghdr *msg, struct scm_cookie *p)
{
	struct cmsghdr *cmsg;
	int err;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg))
	{
		err = -EINVAL;

		
		
		if (!CMSG_OK(msg, cmsg))
			goto error;

		if (cmsg->cmsg_level != SOL_SOCKET)
			continue;

		switch (cmsg->cmsg_type)
		{
		case SCM_RIGHTS:
			if (!sock->ops || sock->ops->family != PF_UNIX)
				goto error;
			err=scm_fp_copy(cmsg, &p->fp);
			if (err<0)
				goto error;
			break;
		case SCM_CREDENTIALS:
			if (cmsg->cmsg_len != CMSG_LEN(sizeof(struct ucred)))
				goto error;
			memcpy(&p->creds, CMSG_DATA(cmsg), sizeof(struct ucred));
			err = scm_check_creds(&p->creds);
			if (err)
				goto error;

			if (pid_vnr(p->pid) != p->creds.pid) {
				struct pid *pid;
				err = -ESRCH;
				pid = find_get_pid(p->creds.pid);
				if (!pid)
					goto error;
				put_pid(p->pid);
				p->pid = pid;
			}

			if ((p->cred->euid != p->creds.uid) ||
				(p->cred->egid != p->creds.gid)) {
				struct cred *cred;
				err = -ENOMEM;
				cred = prepare_creds();
				if (!cred)
					goto error;

				cred->uid = cred->euid = p->creds.uid;
				cred->gid = cred->egid = p->creds.gid;
				put_cred(p->cred);
				p->cred = cred;
			}
			break;
		default:
			goto error;
		}
	}

	if (p->fp && !p->fp->count)
	{
		kfree(p->fp);
		p->fp = NULL;
	}
	return 0;

error:
	scm_destroy(p);
	return err;
}