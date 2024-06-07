static void add_dirs_to_tree(int parent_ndx, struct file_list *from_flist,
			     int dir_cnt)
{
	int i;
	int32 *dp = NULL;
	int32 *parent_dp = parent_ndx < 0 ? NULL
			 : F_DIR_NODE_P(dir_flist->sorted[parent_ndx]);

	
	flist_expand(dir_flist, dir_cnt);
	dir_flist->sorted = dir_flist->files;

	for (i = 0; dir_cnt; i++) {
		struct file_struct *file = from_flist->sorted[i];

		if (!S_ISDIR(file->mode))
			continue;

		dir_flist->files[dir_flist->used++] = file;
		dir_cnt--;

		if (file->basename[0] == '.' && file->basename[1] == '\0')
			continue;

		if (dp)
			DIR_NEXT_SIBLING(dp) = dir_flist->used - 1;
		else if (parent_dp)
			DIR_FIRST_CHILD(parent_dp) = dir_flist->used - 1;
		else
			send_dir_ndx = dir_flist->used - 1;

		dp = F_DIR_NODE_P(file);
		DIR_PARENT(dp) = parent_ndx;
		DIR_FIRST_CHILD(dp) = -1;
	}
	if (dp)
		DIR_NEXT_SIBLING(dp) = -1;
}