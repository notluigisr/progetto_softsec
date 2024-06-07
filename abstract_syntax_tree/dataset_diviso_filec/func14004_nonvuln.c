static struct sk_buff *cfg80211_prepare_cqm(struct net_device *dev,
					    const char *mac, gfp_t gfp)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct sk_buff *msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	void **cb;

	if (!msg)
		return NULL;

	cb = (void **)msg->cb;

	cb[0] = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_NOTIFY_CQM);
	if (!cb[0]) {
		nlmsg_free(msg);
		return NULL;
	}

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex))
		goto nla_put_failure;

	if (mac && nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac))
		goto nla_put_failure;

	cb[1] = nla_nest_start_noflag(msg, NL80211_ATTR_CQM);
	if (!cb[1])
		goto nla_put_failure;

	cb[2] = rdev;

	return msg;
 nla_put_failure:
	nlmsg_free(msg);
	return NULL;
}