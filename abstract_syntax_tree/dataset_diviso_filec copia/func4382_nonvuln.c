static int sta_prepare_rate_control(struct ieee80211_local *local,
				    struct sta_info *sta, gfp_t gfp)
{
	if (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL))
		return 0;

	sta->rate_ctrl = local->rate_ctrl;
	sta->rate_ctrl_priv = rate_control_alloc_sta(sta->rate_ctrl,
						     sta, gfp);
	if (!sta->rate_ctrl_priv)
		return -ENOMEM;

	return 0;
}