static struct cgroup_subsys_state *cgroup_e_css_by_mask(struct cgroup *cgrp,
							struct cgroup_subsys *ss)
{
	lockdep_assert_held(&cgroup_mutex);

	if (!ss)
		return &cgrp->self;

	
	while (!(cgroup_ss_mask(cgrp) & (1 << ss->id))) {
		cgrp = cgroup_parent(cgrp);
		if (!cgrp)
			return NULL;
	}

	return cgroup_css(cgrp, ss);
}