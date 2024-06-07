void ieee80211_sta_ps_deliver_wakeup(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	struct sk_buff_head pending;
	int filtered = 0, buffered = 0, ac;
	unsigned long flags;

	clear_sta_flag(sta, WLAN_STA_SP);

	BUILD_BUG_ON(BITS_TO_LONGS(IEEE80211_NUM_TIDS) > 1);
	sta->driver_buffered_tids = 0;

	if (!(local->hw.flags & IEEE80211_HW_AP_LINK_PS))
		drv_sta_notify(local, sdata, STA_NOTIFY_AWAKE, &sta->sta);

	skb_queue_head_init(&pending);

	
	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		int count = skb_queue_len(&pending), tmp;

		spin_lock_irqsave(&sta->tx_filtered[ac].lock, flags);
		skb_queue_splice_tail_init(&sta->tx_filtered[ac], &pending);
		spin_unlock_irqrestore(&sta->tx_filtered[ac].lock, flags);
		tmp = skb_queue_len(&pending);
		filtered += tmp - count;
		count = tmp;

		spin_lock_irqsave(&sta->ps_tx_buf[ac].lock, flags);
		skb_queue_splice_tail_init(&sta->ps_tx_buf[ac], &pending);
		spin_unlock_irqrestore(&sta->ps_tx_buf[ac].lock, flags);
		tmp = skb_queue_len(&pending);
		buffered += tmp - count;
	}

	ieee80211_add_pending_skbs_fn(local, &pending, clear_sta_ps_flags, sta);

	
	if (!ieee80211_smps_is_restrictive(sta->known_smps_mode,
					   sdata->smps_mode) &&
	    sta->known_smps_mode != sdata->bss->req_smps &&
	    sta_info_tx_streams(sta) != 1) {
		ht_dbg(sdata,
		       "STR",
		       sta->sta.addr);
		ieee80211_send_smps_action(sdata, sdata->bss->req_smps,
					   sta->sta.addr,
					   sdata->vif.bss_conf.bssid);
	}

	local->total_ps_buffered -= buffered;

	sta_info_recalc_tim(sta);

	ps_dbg(sdata,
	       "STR",
	       sta->sta.addr, sta->sta.aid, filtered, buffered);
}