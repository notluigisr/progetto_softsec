static void vma_commit_reservation(struct hstate *h,
			struct vm_area_struct *vma, unsigned long addr)
{
	struct address_space *mapping = vma->vm_file->f_mapping;
	struct inode *inode = mapping->host;

	if (vma->vm_flags & VM_MAYSHARE) {
		pgoff_t idx = vma_hugecache_offset(h, vma, addr);
		region_add(&inode->i_mapping->private_list, idx, idx + 1);

	} else if (is_vma_resv_set(vma, HPAGE_RESV_OWNER)) {
		pgoff_t idx = vma_hugecache_offset(h, vma, addr);
		struct resv_map *reservations = vma_resv_map(vma);

		
		region_add(&reservations->regions, idx, idx + 1);
	}
}