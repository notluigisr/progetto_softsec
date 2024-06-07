static int ext4_feature_set_ok(struct super_block *sb, int readonly)
{
	if (ext4_has_unknown_ext4_incompat_features(sb)) {
		ext4_msg(sb, KERN_ERR,
			"STR"
			"STR",
			(le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_incompat) &
			~EXT4_FEATURE_INCOMPAT_SUPP));
		return 0;
	}

#ifndef CONFIG_UNICODE
	if (ext4_has_feature_casefold(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "STR"
			 "STR");
		return 0;
	}
#endif

	if (readonly)
		return 1;

	if (ext4_has_feature_readonly(sb)) {
		ext4_msg(sb, KERN_INFO, "STR");
		sb->s_flags |= SB_RDONLY;
		return 1;
	}

	
	if (ext4_has_unknown_ext4_ro_compat_features(sb)) {
		ext4_msg(sb, KERN_ERR, "STR"
			 "STR",
			 (le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_ro_compat) &
				~EXT4_FEATURE_RO_COMPAT_SUPP));
		return 0;
	}
	if (ext4_has_feature_bigalloc(sb) && !ext4_has_feature_extents(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "STR"
			 "STR");
		return 0;
	}

#ifndef CONFIG_QUOTA
	if (ext4_has_feature_quota(sb) && !readonly) {
		ext4_msg(sb, KERN_ERR,
			 "STR"
			 "STR");
		return 0;
	}
	if (ext4_has_feature_project(sb) && !readonly) {
		ext4_msg(sb, KERN_ERR,
			 "STR"
			 "STR");
		return 0;
	}
#endif  
	return 1;
}