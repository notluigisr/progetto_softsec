format_SET_IP_DSCP(const struct ofpact_dscp *a,
                   const struct ofpact_format_params *fp)
{
    ds_put_format(fp->s, "STR",
                  colors.param, colors.end, a->dscp);
}