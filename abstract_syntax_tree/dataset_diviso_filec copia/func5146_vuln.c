int vc_allocate(unsigned int currcons)	
{
	struct vt_notifier_param param;
	struct vc_data *vc;

	WARN_CONSOLE_UNLOCKED();

	if (currcons >= MAX_NR_CONSOLES)
		return -ENXIO;

	if (vc_cons[currcons].d)
		return 0;

	
	
	
	param.vc = vc = kzalloc(sizeof(struct vc_data), GFP_KERNEL);
	if (!vc)
		return -ENOMEM;

	vc_cons[currcons].d = vc;
	tty_port_init(&vc->port);
	INIT_WORK(&vc_cons[currcons].SAK_work, vc_SAK);

	visual_init(vc, currcons, 1);

	if (!*vc->vc_uni_pagedir_loc)
		con_set_default_unimap(vc);

	vc->vc_screenbuf = kzalloc(vc->vc_screenbuf_size, GFP_KERNEL);
	if (!vc->vc_screenbuf)
		goto err_free;

	
	if (global_cursor_default == -1)
		global_cursor_default = 1;

	vc_init(vc, vc->vc_rows, vc->vc_cols, 1);
	vcs_make_sysfs(currcons);
	atomic_notifier_call_chain(&vt_notifier_list, VT_ALLOCATE, &param);

	return 0;
err_free:
	visual_deinit(vc);
	kfree(vc);
	vc_cons[currcons].d = NULL;
	return -ENOMEM;
}