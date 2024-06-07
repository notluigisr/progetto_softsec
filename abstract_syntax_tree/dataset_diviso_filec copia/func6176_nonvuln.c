static void agent_auth_cb(struct agent *agent, DBusError *derr,
							void *user_data)
{
	struct btd_adapter *adapter = user_data;
	struct service_auth *auth = g_queue_pop_head(adapter->auths);

	if (!auth) {
		DBG("STR");
		return;
	}

	auth->cb(derr, auth->user_data);

	if (auth->agent)
		agent_unref(auth->agent);

	g_free(auth);

	
	if (g_queue_is_empty(adapter->auths)) {
		if (adapter->auth_idle_id > 0)
			g_source_remove(adapter->auth_idle_id);
		return;
	}

	if (adapter->auth_idle_id > 0)
		return;

	adapter->auth_idle_id = g_idle_add(process_auth_queue, adapter);
}