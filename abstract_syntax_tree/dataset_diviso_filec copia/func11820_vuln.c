static int sfq_change(struct Qdisc *sch, struct nlattr *opt)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	struct tc_sfq_qopt *ctl = nla_data(opt);
	struct tc_sfq_qopt_v1 *ctl_v1 = NULL;
	unsigned int qlen, dropped = 0;
	struct red_parms *p = NULL;
	struct sk_buff *to_free = NULL;
	struct sk_buff *tail = NULL;

	if (opt->nla_len < nla_attr_size(sizeof(*ctl)))
		return -EINVAL;
	if (opt->nla_len >= nla_attr_size(sizeof(*ctl_v1)))
		ctl_v1 = nla_data(opt);
	if (ctl->divisor &&
	    (!is_power_of_2(ctl->divisor) || ctl->divisor > 65536))
		return -EINVAL;
	if (ctl_v1 && !red_check_params(ctl_v1->qth_min, ctl_v1->qth_max,
					ctl_v1->Wlog))
		return -EINVAL;
	if (ctl_v1 && ctl_v1->qth_min) {
		p = kmalloc(sizeof(*p), GFP_KERNEL);
		if (!p)
			return -ENOMEM;
	}
	sch_tree_lock(sch);
	if (ctl->quantum) {
		q->quantum = ctl->quantum;
		q->scaled_quantum = SFQ_ALLOT_SIZE(q->quantum);
	}
	q->perturb_period = ctl->perturb_period * HZ;
	if (ctl->flows)
		q->maxflows = min_t(u32, ctl->flows, SFQ_MAX_FLOWS);
	if (ctl->divisor) {
		q->divisor = ctl->divisor;
		q->maxflows = min_t(u32, q->maxflows, q->divisor);
	}
	if (ctl_v1) {
		if (ctl_v1->depth)
			q->maxdepth = min_t(u32, ctl_v1->depth, SFQ_MAX_DEPTH);
		if (p) {
			swap(q->red_parms, p);
			red_set_parms(q->red_parms,
				      ctl_v1->qth_min, ctl_v1->qth_max,
				      ctl_v1->Wlog,
				      ctl_v1->Plog, ctl_v1->Scell_log,
				      NULL,
				      ctl_v1->max_P);
		}
		q->flags = ctl_v1->flags;
		q->headdrop = ctl_v1->headdrop;
	}
	if (ctl->limit) {
		q->limit = min_t(u32, ctl->limit, q->maxdepth * q->maxflows);
		q->maxflows = min_t(u32, q->maxflows, q->limit);
	}

	qlen = sch->q.qlen;
	while (sch->q.qlen > q->limit) {
		dropped += sfq_drop(sch, &to_free);
		if (!tail)
			tail = to_free;
	}

	rtnl_kfree_skbs(to_free, tail);
	qdisc_tree_reduce_backlog(sch, qlen - sch->q.qlen, dropped);

	del_timer(&q->perturb_timer);
	if (q->perturb_period) {
		mod_timer(&q->perturb_timer, jiffies + q->perturb_period);
		q->perturbation = prandom_u32();
	}
	sch_tree_unlock(sch);
	kfree(p);
	return 0;
}