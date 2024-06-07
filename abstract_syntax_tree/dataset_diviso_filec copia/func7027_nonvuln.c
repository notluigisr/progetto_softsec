static int set_qf_name(struct super_block *sb, int qtype, substring_t *args)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	char *qname, *old_qname = get_qf_name(sb, sbi, qtype);
	int ret = -1;

	if (sb_any_quota_loaded(sb) && !old_qname) {
		ext4_msg(sb, KERN_ERR,
			"STR"
			"STR");
		return -1;
	}
	if (ext4_has_feature_quota(sb)) {
		ext4_msg(sb, KERN_INFO, "STR"
			 "STR");
		return 1;
	}
	qname = match_strdup(args);
	if (!qname) {
		ext4_msg(sb, KERN_ERR,
			"STR");
		return -1;
	}
	if (old_qname) {
		if (strcmp(old_qname, qname) == 0)
			ret = 1;
		else
			ext4_msg(sb, KERN_ERR,
				 "STR",
				 QTYPE2NAME(qtype));
		goto errout;
	}
	if (strchr(qname, '/')) {
		ext4_msg(sb, KERN_ERR,
			"STR");
		goto errout;
	}
	rcu_assign_pointer(sbi->s_qf_names[qtype], qname);
	set_opt(sb, QUOTA);
	return 1;
errout:
	kfree(qname);
	return ret;
}