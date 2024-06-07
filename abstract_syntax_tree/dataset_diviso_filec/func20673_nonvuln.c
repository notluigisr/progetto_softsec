static void ath6kl_wmi_relinquish_implicit_pstream_credits(struct wmi *wmi)
{
	u16 active_tsids;
	u8 stream_exist;
	int i;

	
	spin_lock_bh(&wmi->lock);
	stream_exist = wmi->fat_pipe_exist;
	spin_unlock_bh(&wmi->lock);

	for (i = 0; i < WMM_NUM_AC; i++) {
		if (stream_exist & (1 << i)) {
			
			spin_lock_bh(&wmi->lock);
			active_tsids = wmi->stream_exist_for_ac[i];
			spin_unlock_bh(&wmi->lock);

			
			if (!active_tsids) {
				stream_exist &= ~(1 << i);
				
				ath6kl_indicate_tx_activity(wmi->parent_dev,
							    i, false);
			}
		}
	}

	
	spin_lock_bh(&wmi->lock);
	wmi->fat_pipe_exist = stream_exist;
	spin_unlock_bh(&wmi->lock);
}