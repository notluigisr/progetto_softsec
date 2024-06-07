static int snd_mem_proc_read(struct seq_file *seq, void *offset)
{
	long pages = snd_allocated_pages >> (PAGE_SHIFT-12);
	struct snd_mem_list *mem;
	int devno;
	static char *types[] = { "STR" };

	mutex_lock(&list_mutex);
	seq_printf(seq, "STR",
		   pages * PAGE_SIZE, pages, PAGE_SIZE / 1024);
	devno = 0;
	list_for_each_entry(mem, &mem_list_head, list) {
		devno++;
		seq_printf(seq, "STR",
			   devno, mem->id, types[mem->buffer.dev.type]);
		seq_printf(seq, "STR",
			   (unsigned long)mem->buffer.addr,
			   (int)mem->buffer.bytes);
	}
	mutex_unlock(&list_mutex);
	return 0;
}