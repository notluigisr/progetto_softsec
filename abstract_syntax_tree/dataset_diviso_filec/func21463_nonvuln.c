guint btd_request_authorization_cable_configured(const bdaddr_t *src, const bdaddr_t *dst,
						const char *uuid, service_auth_cb cb,
						void *user_data)
{
	struct btd_adapter *adapter;

	if (bacmp(src, BDADDR_ANY) == 0)
		return 0;

	adapter = adapter_find(src);
	if (!adapter)
		return 0;

	return adapter_authorize(adapter, dst, uuid,
			ADAPTER_AUTHORIZE_DISCONNECTED, cb, user_data);
}