static void hns_ppe_init_hw(struct hns_ppe_cb *ppe_cb)
{
	struct ppe_common_cb *ppe_common_cb = ppe_cb->ppe_common_cb;
	u32 port = ppe_cb->index;
	struct dsaf_device *dsaf_dev = ppe_common_cb->dsaf_dev;
	int i;

	
	netdev_rss_key_fill(ppe_cb->rss_key, HNS_PPEV2_RSS_KEY_SIZE);

	dsaf_dev->misc_op->ppe_srst(dsaf_dev, port, 0);
	mdelay(10);
	dsaf_dev->misc_op->ppe_srst(dsaf_dev, port, 1);

	
	hns_ppe_exc_irq_en(ppe_cb, 0);

	if (ppe_common_cb->ppe_mode == PPE_COMMON_MODE_DEBUG) {
		hns_ppe_set_port_mode(ppe_cb, PPE_MODE_GE);
		dsaf_write_dev(ppe_cb, PPE_CFG_PAUSE_IDLE_CNT_REG, 0);
	} else {
		hns_ppe_set_port_mode(ppe_cb, PPE_MODE_XGE);
	}

	hns_ppe_checksum_hw(ppe_cb, 0xffffffff);
	hns_ppe_cnt_clr_ce(ppe_cb);

	if (!AE_IS_VER1(dsaf_dev->dsaf_ver)) {
		hns_ppe_set_vlan_strip(ppe_cb, 0);

		dsaf_write_dev(ppe_cb, PPE_CFG_MAX_FRAME_LEN_REG,
			       HNS_PPEV2_MAX_FRAME_LEN);

		
		hns_ppe_set_rss_key(ppe_cb, ppe_cb->rss_key);

		
		for (i = 0; i < HNS_PPEV2_RSS_IND_TBL_SIZE; i++)
			ppe_cb->rss_indir_table[i] = i;
		hns_ppe_set_indir_table(ppe_cb, ppe_cb->rss_indir_table);
	}
}