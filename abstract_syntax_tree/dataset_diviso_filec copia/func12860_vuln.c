videobuf_vm_open(struct vm_area_struct *vma)
{
	struct videobuf_mapping *map = vma->vm_private_data;

	dprintk(2,"STR",map,
		map->count,vma->vm_start,vma->vm_end);

	map->count++;
}