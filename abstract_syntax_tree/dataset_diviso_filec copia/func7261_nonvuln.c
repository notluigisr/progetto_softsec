static void hci_store_wake_reason(struct hci_dev *hdev, u8 event,
				  struct sk_buff *skb)
{
	struct hci_ev_le_advertising_info *adv;
	struct hci_ev_le_direct_adv_info *direct_adv;
	struct hci_ev_le_ext_adv_report *ext_adv;
	const struct hci_ev_conn_complete *conn_complete = (void *)skb->data;
	const struct hci_ev_conn_request *conn_request = (void *)skb->data;

	hci_dev_lock(hdev);

	
	if (!hdev->suspended || hdev->wake_reason)
		goto unlock;

	
	hdev->wake_reason = MGMT_WAKE_REASON_REMOTE_WAKE;

	
	if (event == HCI_EV_CONN_REQUEST) {
		bacpy(&hdev->wake_addr, &conn_complete->bdaddr);
		hdev->wake_addr_type = BDADDR_BREDR;
	} else if (event == HCI_EV_CONN_COMPLETE) {
		bacpy(&hdev->wake_addr, &conn_request->bdaddr);
		hdev->wake_addr_type = BDADDR_BREDR;
	} else if (event == HCI_EV_LE_META) {
		struct hci_ev_le_meta *le_ev = (void *)skb->data;
		u8 subevent = le_ev->subevent;
		u8 *ptr = &skb->data[sizeof(*le_ev)];
		u8 num_reports = *ptr;

		if ((subevent == HCI_EV_LE_ADVERTISING_REPORT ||
		     subevent == HCI_EV_LE_DIRECT_ADV_REPORT ||
		     subevent == HCI_EV_LE_EXT_ADV_REPORT) &&
		    num_reports) {
			adv = (void *)(ptr + 1);
			direct_adv = (void *)(ptr + 1);
			ext_adv = (void *)(ptr + 1);

			switch (subevent) {
			case HCI_EV_LE_ADVERTISING_REPORT:
				bacpy(&hdev->wake_addr, &adv->bdaddr);
				hdev->wake_addr_type = adv->bdaddr_type;
				break;
			case HCI_EV_LE_DIRECT_ADV_REPORT:
				bacpy(&hdev->wake_addr, &direct_adv->bdaddr);
				hdev->wake_addr_type = direct_adv->bdaddr_type;
				break;
			case HCI_EV_LE_EXT_ADV_REPORT:
				bacpy(&hdev->wake_addr, &ext_adv->bdaddr);
				hdev->wake_addr_type = ext_adv->bdaddr_type;
				break;
			}
		}
	} else {
		hdev->wake_reason = MGMT_WAKE_REASON_UNEXPECTED;
	}

unlock:
	hci_dev_unlock(hdev);
}