int hci_conn_check_link_mode(struct hci_conn *conn)
{
	BT_DBG("STR", conn);

	
	if (hci_dev_test_flag(conn->hdev, HCI_SC_ONLY)) {
		if (!hci_conn_sc_enabled(conn) ||
		    !test_bit(HCI_CONN_AES_CCM, &conn->flags) ||
		    conn->key_type != HCI_LK_AUTH_COMBINATION_P256)
			return 0;
	}

	if (hci_conn_ssp_enabled(conn) &&
	    !test_bit(HCI_CONN_ENCRYPT, &conn->flags))
		return 0;

	return 1;
}