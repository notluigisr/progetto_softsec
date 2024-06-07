format_CONJUNCTION(const struct ofpact_conjunction *oc,
                   const struct ofpact_format_params *fp)
{
    ds_put_format(fp->s, "STR",
                  colors.paren, colors.end,
                  oc->id, oc->clause + 1, oc->n_clauses,
                  colors.paren, colors.end);
}