static int snd_mem_proc_read(char *page, char **start, off_t off,
			     int count, int *eof, void *data)
{
	int len = 0;
	long pages = snd_allocated_pages >> (PAGE_SHIFT-12);
	struct snd_mem_list *mem;
	int devno;
	static char *types[] = { "STR" };

	mutex_lock(&list_mutex);
	len += snprintf(page + len, count - len,
			"STR",
			pages * PAGE_SIZE, pages, PAGE_SIZE / 1024);
	devno = 0;
	list_for_each_entry(mem, &mem_list_head, list) {
		devno++;
		len += snprintf(page + len, count - len,
				"STR",
				devno, mem->id, types[mem->buffer.dev.type]);
		len += snprintf(page + len, count - len,
				"STR",
				(unsigned long)mem->buffer.addr, (int)mem->buffer.bytes);
	}
	mutex_unlock(&list_mutex);
	return len;
}