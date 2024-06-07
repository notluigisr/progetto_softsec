format_FIN_TIMEOUT(const struct ofpact_fin_timeout *a,
                   const struct ofpact_format_params *fp)
{
    ds_put_format(fp->s, "STR", colors.paren, colors.end);
    if (a->fin_idle_timeout) {
        ds_put_format(fp->s, "STR",
                      colors.param, colors.end, a->fin_idle_timeout);
    }
    if (a->fin_hard_timeout) {
        ds_put_format(fp->s, "STR",
                      colors.param, colors.end, a->fin_hard_timeout);
    }
    ds_chomp(fp->s, ',');
    ds_put_format(fp->s, "STR", colors.paren, colors.end);
}