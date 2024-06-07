smb2_dump_share_caps(struct seq_file *m, struct cifs_tcon *tcon)
{
	seq_puts(m, "STR");
	if (tcon->capabilities & SMB2_SHARE_CAP_DFS)
		seq_puts(m, "STR");
	if (tcon->capabilities & SMB2_SHARE_CAP_CONTINUOUS_AVAILABILITY)
		seq_puts(m, "STR");
	if (tcon->capabilities & SMB2_SHARE_CAP_SCALEOUT)
		seq_puts(m, "STR");
	if (tcon->capabilities & SMB2_SHARE_CAP_CLUSTER)
		seq_puts(m, "STR");
	if (tcon->capabilities & SMB2_SHARE_CAP_ASYMMETRIC)
		seq_puts(m, "STR");
	if (tcon->capabilities == 0)
		seq_puts(m, "STR");
	if (tcon->ss_flags & SSINFO_FLAGS_ALIGNED_DEVICE)
		seq_puts(m, "STR");
	if (tcon->ss_flags & SSINFO_FLAGS_PARTITION_ALIGNED_ON_DEVICE)
		seq_puts(m, "STR");
	if (tcon->ss_flags & SSINFO_FLAGS_NO_SEEK_PENALTY)
		seq_puts(m, "STR");
	if (tcon->ss_flags & SSINFO_FLAGS_TRIM_ENABLED)
		seq_puts(m, "STR");

	seq_printf(m, "STR", tcon->share_flags);
	seq_printf(m, "STR", tcon->tid);
	if (tcon->perf_sector_size)
		seq_printf(m, "STR",
			   tcon->perf_sector_size);
	seq_printf(m, "STR", tcon->maximal_access);
}