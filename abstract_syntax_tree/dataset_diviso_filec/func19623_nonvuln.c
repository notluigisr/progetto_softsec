static int nci_activate_target(struct nfc_dev *nfc_dev,
			       struct nfc_target *target, __u32 protocol)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	struct nci_rf_discover_select_param param;
	const struct nfc_target *nci_target = NULL;
	int i;
	int rc = 0;

	pr_debug("STR", target->idx, protocol);

	if ((atomic_read(&ndev->state) != NCI_W4_HOST_SELECT) &&
	    (atomic_read(&ndev->state) != NCI_POLL_ACTIVE)) {
		pr_err("STR");
		return -EINVAL;
	}

	if (ndev->target_active_prot) {
		pr_err("STR");
		return -EBUSY;
	}

	for (i = 0; i < ndev->n_targets; i++) {
		if (ndev->targets[i].idx == target->idx) {
			nci_target = &ndev->targets[i];
			break;
		}
	}

	if (!nci_target) {
		pr_err("STR");
		return -EINVAL;
	}

	if (!(nci_target->supported_protocols & (1 << protocol))) {
		pr_err("STR",
		       protocol);
		return -EINVAL;
	}

	if (atomic_read(&ndev->state) == NCI_W4_HOST_SELECT) {
		param.rf_discovery_id = nci_target->logical_idx;

		if (protocol == NFC_PROTO_JEWEL)
			param.rf_protocol = NCI_RF_PROTOCOL_T1T;
		else if (protocol == NFC_PROTO_MIFARE)
			param.rf_protocol = NCI_RF_PROTOCOL_T2T;
		else if (protocol == NFC_PROTO_FELICA)
			param.rf_protocol = NCI_RF_PROTOCOL_T3T;
		else if (protocol == NFC_PROTO_ISO14443 ||
			 protocol == NFC_PROTO_ISO14443_B)
			param.rf_protocol = NCI_RF_PROTOCOL_ISO_DEP;
		else
			param.rf_protocol = NCI_RF_PROTOCOL_NFC_DEP;

		rc = nci_request(ndev, nci_rf_discover_select_req, &param,
				 msecs_to_jiffies(NCI_RF_DISC_SELECT_TIMEOUT));
	}

	if (!rc)
		ndev->target_active_prot = protocol;

	return rc;
}