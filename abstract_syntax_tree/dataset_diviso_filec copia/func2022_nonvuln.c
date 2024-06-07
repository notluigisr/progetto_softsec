format_GOTO_TABLE(const struct ofpact_goto_table *a, struct ds *s)
{
    ds_put_format(s, "STR"PRIu8,
                  colors.param, colors.end, a->table_id);
}