static int ieee80211_join_mesh(struct wiphy *wiphy, struct net_device *dev,
			       const struct mesh_config *conf,
			       const struct mesh_setup *setup)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	int err;

	memcpy(&ifmsh->mshcfg, conf, sizeof(struct mesh_config));
	err = copy_mesh_setup(ifmsh, setup);
	if (err)
		return err;

	sdata->control_port_over_nl80211 = setup->control_port_over_nl80211;

	
	sdata->smps_mode = IEEE80211_SMPS_OFF;
	sdata->needed_rx_chains = sdata->local->rx_chains;

	mutex_lock(&sdata->local->mtx);
	err = ieee80211_vif_use_channel(sdata, &setup->chandef,
					IEEE80211_CHANCTX_SHARED);
	mutex_unlock(&sdata->local->mtx);
	if (err)
		return err;

	return ieee80211_start_mesh(sdata);
}