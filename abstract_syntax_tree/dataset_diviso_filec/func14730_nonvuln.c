static void nci_set_config_req(struct nci_dev *ndev, const void *opt)
{
	const struct nci_set_config_param *param = opt;
	struct nci_core_set_config_cmd cmd;

	BUG_ON(param->len > NCI_MAX_PARAM_LEN);

	cmd.num_params = 1;
	cmd.param.id = param->id;
	cmd.param.len = param->len;
	memcpy(cmd.param.val, param->val, param->len);

	nci_send_cmd(ndev, NCI_OP_CORE_SET_CONFIG_CMD, (3 + param->len), &cmd);
}