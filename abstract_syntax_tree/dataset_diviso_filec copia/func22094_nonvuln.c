static void accept_cr(struct iwch_ep *ep, __be32 peer_ip, struct sk_buff *skb)
{
	struct cpl_pass_accept_rpl *rpl;
	unsigned int mtu_idx;
	u32 opt0h, opt0l, opt2;
	int wscale;

	PDBG("STR", __func__, ep);
	BUG_ON(skb_cloned(skb));
	skb_trim(skb, sizeof(*rpl));
	skb_get(skb);
	mtu_idx = find_best_mtu(T3C_DATA(ep->com.tdev), dst_mtu(ep->dst));
	wscale = compute_wscale(rcv_win);
	opt0h = V_NAGLE(0) |
	    V_NO_CONG(nocong) |
	    V_KEEP_ALIVE(1) |
	    F_TCAM_BYPASS |
	    V_WND_SCALE(wscale) |
	    V_MSS_IDX(mtu_idx) |
	    V_L2T_IDX(ep->l2t->idx) | V_TX_CHANNEL(ep->l2t->smt_idx);
	opt0l = V_TOS((ep->tos >> 2) & M_TOS) | V_RCV_BUFSIZ(rcv_win>>10);
	opt2 = F_RX_COALESCE_VALID | V_RX_COALESCE(0) | V_FLAVORS_VALID(1) |
	       V_CONG_CONTROL_FLAVOR(cong_flavor);

	rpl = cplhdr(skb);
	rpl->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(rpl) = htonl(MK_OPCODE_TID(CPL_PASS_ACCEPT_RPL, ep->hwtid));
	rpl->peer_ip = peer_ip;
	rpl->opt0h = htonl(opt0h);
	rpl->opt0l_status = htonl(opt0l | CPL_PASS_OPEN_ACCEPT);
	rpl->opt2 = htonl(opt2);
	rpl->rsvd = rpl->opt2;	
	skb->priority = CPL_PRIORITY_SETUP;
	iwch_l2t_send(ep->com.tdev, skb, ep->l2t);

	return;
}