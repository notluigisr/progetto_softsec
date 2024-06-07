static int nl80211_dump_station(struct sk_buff *skb,
				struct netlink_callback *cb)
{
	struct station_info sinfo;
	struct cfg80211_registered_device *rdev;
	struct wireless_dev *wdev;
	u8 mac_addr[ETH_ALEN];
	int sta_idx = cb->args[2];
	int err;

	rtnl_lock();
	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	if (err)
		goto out_err;

	if (!wdev->netdev) {
		err = -EINVAL;
		goto out_err;
	}

	if (!rdev->ops->dump_station) {
		err = -EOPNOTSUPP;
		goto out_err;
	}

	while (1) {
		memset(&sinfo, 0, sizeof(sinfo));
		err = rdev_dump_station(rdev, wdev->netdev, sta_idx,
					mac_addr, &sinfo);
		if (err == -ENOENT)
			break;
		if (err)
			goto out_err;

		if (nl80211_send_station(skb, NL80211_CMD_NEW_STATION,
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				rdev, wdev->netdev, mac_addr,
				&sinfo) < 0)
			goto out;

		sta_idx++;
	}

 out:
	cb->args[2] = sta_idx;
	err = skb->len;
 out_err:
	rtnl_unlock();

	return err;
}