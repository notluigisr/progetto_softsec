int wvlan_uil_action(struct uilreq *urq, struct wl_private *lp)
{
	int     result = 0;
	ltv_t   *ltv;
	


	DBG_FUNC("STR");
	DBG_ENTER(DbgInfo);


	if (urq->hcfCtx == &(lp->hcfCtx)) {
		
		ltv = (ltv_t *)urq->data;
		if (ltv != NULL) {
			
			switch (ltv->typ) {
			case UIL_ACT_BLOCK:
				DBG_TRACE(DbgInfo, "STR");
				result = wvlan_uil_block(urq, lp);
				break;
			case UIL_ACT_UNBLOCK:
				DBG_TRACE(DbgInfo, "STR");
				result = wvlan_uil_unblock(urq, lp);
				break;
			case UIL_ACT_SCAN:
				DBG_TRACE(DbgInfo, "STR");
				urq->result = hcf_action(&(lp->hcfCtx), MDD_ACT_SCAN);
				break;
			case UIL_ACT_APPLY:
				DBG_TRACE(DbgInfo, "STR");
				urq->result = wl_apply(lp);
				break;
			case UIL_ACT_RESET:
				DBG_TRACE(DbgInfo, "STR");
				urq->result = wl_go(lp);
				break;
			default:
				DBG_WARNING(DbgInfo, "STR", ltv->typ);
				break;
			}
		} else {
			DBG_ERROR(DbgInfo, "STR");
			urq->result = UIL_ERR_LEN;
		}
	} else {
		DBG_ERROR(DbgInfo, "STR");
		urq->result = UIL_ERR_WRONG_IFB;
	}

	DBG_LEAVE(DbgInfo);
	return result;
} 