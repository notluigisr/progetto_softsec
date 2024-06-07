static void ieee80211_sta_conn_mon_timer(struct timer_list *t)
{
	struct ieee80211_sub_if_data *sdata =
		from_timer(sdata, t, u.mgd.conn_mon_timer);
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_local *local = sdata->local;

	if (sdata->vif.csa_active && !ifmgd->csa_waiting_bcn)
		return;

	ieee80211_queue_work(&local->hw, &ifmgd->monitor_work);
}