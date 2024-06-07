static inline void eventpoll_init_file(struct file *file)
{
	INIT_LIST_HEAD(&file->f_ep_links);
}