static void brcmf_escan_timeout(unsigned long data)
{
	struct brcmf_cfg80211_info *cfg =
			(struct brcmf_cfg80211_info *)data;

	if (cfg->scan_request) {
		brcmf_err("STR");
		schedule_work(&cfg->escan_timeout_work);
	}
}