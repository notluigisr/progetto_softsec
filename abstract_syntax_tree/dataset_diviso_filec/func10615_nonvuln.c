int hci_conn_check_secure(struct hci_conn *conn, __u8 sec_level)
{
	BT_DBG("STR", conn);

	
	if (sec_level != BT_SECURITY_HIGH && sec_level != BT_SECURITY_FIPS)
		return 1;

	
	if (conn->sec_level == BT_SECURITY_HIGH ||
	    conn->sec_level == BT_SECURITY_FIPS)
		return 1;

	
	return 0;
}