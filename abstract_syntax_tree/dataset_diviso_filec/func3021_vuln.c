static int read_fragment_table(long long *directory_table_end)
{
	int res, i;
	int bytes = SQUASHFS_FRAGMENT_BYTES(sBlk.s.fragments);
	int  indexes = SQUASHFS_FRAGMENT_INDEXES(sBlk.s.fragments);
	long long fragment_table_index[indexes];

	TRACE("STR"
		"STR", sBlk.s.fragments, indexes,
		sBlk.s.fragment_table_start);

	if(sBlk.s.fragments == 0) {
		*directory_table_end = sBlk.s.fragment_table_start;
		return TRUE;
	}

	fragment_table = malloc(bytes);
	if(fragment_table == NULL)
		EXIT_UNSQUASH("STR"
			"STR");

	res = read_fs_bytes(fd, sBlk.s.fragment_table_start,
		SQUASHFS_FRAGMENT_INDEX_BYTES(sBlk.s.fragments),
		fragment_table_index);
	if(res == FALSE) {
		ERROR("STR"
			"STR");
		return FALSE;
	}
	SQUASHFS_INSWAP_FRAGMENT_INDEXES(fragment_table_index, indexes);

	for(i = 0; i < indexes; i++) {
		int expected = (i + 1) != indexes ? SQUASHFS_METADATA_SIZE :
					bytes & (SQUASHFS_METADATA_SIZE - 1);
		int length = read_block(fd, fragment_table_index[i], NULL,
			expected, ((char *) fragment_table) + (i *
			SQUASHFS_METADATA_SIZE));
		TRACE("STR",
			i, fragment_table_index[i], length);
		if(length == FALSE) {
			ERROR("STR"
				"STR");
			return FALSE;
		}
	}

	for(i = 0; i < sBlk.s.fragments; i++) 
		SQUASHFS_INSWAP_FRAGMENT_ENTRY(&fragment_table[i]);

	*directory_table_end = fragment_table_index[0];
	return TRUE;
}