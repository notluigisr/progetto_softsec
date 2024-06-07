static void new_conn_param(uint16_t index, uint16_t length,
					const void *param, void *user_data)
{
	const struct mgmt_ev_new_conn_param *ev = param;
	struct btd_adapter *adapter = user_data;
	uint16_t min, max, latency, timeout;
	struct btd_device *dev;
	char dst[18];


	if (length < sizeof(*ev)) {
		btd_error(adapter->dev_id,
				"STR");
		return;
	}

	ba2str(&ev->addr.bdaddr, dst);

	min = btohs(ev->min_interval);
	max = btohs(ev->max_interval);
	latency = btohs(ev->latency);
	timeout = btohs(ev->timeout);

	DBG("STR",
		adapter->dev_id, dst, ev->addr.type, min, max, latency, timeout);

	dev = btd_adapter_get_device(adapter, &ev->addr.bdaddr, ev->addr.type);
	if (!dev) {
		btd_error(adapter->dev_id,
				"STR", dst);
		return;
	}

	if (!ev->store_hint)
		return;

	store_conn_param(adapter, &ev->addr.bdaddr, ev->addr.type,
					ev->min_interval, ev->max_interval,
					ev->latency, ev->timeout);
}