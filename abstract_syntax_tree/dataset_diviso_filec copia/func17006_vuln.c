int wvlan_set_station_nickname(struct net_device *dev,
		      struct iw_request_info *info,
		      union iwreq_data *wrqu,
		      char *extra)
{
	struct wl_private *lp = wl_priv(dev);
	unsigned long flags;
	int         ret = 0;
	


	DBG_FUNC("STR");
	DBG_ENTER(DbgInfo);

	wl_lock(lp, &flags);

	memset(lp->StationName, 0, sizeof(lp->StationName));

	memcpy(lp->StationName, extra, wrqu->data.length);

	
	wl_apply(lp);
	wl_unlock(lp, &flags);

	DBG_LEAVE(DbgInfo);
	return ret;
} 