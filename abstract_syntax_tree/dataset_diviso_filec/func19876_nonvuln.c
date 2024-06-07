static int rc_table_update(struct qcow_state *s, unsigned int rc_index, uint64_t refblock_offset)
{
	ssize_t ret;

	tcmu_dbg("STR", __func__, rc_index, refblock_offset);
	s->refcount_table[rc_index] = htobe64(refblock_offset);

	ret = pwrite(s->fd,
		&s->refcount_table[rc_index],
		sizeof(uint64_t),
		s->refcount_table_offset + (rc_index * sizeof(uint64_t)));

	if (ret != sizeof(uint64_t))
		tcmu_err("STR", __func__, ret);

	fdatasync(s->fd);
	return ret;
}