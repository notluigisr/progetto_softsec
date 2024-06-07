static int xfrm_expand_policies(const struct flowi *fl, u16 family,
				struct xfrm_policy **pols,
				int *num_pols, int *num_xfrms)
{
	int i;

	if (*num_pols == 0 || !pols[0]) {
		*num_pols = 0;
		*num_xfrms = 0;
		return 0;
	}
	if (IS_ERR(pols[0]))
		return PTR_ERR(pols[0]);

	*num_xfrms = pols[0]->xfrm_nr;

#ifdef CONFIG_XFRM_SUB_POLICY
	if (pols[0]->action == XFRM_POLICY_ALLOW &&
	    pols[0]->type != XFRM_POLICY_TYPE_MAIN) {
		pols[1] = xfrm_policy_lookup_bytype(xp_net(pols[0]),
						    XFRM_POLICY_TYPE_MAIN,
						    fl, family,
						    XFRM_POLICY_OUT,
						    pols[0]->if_id);
		if (pols[1]) {
			if (IS_ERR(pols[1])) {
				xfrm_pols_put(pols, *num_pols);
				return PTR_ERR(pols[1]);
			}
			(*num_pols)++;
			(*num_xfrms) += pols[1]->xfrm_nr;
		}
	}
#endif
	for (i = 0; i < *num_pols; i++) {
		if (pols[i]->action != XFRM_POLICY_ALLOW) {
			*num_xfrms = -1;
			break;
		}
	}

	return 0;

}