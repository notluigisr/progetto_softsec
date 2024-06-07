struct se_portal_group *tcm_loop_make_naa_tpg(
	struct se_wwn *wwn,
	struct config_group *group,
	const char *name)
{
	struct tcm_loop_hba *tl_hba = container_of(wwn,
			struct tcm_loop_hba, tl_hba_wwn);
	struct tcm_loop_tpg *tl_tpg;
	char *tpgt_str, *end_ptr;
	int ret;
	unsigned short int tpgt;

	tpgt_str = strstr(name, "STR");
	if (!tpgt_str) {
		printk(KERN_ERR "STR"
				"STR");
		return ERR_PTR(-EINVAL);
	}
	tpgt_str += 5; 
	tpgt = (unsigned short int) simple_strtoul(tpgt_str, &end_ptr, 0);

	if (tpgt > TL_TPGS_PER_HBA) {
		printk(KERN_ERR "STR"
				"STR", tpgt, TL_TPGS_PER_HBA);
		return ERR_PTR(-EINVAL);
	}
	tl_tpg = &tl_hba->tl_hba_tpgs[tpgt];
	tl_tpg->tl_hba = tl_hba;
	tl_tpg->tl_tpgt = tpgt;
	
	ret = core_tpg_register(&tcm_loop_fabric_configfs->tf_ops,
			wwn, &tl_tpg->tl_se_tpg, tl_tpg,
			TRANSPORT_TPG_TYPE_NORMAL);
	if (ret < 0)
		return ERR_PTR(-ENOMEM);

	printk(KERN_INFO "STR"
		"STR", tcm_loop_dump_proto_id(tl_hba),
		config_item_name(&wwn->wwn_group.cg_item), tpgt);

	return &tl_tpg->tl_se_tpg;
}