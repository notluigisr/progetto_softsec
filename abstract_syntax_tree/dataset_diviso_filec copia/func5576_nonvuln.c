static void fq_flow_reset(struct fq *fq,
			  struct fq_flow *flow,
			  fq_skb_free_t free_func)
{
	struct sk_buff *skb;

	while ((skb = fq_flow_dequeue(fq, flow)))
		free_func(fq, flow->tin, flow, skb);

	if (!list_empty(&flow->flowchain))
		list_del_init(&flow->flowchain);

	if (!list_empty(&flow->backlogchain))
		list_del_init(&flow->backlogchain);

	flow->tin = NULL;

	WARN_ON_ONCE(flow->backlog);
}