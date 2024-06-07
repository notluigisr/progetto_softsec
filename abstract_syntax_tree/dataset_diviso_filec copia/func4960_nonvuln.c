
static int io_register_pbuf_ring(struct io_ring_ctx *ctx, void __user *arg)
{
	struct io_uring_buf_ring *br;
	struct io_uring_buf_reg reg;
	struct io_buffer_list *bl;
	struct page **pages;
	int nr_pages;

	if (copy_from_user(&reg, arg, sizeof(reg)))
		return -EFAULT;

	if (reg.pad || reg.resv[0] || reg.resv[1] || reg.resv[2])
		return -EINVAL;
	if (!reg.ring_addr)
		return -EFAULT;
	if (reg.ring_addr & ~PAGE_MASK)
		return -EINVAL;
	if (!is_power_of_2(reg.ring_entries))
		return -EINVAL;

	if (unlikely(reg.bgid < BGID_ARRAY && !ctx->io_bl)) {
		int ret = io_init_bl_list(ctx);
		if (ret)
			return ret;
	}

	bl = io_buffer_get_list(ctx, reg.bgid);
	if (bl) {
		
		if (bl->buf_nr_pages || !list_empty(&bl->buf_list))
			return -EEXIST;
	} else {
		bl = kzalloc(sizeof(*bl), GFP_KERNEL);
		if (!bl)
			return -ENOMEM;
	}

	pages = io_pin_pages(reg.ring_addr,
			     struct_size(br, bufs, reg.ring_entries),
			     &nr_pages);
	if (IS_ERR(pages)) {
		kfree(bl);
		return PTR_ERR(pages);
	}

	br = page_address(pages[0]);
	bl->buf_pages = pages;
	bl->buf_nr_pages = nr_pages;
	bl->nr_entries = reg.ring_entries;
	bl->buf_ring = br;
	bl->mask = reg.ring_entries - 1;
	io_buffer_add_list(ctx, bl, reg.bgid);
	return 0;