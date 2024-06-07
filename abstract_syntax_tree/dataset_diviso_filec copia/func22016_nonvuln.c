static struct pgpath *parse_path(struct dm_arg_set *as, struct path_selector *ps,
			       struct dm_target *ti)
{
	int r;
	struct pgpath *p;
	struct multipath *m = ti->private;

	
	if (as->argc < 1) {
		ti->error = "STR";
		return ERR_PTR(-EINVAL);
	}

	p = alloc_pgpath();
	if (!p)
		return ERR_PTR(-ENOMEM);

	r = dm_get_device(ti, dm_shift_arg(as), dm_table_get_mode(ti->table),
			  &p->path.dev);
	if (r) {
		ti->error = "STR";
		goto bad;
	}

	if (m->hw_handler_name) {
		struct request_queue *q = bdev_get_queue(p->path.dev->bdev);

		r = scsi_dh_attach(q, m->hw_handler_name);
		if (r == -EBUSY) {
			
			scsi_dh_detach(q);
			r = scsi_dh_attach(q, m->hw_handler_name);
		}

		if (r < 0) {
			ti->error = "STR";
			dm_put_device(ti, p->path.dev);
			goto bad;
		}

		if (m->hw_handler_params) {
			r = scsi_dh_set_params(q, m->hw_handler_params);
			if (r < 0) {
				ti->error = "STR"
							"STR";
				scsi_dh_detach(q);
				dm_put_device(ti, p->path.dev);
				goto bad;
			}
		}
	}

	r = ps->type->add_path(ps, &p->path, as->argc, as->argv, &ti->error);
	if (r) {
		dm_put_device(ti, p->path.dev);
		goto bad;
	}

	return p;

 bad:
	free_pgpath(p);
	return ERR_PTR(r);
}