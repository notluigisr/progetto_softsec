free_config_access(
	config_tree *ptree
	)
{
	FREE_ATTR_VAL_FIFO(ptree->mru_opts);
	FREE_ATTR_VAL_FIFO(ptree->discard_opts);
	FREE_RESTRICT_FIFO(ptree->restrict_opts);
}