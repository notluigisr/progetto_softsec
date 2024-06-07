static void sta_ps_end(struct sta_info *sta)
{
	ps_dbg(sta->sdata, "STR",
	       sta->sta.addr, sta->sta.aid);

	if (test_sta_flag(sta, WLAN_STA_PS_DRIVER)) {
		
		clear_sta_flag(sta, WLAN_STA_PS_STA);
		ps_dbg(sta->sdata, "STR",
		       sta->sta.addr, sta->sta.aid);
		return;
	}

	set_sta_flag(sta, WLAN_STA_PS_DELIVER);
	clear_sta_flag(sta, WLAN_STA_PS_STA);
	ieee80211_sta_ps_deliver_wakeup(sta);
}