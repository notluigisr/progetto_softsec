static int i40e_queue_pair_toggle_rings(struct i40e_vsi *vsi, int queue_pair,
					bool enable)
{
	struct i40e_pf *pf = vsi->back;
	int pf_q, ret = 0;

	pf_q = vsi->base_queue + queue_pair;
	ret = i40e_control_wait_tx_q(vsi->seid, pf, pf_q,
				     false , enable);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "STR",
			 vsi->seid, pf_q, (enable ? "STR"));
		return ret;
	}

	i40e_control_rx_q(pf, pf_q, enable);
	ret = i40e_pf_rxq_wait(pf, pf_q, enable);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "STR",
			 vsi->seid, pf_q, (enable ? "STR"));
		return ret;
	}

	
	if (!enable)
		mdelay(50);

	if (!i40e_enabled_xdp_vsi(vsi))
		return ret;

	ret = i40e_control_wait_tx_q(vsi->seid, pf,
				     pf_q + vsi->alloc_queue_pairs,
				     true , enable);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "STR",
			 vsi->seid, pf_q, (enable ? "STR"));
	}

	return ret;
}