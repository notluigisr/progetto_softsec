static void fuse_writepage_end(struct fuse_mount *fm, struct fuse_args *args,
			       int error)
{
	struct fuse_writepage_args *wpa =
		container_of(args, typeof(*wpa), ia.ap.args);
	struct inode *inode = wpa->inode;
	struct fuse_inode *fi = get_fuse_inode(inode);

	mapping_set_error(inode->i_mapping, error);
	spin_lock(&fi->lock);
	rb_erase(&wpa->writepages_entry, &fi->writepages);
	while (wpa->next) {
		struct fuse_mount *fm = get_fuse_mount(inode);
		struct fuse_write_in *inarg = &wpa->ia.write.in;
		struct fuse_writepage_args *next = wpa->next;

		wpa->next = next->next;
		next->next = NULL;
		next->ia.ff = fuse_file_get(wpa->ia.ff);
		tree_insert(&fi->writepages, next);

		
		fuse_send_writepage(fm, next, inarg->offset + inarg->size);
	}
	fi->writectr--;
	fuse_writepage_finish(fm, wpa);
	spin_unlock(&fi->lock);
	fuse_writepage_free(wpa);
}