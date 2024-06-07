static inline void hci_encrypt_cfm(struct hci_conn *conn, __u8 status,
								__u8 encrypt)
{
	struct hci_cb *cb;

	if (conn->sec_level == BT_SECURITY_SDP)
		conn->sec_level = BT_SECURITY_LOW;

	if (conn->pending_sec_level > conn->sec_level)
		conn->sec_level = conn->pending_sec_level;

	mutex_lock(&hci_cb_list_lock);
	list_for_each_entry(cb, &hci_cb_list, list) {
		if (cb->security_cfm)
			cb->security_cfm(conn, status, encrypt);
	}
	mutex_unlock(&hci_cb_list_lock);

	if (conn->security_cfm_cb)
		conn->security_cfm_cb(conn, status);
}