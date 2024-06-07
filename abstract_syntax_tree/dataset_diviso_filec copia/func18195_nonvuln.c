static RCmdDesc *create_cmd_desc(RCmd *cmd, RCmdDesc *parent, RCmdDescType type, const char *name, const RCmdDescHelp *help, bool ht_insert) {
	RCmdDesc *res = R_NEW0 (RCmdDesc);
	if (!res) {
		return NULL;
	}
	res->type = type;
	res->name = strdup (name);
	if (!res->name) {
		goto err;
	}
	res->n_children = 0;
	res->help = help? help: &not_defined_help;
	r_pvector_init (&res->children, (RPVectorFree)cmd_desc_free);
	if (ht_insert && !ht_pp_insert (cmd->ht_cmds, name, res)) {
		goto err;
	}
	cmd_desc_set_parent (res, parent);
	return res;
err:
	cmd_desc_free (res);
	return NULL;
}