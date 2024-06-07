static void __srpt_close_ch(struct srpt_rdma_ch *ch)
{
	enum rdma_ch_state prev_state;
	unsigned long flags;

	spin_lock_irqsave(&ch->spinlock, flags);
	prev_state = ch->state;
	switch (prev_state) {
	case CH_CONNECTING:
	case CH_LIVE:
		ch->state = CH_DISCONNECTING;
		break;
	default:
		break;
	}
	spin_unlock_irqrestore(&ch->spinlock, flags);

	switch (prev_state) {
	case CH_CONNECTING:
		ib_send_cm_rej(ch->cm_id, IB_CM_REJ_NO_RESOURCES, NULL, 0,
			       NULL, 0);
		
	case CH_LIVE:
		if (ib_send_cm_dreq(ch->cm_id, NULL, 0) < 0)
			pr_err("STR");
		break;
	case CH_DISCONNECTING:
		break;
	case CH_DRAINING:
	case CH_RELEASING:
		break;
	}
}