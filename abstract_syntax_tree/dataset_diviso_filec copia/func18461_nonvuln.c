static void i40e_watchdog_subtask(struct i40e_pf *pf)
{
	int i;

	
	if (test_bit(__I40E_DOWN, pf->state) ||
	    test_bit(__I40E_CONFIG_BUSY, pf->state))
		return;

	
	if (time_before(jiffies, (pf->service_timer_previous +
				  pf->service_timer_period)))
		return;
	pf->service_timer_previous = jiffies;

	if ((pf->flags & I40E_FLAG_LINK_POLLING_ENABLED) ||
	    test_bit(__I40E_TEMP_LINK_POLLING, pf->state))
		i40e_link_event(pf);

	
	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i] && pf->vsi[i]->netdev)
			i40e_update_stats(pf->vsi[i]);

	if (pf->flags & I40E_FLAG_VEB_STATS_ENABLED) {
		
		for (i = 0; i < I40E_MAX_VEB; i++)
			if (pf->veb[i])
				i40e_update_veb_stats(pf->veb[i]);
	}

	i40e_ptp_rx_hang(pf);
	i40e_ptp_tx_hang(pf);
}