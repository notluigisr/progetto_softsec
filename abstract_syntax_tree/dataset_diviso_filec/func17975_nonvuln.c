GF_Err gf_filter_set_configure_ckb(GF_Filter *filter, GF_Err (*configure_cbk)(GF_Filter *filter, GF_FilterPid *PID, Bool is_remove) )
{
	if (! (filter->freg->flags & GF_FS_REG_CUSTOM)) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_FILTER, ("STR", filter->freg->name));
		return GF_BAD_PARAM;
	}
	((GF_FilterRegister *) filter->freg)->configure_pid = configure_cbk;
	return GF_OK;
}