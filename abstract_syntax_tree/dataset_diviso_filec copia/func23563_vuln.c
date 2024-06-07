static inline int compat_copy_match_to_user(struct ipt_entry_match *m,
		void __user **dstptr, compat_uint_t *size)
{
	if (m->u.kernel.match->compat)
		return m->u.kernel.match->compat(m, dstptr, size,
				COMPAT_TO_USER);
	else
		return xt_compat_match(m, dstptr, size, COMPAT_TO_USER);
}