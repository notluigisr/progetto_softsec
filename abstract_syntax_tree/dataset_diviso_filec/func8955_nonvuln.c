static int ieee80211_del_iface(struct wiphy *wiphy, struct wireless_dev *wdev)
{
	ieee80211_if_remove(IEEE80211_WDEV_TO_SUB_IF(wdev));

	return 0;
}