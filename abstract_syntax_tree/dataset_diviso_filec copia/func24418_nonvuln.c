static int nl80211_update_connect_params(struct sk_buff *skb,
					 struct genl_info *info)
{
	struct cfg80211_connect_params connect = {};
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	bool fils_sk_offload;
	u32 auth_type;
	u32 changed = 0;
	int ret;

	if (!rdev->ops->update_connect_params)
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_IE]) {
		connect.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		connect.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
		changed |= UPDATE_ASSOC_IES;
	}

	fils_sk_offload = wiphy_ext_feature_isset(&rdev->wiphy,
						  NL80211_EXT_FEATURE_FILS_SK_OFFLOAD);

	
	if (fils_sk_offload &&
	    info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_REALM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_RRK]) {
		connect.fils_erp_username =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_username_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_realm =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_realm_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_next_seq_num =
			nla_get_u16(
			   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM]);
		connect.fils_erp_rrk =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		connect.fils_erp_rrk_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		changed |= UPDATE_FILS_ERP_INFO;
	} else if (info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_REALM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_RRK]) {
		return -EINVAL;
	}

	if (info->attrs[NL80211_ATTR_AUTH_TYPE]) {
		auth_type = nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
		if (!nl80211_valid_auth_type(rdev, auth_type,
					     NL80211_CMD_CONNECT))
			return -EINVAL;

		if (auth_type == NL80211_AUTHTYPE_FILS_SK &&
		    fils_sk_offload && !(changed & UPDATE_FILS_ERP_INFO))
			return -EINVAL;

		connect.auth_type = auth_type;
		changed |= UPDATE_AUTH_TYPE;
	}

	wdev_lock(dev->ieee80211_ptr);
	if (!wdev->current_bss)
		ret = -ENOLINK;
	else
		ret = rdev_update_connect_params(rdev, dev, &connect, changed);
	wdev_unlock(dev->ieee80211_ptr);

	return ret;
}