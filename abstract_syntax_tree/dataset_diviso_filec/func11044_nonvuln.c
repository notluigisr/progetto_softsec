int git_pkt_buffer_have(git_oid *oid, git_buf *buf)
{
	char oidhex[GIT_OID_HEXSZ + 1];

	memset(oidhex, 0x0, sizeof(oidhex));
	git_oid_fmt(oidhex, oid);
	return git_buf_printf(buf, "STR", pkt_have_prefix, oidhex);
}