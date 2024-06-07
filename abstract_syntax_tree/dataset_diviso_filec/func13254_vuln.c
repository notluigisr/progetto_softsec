static void read_enc_key_size_complete(struct hci_dev *hdev, u8 status,
				       u16 opcode, struct sk_buff *skb)
{
	const struct hci_rp_read_enc_key_size *rp;
	struct hci_conn *conn;
	u16 handle;

	BT_DBG("STR", hdev->name, status);

	if (!skb || skb->len < sizeof(*rp)) {
		bt_dev_err(hdev, "STR");
		return;
	}

	rp = (void *)skb->data;
	handle = le16_to_cpu(rp->handle);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, handle);
	if (!conn)
		goto unlock;

	
	if (rp->status) {
		bt_dev_err(hdev, "STR",
			   handle);
		conn->enc_key_size = 0;
	} else {
		conn->enc_key_size = rp->key_size;
	}

	if (conn->state == BT_CONFIG) {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, 0);
		hci_conn_drop(conn);
	} else {
		u8 encrypt;

		if (!test_bit(HCI_CONN_ENCRYPT, &conn->flags))
			encrypt = 0x00;
		else if (test_bit(HCI_CONN_AES_CCM, &conn->flags))
			encrypt = 0x02;
		else
			encrypt = 0x01;

		hci_encrypt_cfm(conn, 0, encrypt);
	}

unlock:
	hci_dev_unlock(hdev);
}