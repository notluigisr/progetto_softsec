static int i40e_fwd_ring_up(struct i40e_vsi *vsi, struct net_device *vdev,
			    struct i40e_fwd_adapter *fwd)
{
	int ret = 0, num_tc = 1,  i, aq_err;
	struct i40e_channel *ch, *ch_tmp;
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;

	if (list_empty(&vsi->macvlan_list))
		return -EINVAL;

	
	list_for_each_entry_safe(ch, ch_tmp, &vsi->macvlan_list, list) {
		if (!i40e_is_channel_macvlan(ch)) {
			ch->fwd = fwd;
			
			for (i = 0; i < num_tc; i++)
				netdev_bind_sb_channel_queue(vsi->netdev, vdev,
							     i,
							     ch->num_queue_pairs,
							     ch->base_queue);
			for (i = 0; i < ch->num_queue_pairs; i++) {
				struct i40e_ring *tx_ring, *rx_ring;
				u16 pf_q;

				pf_q = ch->base_queue + i;

				
				tx_ring = vsi->tx_rings[pf_q];
				tx_ring->ch = ch;

				
				rx_ring = vsi->rx_rings[pf_q];
				rx_ring->ch = ch;
			}
			break;
		}
	}

	
	wmb();

	
	ret = i40e_add_macvlan_filter(hw, ch->seid, vdev->dev_addr, &aq_err);
	if (ret) {
		
		macvlan_release_l2fw_offload(vdev);
		for (i = 0; i < ch->num_queue_pairs; i++) {
			struct i40e_ring *rx_ring;
			u16 pf_q;

			pf_q = ch->base_queue + i;
			rx_ring = vsi->rx_rings[pf_q];
			rx_ring->netdev = NULL;
		}
		dev_info(&pf->pdev->dev,
			 "STR",
			  i40e_stat_str(hw, ret),
			  i40e_aq_str(hw, aq_err));
		netdev_err(vdev, "STR");
	}

	return ret;
}