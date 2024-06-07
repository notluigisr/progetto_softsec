void sco_connect_cfm(struct hci_conn *hcon, __u8 status)
{
	BT_DBG("STR", hcon, &hcon->dst, status);
	if (!status) {
		struct sco_conn *conn;

		conn = sco_conn_add(hcon);
		if (conn)
			sco_conn_ready(conn);
	} else
		sco_conn_del(hcon, bt_to_errno(status));
}