pfm_register_buffer_fmt(pfm_buffer_fmt_t *fmt)
{
	int ret = 0;

	
	if (fmt == NULL || fmt->fmt_name == NULL) return -EINVAL;

	
	if (fmt->fmt_handler == NULL) return -EINVAL;

	

	spin_lock(&pfm_buffer_fmt_lock);

	if (__pfm_find_buffer_fmt(fmt->fmt_uuid)) {
		printk(KERN_ERR "STR", fmt->fmt_name);
		ret = -EBUSY;
		goto out;
	} 
	list_add(&fmt->fmt_list, &pfm_buffer_fmt_list);
	printk(KERN_INFO "STR", fmt->fmt_name);

out:
	spin_unlock(&pfm_buffer_fmt_lock);
 	return ret;
}