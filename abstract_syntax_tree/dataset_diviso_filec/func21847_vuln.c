static int read_uids_guids(long long *table_start)
{
	int res, i;
	int bytes = SQUASHFS_ID_BYTES(sBlk.s.no_ids);
	int indexes = SQUASHFS_ID_BLOCKS(sBlk.s.no_ids);
	long long id_index_table[indexes];

	TRACE("STR", sBlk.s.no_ids);

	id_table = malloc(bytes);
	if(id_table == NULL) {
		ERROR("STR");
		return FALSE;
	}

	res = read_fs_bytes(fd, sBlk.s.id_table_start,
		SQUASHFS_ID_BLOCK_BYTES(sBlk.s.no_ids), id_index_table);
	if(res == FALSE) {
		ERROR("STR");
		return FALSE;
	}
	SQUASHFS_INSWAP_ID_BLOCKS(id_index_table, indexes);

	
	*table_start = id_index_table[0];

	for(i = 0; i < indexes; i++) {
		int expected = (i + 1) != indexes ? SQUASHFS_METADATA_SIZE :
					bytes & (SQUASHFS_METADATA_SIZE - 1);
		res = read_block(fd, id_index_table[i], NULL, expected,
			((char *) id_table) + i * SQUASHFS_METADATA_SIZE);
		if(res == FALSE) {
			ERROR("STR"
				"STR");
			return FALSE;
		}
	}

	SQUASHFS_INSWAP_INTS(id_table, sBlk.s.no_ids);

	return TRUE;
}