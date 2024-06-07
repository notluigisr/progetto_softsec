static int ieee80211_set_ftm_responder_params(
				struct ieee80211_sub_if_data *sdata,
				const u8 *lci, size_t lci_len,
				const u8 *civicloc, size_t civicloc_len)
{
	struct ieee80211_ftm_responder_params *new, *old;
	struct ieee80211_bss_conf *bss_conf;
	u8 *pos;
	int len;

	if (!lci_len && !civicloc_len)
		return 0;

	bss_conf = &sdata->vif.bss_conf;
	old = bss_conf->ftmr_params;
	len = lci_len + civicloc_len;

	new = kzalloc(sizeof(*new) + len, GFP_KERNEL);
	if (!new)
		return -ENOMEM;

	pos = (u8 *)(new + 1);
	if (lci_len) {
		new->lci_len = lci_len;
		new->lci = pos;
		memcpy(pos, lci, lci_len);
		pos += lci_len;
	}

	if (civicloc_len) {
		new->civicloc_len = civicloc_len;
		new->civicloc = pos;
		memcpy(pos, civicloc, civicloc_len);
		pos += civicloc_len;
	}

	bss_conf->ftmr_params = new;
	kfree(old);

	return 0;
}