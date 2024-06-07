static int nl80211_testmode_dump(struct sk_buff *skb,
				 struct netlink_callback *cb)
{
	struct cfg80211_registered_device *rdev;
	struct nlattr **attrbuf = NULL;
	int err;
	long phy_idx;
	void *data = NULL;
	int data_len = 0;

	rtnl_lock();

	if (cb->args[0]) {
		
		phy_idx = cb->args[0] - 1;

		rdev = cfg80211_rdev_by_wiphy_idx(phy_idx);
		if (!rdev) {
			err = -ENOENT;
			goto out_err;
		}
	} else {
		attrbuf = kcalloc(NUM_NL80211_ATTR, sizeof(*attrbuf),
				  GFP_KERNEL);
		if (!attrbuf) {
			err = -ENOMEM;
			goto out_err;
		}

		err = nlmsg_parse_deprecated(cb->nlh,
					     GENL_HDRLEN + nl80211_fam.hdrsize,
					     attrbuf, nl80211_fam.maxattr,
					     nl80211_policy, NULL);
		if (err)
			goto out_err;

		rdev = __cfg80211_rdev_from_attrs(sock_net(skb->sk), attrbuf);
		if (IS_ERR(rdev)) {
			err = PTR_ERR(rdev);
			goto out_err;
		}
		phy_idx = rdev->wiphy_idx;

		if (attrbuf[NL80211_ATTR_TESTDATA])
			cb->args[1] = (long)attrbuf[NL80211_ATTR_TESTDATA];
	}

	if (cb->args[1]) {
		data = nla_data((void *)cb->args[1]);
		data_len = nla_len((void *)cb->args[1]);
	}

	if (!rdev->ops->testmode_dump) {
		err = -EOPNOTSUPP;
		goto out_err;
	}

	while (1) {
		void *hdr = nl80211hdr_put(skb, NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   NL80211_CMD_TESTMODE);
		struct nlattr *tmdata;

		if (!hdr)
			break;

		if (nla_put_u32(skb, NL80211_ATTR_WIPHY, phy_idx)) {
			genlmsg_cancel(skb, hdr);
			break;
		}

		tmdata = nla_nest_start_noflag(skb, NL80211_ATTR_TESTDATA);
		if (!tmdata) {
			genlmsg_cancel(skb, hdr);
			break;
		}
		err = rdev_testmode_dump(rdev, skb, cb, data, data_len);
		nla_nest_end(skb, tmdata);

		if (err == -ENOBUFS || err == -ENOENT) {
			genlmsg_cancel(skb, hdr);
			break;
		} else if (err) {
			genlmsg_cancel(skb, hdr);
			goto out_err;
		}

		genlmsg_end(skb, hdr);
	}

	err = skb->len;
	
	cb->args[0] = phy_idx + 1;
 out_err:
	kfree(attrbuf);
	rtnl_unlock();
	return err;
}