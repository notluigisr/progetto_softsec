static int update_discovery_filter(struct btd_adapter *adapter)
{
	struct mgmt_cp_start_service_discovery *sd_cp;
	GSList *l;


	DBG("");

	if (discovery_filter_to_mgmt_cp(adapter, &sd_cp)) {
		btd_error(adapter->dev_id,
				"STR");
		return -ENOMEM;
	}

	for (l = adapter->discovery_list; l; l = g_slist_next(l)) {
		struct discovery_client *client = l->data;

		if (!client->discovery_filter)
			continue;

		if (client->discovery_filter->discoverable)
			break;
	}

	set_discovery_discoverable(adapter, l ? true : false);

	
	if (filters_equal(adapter->current_discovery_filter, sd_cp) &&
	    adapter->discovering != 0) {
		DBG("STR");
		g_free(sd_cp);
		return 0;
	}

	g_free(adapter->current_discovery_filter);
	adapter->current_discovery_filter = sd_cp;

	trigger_start_discovery(adapter, 0);

	return -EINPROGRESS;
}