static void protocol_timeout(struct k_work *work)
{
	if (!atomic_test_bit(link.flags, ADV_LINK_ACTIVE)) {
		return;
	}

	BT_DBG("");

	link.rx.seg = 0U;
	prov_link_close(PROV_BEARER_LINK_STATUS_TIMEOUT);
}