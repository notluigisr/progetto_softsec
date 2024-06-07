int security_xfrm_state_pol_flow_match(struct xfrm_state *x,
				       struct xfrm_policy *xp, struct flowi *fl)
{
	return security_ops->xfrm_state_pol_flow_match(x, xp, fl);
}