ieee80211_sta_abort_chanswitch(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;

	if (!local->ops->abort_channel_switch)
		return;

	mutex_lock(&local->mtx);

	mutex_lock(&local->chanctx_mtx);
	ieee80211_vif_unreserve_chanctx(sdata);
	mutex_unlock(&local->chanctx_mtx);

	if (sdata->csa_block_tx)
		ieee80211_wake_vif_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);

	sdata->csa_block_tx = false;
	sdata->vif.csa_active = false;

	mutex_unlock(&local->mtx);

	drv_abort_channel_switch(sdata);
}