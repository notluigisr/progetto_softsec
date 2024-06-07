static int sta_info_insert_check(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;

	
	if (unlikely(!ieee80211_sdata_running(sdata)))
		return -ENETDOWN;

	if (WARN_ON(ether_addr_equal(sta->sta.addr, sdata->vif.addr) ||
		    is_multicast_ether_addr(sta->sta.addr)))
		return -EINVAL;

	
	rcu_read_lock();
	lockdep_assert_held(&sdata->local->sta_mtx);
	if (ieee80211_hw_check(&sdata->local->hw, NEEDS_UNIQUE_STA_ADDR) &&
	    ieee80211_find_sta_by_ifaddr(&sdata->local->hw, sta->addr, NULL)) {
		rcu_read_unlock();
		return -ENOTUNIQ;
	}
	rcu_read_unlock();

	return 0;
}