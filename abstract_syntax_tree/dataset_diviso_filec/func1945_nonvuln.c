#ifdef CONFIG_PROC_FS
static __cold int io_uring_show_cred(struct seq_file *m, unsigned int id,
		const struct cred *cred)
{
	struct user_namespace *uns = seq_user_ns(m);
	struct group_info *gi;
	kernel_cap_t cap;
	unsigned __capi;
	int g;

	seq_printf(m, "STR", id);
	seq_put_decimal_ull(m, "STR", from_kuid_munged(uns, cred->uid));
	seq_put_decimal_ull(m, "STR", from_kuid_munged(uns, cred->euid));
	seq_put_decimal_ull(m, "STR", from_kuid_munged(uns, cred->suid));
	seq_put_decimal_ull(m, "STR", from_kuid_munged(uns, cred->fsuid));
	seq_put_decimal_ull(m, "STR", from_kgid_munged(uns, cred->gid));
	seq_put_decimal_ull(m, "STR", from_kgid_munged(uns, cred->egid));
	seq_put_decimal_ull(m, "STR", from_kgid_munged(uns, cred->sgid));
	seq_put_decimal_ull(m, "STR", from_kgid_munged(uns, cred->fsgid));
	seq_puts(m, "STR");
	gi = cred->group_info;
	for (g = 0; g < gi->ngroups; g++) {
		seq_put_decimal_ull(m, g ? "STR",
					from_kgid_munged(uns, gi->gid[g]));
	}
	seq_puts(m, "STR");
	cap = cred->cap_effective;
	CAP_FOR_EACH_U32(__capi)
		seq_put_hex_ll(m, NULL, cap.cap[CAP_LAST_U32 - __capi], 8);
	seq_putc(m, '\n');
	return 0;