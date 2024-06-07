static int airo_get_freq(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_freq *fwrq,
			 char *extra)
{
	struct airo_info *local = dev->ml_priv;
	StatusRid status_rid;		
	int ch;

	readConfigRid(local, 1);
	if ((local->config.opmode & MODE_CFG_MASK) == MODE_STA_ESS)
		status_rid.channel = local->config.channelSet;
	else
		readStatusRid(local, &status_rid, 1);

	ch = le16_to_cpu(status_rid.channel);
	if((ch > 0) && (ch < 15)) {
		fwrq->m = ieee80211_dsss_chan_to_freq(ch) * 100000;
		fwrq->e = 1;
	} else {
		fwrq->m = ch;
		fwrq->e = 0;
	}

	return 0;
}