static int ath6kl_wmi_pstream_timeout_event_rx(struct wmi *wmi, u8 *datap,
					       int len)
{
	struct wmi_pstream_timeout_event *ev;

	if (len < sizeof(struct wmi_pstream_timeout_event))
		return -EINVAL;

	ev = (struct wmi_pstream_timeout_event *) datap;

	
	spin_lock_bh(&wmi->lock);
	wmi->stream_exist_for_ac[ev->traffic_class] = 0;
	wmi->fat_pipe_exist &= ~(1 << ev->traffic_class);
	spin_unlock_bh(&wmi->lock);

	
	ath6kl_indicate_tx_activity(wmi->parent_dev, ev->traffic_class, false);

	return 0;
}