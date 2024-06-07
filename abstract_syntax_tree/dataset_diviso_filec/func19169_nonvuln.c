static s32 brcmf_inform_bss(struct brcmf_cfg80211_info *cfg)
{
	struct wiphy *wiphy = cfg_to_wiphy(cfg);
	struct brcmf_scan_results *bss_list;
	struct brcmf_bss_info_le *bi = NULL;	
	s32 err = 0;
	int i;

	bss_list = (struct brcmf_scan_results *)cfg->escan_info.escan_buf;
	if (bss_list->count != 0 &&
	    bss_list->version != BRCMF_BSS_INFO_VERSION) {
		bphy_err(wiphy, "STR",
			 bss_list->version);
		return -EOPNOTSUPP;
	}
	brcmf_dbg(SCAN, "STR", bss_list->count);
	for (i = 0; i < bss_list->count; i++) {
		bi = next_bss_le(bss_list, bi);
		err = brcmf_inform_single_bss(cfg, bi);
		if (err)
			break;
	}
	return err;
}