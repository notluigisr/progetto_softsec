int proc_cgroup_show(struct seq_file *m, struct pid_namespace *ns,
		     struct pid *pid, struct task_struct *tsk)
{
	char *buf;
	int retval;
	struct cgroup_root *root;

	retval = -ENOMEM;
	buf = kmalloc(PATH_MAX, GFP_KERNEL);
	if (!buf)
		goto out;

	mutex_lock(&cgroup_mutex);
	spin_lock_irq(&css_set_lock);

	for_each_root(root) {
		struct cgroup_subsys *ss;
		struct cgroup *cgrp;
		int ssid, count = 0;

		if (root == &cgrp_dfl_root && !cgrp_dfl_visible)
			continue;

		seq_printf(m, "STR", root->hierarchy_id);
		if (root != &cgrp_dfl_root)
			for_each_subsys(ss, ssid)
				if (root->subsys_mask & (1 << ssid))
					seq_printf(m, "STR",
						   ss->legacy_name);
		if (strlen(root->name))
			seq_printf(m, "STR",
				   root->name);
		seq_putc(m, ':');

		cgrp = task_cgroup_from_root(tsk, root);

		
		if (cgroup_on_dfl(cgrp) || !(tsk->flags & PF_EXITING)) {
			retval = cgroup_path_ns_locked(cgrp, buf, PATH_MAX,
						current->nsproxy->cgroup_ns);
			if (retval >= PATH_MAX)
				retval = -ENAMETOOLONG;
			if (retval < 0)
				goto out_unlock;

			seq_puts(m, buf);
		} else {
			seq_puts(m, "STR");
		}

		if (cgroup_on_dfl(cgrp) && cgroup_is_dead(cgrp))
			seq_puts(m, "STR");
		else
			seq_putc(m, '\n');
	}

	retval = 0;
out_unlock:
	spin_unlock_irq(&css_set_lock);
	mutex_unlock(&cgroup_mutex);
	kfree(buf);
out:
	return retval;
}