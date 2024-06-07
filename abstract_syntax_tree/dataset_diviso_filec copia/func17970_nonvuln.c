static void fq_tin_enqueue(struct fq *fq,
			   struct fq_tin *tin, u32 idx,
			   struct sk_buff *skb,
			   fq_skb_free_t free_func,
			   fq_flow_get_default_t get_default_func)
{
	struct fq_flow *flow;
	bool oom;

	lockdep_assert_held(&fq->lock);

	flow = fq_flow_classify(fq, tin, idx, skb, get_default_func);

	flow->tin = tin;
	flow->backlog += skb->len;
	tin->backlog_bytes += skb->len;
	tin->backlog_packets++;
	fq->memory_usage += skb->truesize;
	fq->backlog++;

	fq_recalc_backlog(fq, tin, flow);

	if (list_empty(&flow->flowchain)) {
		flow->deficit = fq->quantum;
		list_add_tail(&flow->flowchain,
			      &tin->new_flows);
	}

	__skb_queue_tail(&flow->queue, skb);
	oom = (fq->memory_usage > fq->memory_limit);
	while (fq->backlog > fq->limit || oom) {
		flow = list_first_entry_or_null(&fq->backlogs,
						struct fq_flow,
						backlogchain);
		if (!flow)
			return;

		skb = fq_flow_dequeue(fq, flow);
		if (!skb)
			return;

		free_func(fq, flow->tin, flow, skb);

		flow->tin->overlimit++;
		fq->overlimit++;
		if (oom) {
			fq->overmemory++;
			oom = (fq->memory_usage > fq->memory_limit);
		}
	}
}