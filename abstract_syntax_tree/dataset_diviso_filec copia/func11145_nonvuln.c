static void fq_rejigger_backlog(struct fq *fq, struct fq_flow *flow)
{
	struct fq_flow *i;

	if (flow->backlog == 0) {
		list_del_init(&flow->backlogchain);
	} else {
		i = flow;

		list_for_each_entry_continue(i, &fq->backlogs, backlogchain)
			if (i->backlog < flow->backlog)
				break;

		list_move_tail(&flow->backlogchain,
			       &i->backlogchain);
	}
}