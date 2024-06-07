static void hci_disconn_loglink_complete_evt(struct hci_dev *hdev,
					     struct sk_buff *skb)
{
	struct hci_ev_disconn_logical_link_complete *ev = (void *) skb->data;
	struct hci_chan *hchan;

	BT_DBG("STR", hdev->name,
	       le16_to_cpu(ev->handle), ev->status);

	if (ev->status)
		return;

	hci_dev_lock(hdev);

	hchan = hci_chan_lookup_handle(hdev, le16_to_cpu(ev->handle));
	if (!hchan)
		goto unlock;

	amp_destroy_logical_link(hchan, ev->reason);

unlock:
	hci_dev_unlock(hdev);
}