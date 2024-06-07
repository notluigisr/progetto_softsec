static int tc_fill_qdisc(struct sk_buff *skb, struct Qdisc *q, u32 clid,
			 u32 pid, u32 seq, u16 flags, int event)
{
	struct tcmsg *tcm;
	struct nlmsghdr  *nlh;
	unsigned char	 *b = skb->tail;
	struct gnet_dump d;

	nlh = NLMSG_NEW(skb, pid, seq, event, sizeof(*tcm), flags);
	tcm = NLMSG_DATA(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm_ifindex = q->dev->ifindex;
	tcm->tcm_parent = clid;
	tcm->tcm_handle = q->handle;
	tcm->tcm_info = atomic_read(&q->refcnt);
	RTA_PUT(skb, TCA_KIND, IFNAMSIZ, q->ops->id);
	if (q->ops->dump && q->ops->dump(q, skb) < 0)
		goto rtattr_failure;
	q->qstats.qlen = q->q.qlen;

	if (gnet_stats_start_copy_compat(skb, TCA_STATS2, TCA_STATS,
			TCA_XSTATS, q->stats_lock, &d) < 0)
		goto rtattr_failure;

	if (q->ops->dump_stats && q->ops->dump_stats(q, &d) < 0)
		goto rtattr_failure;

	if (gnet_stats_copy_basic(&d, &q->bstats) < 0 ||
#ifdef CONFIG_NET_ESTIMATOR
	    gnet_stats_copy_rate_est(&d, &q->rate_est) < 0 ||
#endif
	    gnet_stats_copy_queue(&d, &q->qstats) < 0)
		goto rtattr_failure;
	
	if (gnet_stats_finish_copy(&d) < 0)
		goto rtattr_failure;
	
	nlh->nlmsg_len = skb->tail - b;
	return skb->len;

nlmsg_failure:
rtattr_failure:
	skb_trim(skb, b - skb->data);
	return -1;
}