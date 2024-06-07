static int io_queue_file_removal(struct fixed_file_data *data,
				 struct file *file)
{
	struct io_file_put *pfile;
	struct percpu_ref *refs = data->cur_refs;
	struct fixed_file_ref_node *ref_node;

	pfile = kzalloc(sizeof(*pfile), GFP_KERNEL);
	if (!pfile)
		return -ENOMEM;

	ref_node = container_of(refs, struct fixed_file_ref_node, refs);
	pfile->file = file;
	list_add(&pfile->list, &ref_node->file_list);

	return 0;
}