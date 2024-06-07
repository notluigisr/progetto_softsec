static int nl80211_update_owe_info(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct cfg80211_update_owe_info owe_info;
	struct net_device *dev = info->user_ptr[1];

	if (!rdev->ops->update_owe_info)
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_STATUS_CODE] ||
	    !info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	memset(&owe_info, 0, sizeof(owe_info));
	owe_info.status = nla_get_u16(info->attrs[NL80211_ATTR_STATUS_CODE]);
	nla_memcpy(owe_info.peer, info->attrs[NL80211_ATTR_MAC], ETH_ALEN);

	if (info->attrs[NL80211_ATTR_IE]) {
		owe_info.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		owe_info.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	}

	return rdev_update_owe_info(rdev, dev, &owe_info);
}