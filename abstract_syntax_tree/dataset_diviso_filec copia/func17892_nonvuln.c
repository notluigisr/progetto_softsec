f_ch_canread(typval_T *argvars, typval_T *rettv)
{
    channel_T *channel = get_channel_arg(&argvars[0], FALSE, FALSE, 0);

    rettv->vval.v_number = 0;
    if (channel != NULL)
	rettv->vval.v_number = channel_has_readahead(channel, PART_SOCK)
			    || channel_has_readahead(channel, PART_OUT)
			    || channel_has_readahead(channel, PART_ERR);
}