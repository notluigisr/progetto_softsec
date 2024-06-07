static int __must_check ax25_rt_add(struct ax25_routes_struct *route)
{
	ax25_route *ax25_rt;
	ax25_dev *ax25_dev;
	int i;

	if ((ax25_dev = ax25_addr_ax25dev(&route->port_addr)) == NULL)
		return -EINVAL;
	if (route->digi_count > AX25_MAX_DIGIS)
		return -EINVAL;

	write_lock_bh(&ax25_route_lock);

	ax25_rt = ax25_route_list;
	while (ax25_rt != NULL) {
		if (ax25cmp(&ax25_rt->callsign, &route->dest_addr) == 0 &&
			    ax25_rt->dev == ax25_dev->dev) {
			kfree(ax25_rt->digipeat);
			ax25_rt->digipeat = NULL;
			if (route->digi_count != 0) {
				if ((ax25_rt->digipeat = kmalloc(sizeof(ax25_digi), GFP_ATOMIC)) == NULL) {
					write_unlock_bh(&ax25_route_lock);
					return -ENOMEM;
				}
				ax25_rt->digipeat->lastrepeat = -1;
				ax25_rt->digipeat->ndigi      = route->digi_count;
				for (i = 0; i < route->digi_count; i++) {
					ax25_rt->digipeat->repeated[i] = 0;
					ax25_rt->digipeat->calls[i]    = route->digi_addr[i];
				}
			}
			write_unlock_bh(&ax25_route_lock);
			return 0;
		}
		ax25_rt = ax25_rt->next;
	}

	if ((ax25_rt = kmalloc(sizeof(ax25_route), GFP_ATOMIC)) == NULL) {
		write_unlock_bh(&ax25_route_lock);
		return -ENOMEM;
	}

	refcount_set(&ax25_rt->refcount, 1);
	ax25_rt->callsign     = route->dest_addr;
	ax25_rt->dev          = ax25_dev->dev;
	ax25_rt->digipeat     = NULL;
	ax25_rt->ip_mode      = ' ';
	ax25_dev_put(ax25_dev);
	if (route->digi_count != 0) {
		if ((ax25_rt->digipeat = kmalloc(sizeof(ax25_digi), GFP_ATOMIC)) == NULL) {
			write_unlock_bh(&ax25_route_lock);
			kfree(ax25_rt);
			return -ENOMEM;
		}
		ax25_rt->digipeat->lastrepeat = -1;
		ax25_rt->digipeat->ndigi      = route->digi_count;
		for (i = 0; i < route->digi_count; i++) {
			ax25_rt->digipeat->repeated[i] = 0;
			ax25_rt->digipeat->calls[i]    = route->digi_addr[i];
		}
	}
	ax25_rt->next   = ax25_route_list;
	ax25_route_list = ax25_rt;
	write_unlock_bh(&ax25_route_lock);

	return 0;
}