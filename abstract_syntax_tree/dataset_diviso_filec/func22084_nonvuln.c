static int peer_close(struct t3cdev *tdev, struct sk_buff *skb, void *ctx)
{
	struct iwch_ep *ep = ctx;
	struct iwch_qp_attributes attrs;
	unsigned long flags;
	int disconnect = 1;
	int release = 0;

	PDBG("STR", __func__, ep);
	dst_confirm(ep->dst);

	spin_lock_irqsave(&ep->com.lock, flags);
	switch (ep->com.state) {
	case MPA_REQ_WAIT:
		__state_set(&ep->com, CLOSING);
		break;
	case MPA_REQ_SENT:
		__state_set(&ep->com, CLOSING);
		connect_reply_upcall(ep, -ECONNRESET);
		break;
	case MPA_REQ_RCVD:

		
		__state_set(&ep->com, CLOSING);
		ep->com.rpl_done = 1;
		ep->com.rpl_err = -ECONNRESET;
		PDBG("STR", ep);
		wake_up(&ep->com.waitq);
		break;
	case MPA_REP_SENT:
		__state_set(&ep->com, CLOSING);
		ep->com.rpl_done = 1;
		ep->com.rpl_err = -ECONNRESET;
		PDBG("STR", ep);
		wake_up(&ep->com.waitq);
		break;
	case FPDU_MODE:
		start_ep_timer(ep);
		__state_set(&ep->com, CLOSING);
		attrs.next_state = IWCH_QP_STATE_CLOSING;
		iwch_modify_qp(ep->com.qp->rhp, ep->com.qp,
			       IWCH_QP_ATTR_NEXT_STATE, &attrs, 1);
		peer_close_upcall(ep);
		break;
	case ABORTING:
		disconnect = 0;
		break;
	case CLOSING:
		__state_set(&ep->com, MORIBUND);
		disconnect = 0;
		break;
	case MORIBUND:
		stop_ep_timer(ep);
		if (ep->com.cm_id && ep->com.qp) {
			attrs.next_state = IWCH_QP_STATE_IDLE;
			iwch_modify_qp(ep->com.qp->rhp, ep->com.qp,
				       IWCH_QP_ATTR_NEXT_STATE, &attrs, 1);
		}
		close_complete_upcall(ep);
		__state_set(&ep->com, DEAD);
		release = 1;
		disconnect = 0;
		break;
	case DEAD:
		disconnect = 0;
		break;
	default:
		BUG_ON(1);
	}
	spin_unlock_irqrestore(&ep->com.lock, flags);
	if (disconnect)
		iwch_ep_disconnect(ep, 0, GFP_KERNEL);
	if (release)
		release_ep_resources(ep);
	return CPL_RET_BUF_DONE;
}