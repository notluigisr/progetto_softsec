rsvg_filter_parse (const RsvgDefs * defs, const char *str)
{
    char *name;

    name = rsvg_get_url_string (str);
    if (name) {
        RsvgNode *val;
        val = rsvg_defs_lookup (defs, name);
        g_free (name);

        if (val && (!strcmp (val->type->str, "STR")))
            return (RsvgFilter *) val;
    }
    return NULL;
}