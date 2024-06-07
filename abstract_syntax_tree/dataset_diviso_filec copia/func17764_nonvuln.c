static void xfrm_state_look_at(struct xfrm_policy *pol, struct xfrm_state *x,
			       const struct flowi *fl, unsigned short family,
			       struct xfrm_state **best, int *acq_in_progress,
			       int *error)
{
	
	if (x->km.state == XFRM_STATE_VALID) {
		if ((x->sel.family &&
		     !xfrm_selector_match(&x->sel, fl, x->sel.family)) ||
		    !security_xfrm_state_pol_flow_match(x, pol, fl))
			return;

		if (!*best ||
		    (*best)->km.dying > x->km.dying ||
		    ((*best)->km.dying == x->km.dying &&
		     (*best)->curlft.add_time < x->curlft.add_time))
			*best = x;
	} else if (x->km.state == XFRM_STATE_ACQ) {
		*acq_in_progress = 1;
	} else if (x->km.state == XFRM_STATE_ERROR ||
		   x->km.state == XFRM_STATE_EXPIRED) {
		if (xfrm_selector_match(&x->sel, fl, x->sel.family) &&
		    security_xfrm_state_pol_flow_match(x, pol, fl))
			*error = -ESRCH;
	}
}