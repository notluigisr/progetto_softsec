static int add_dirname_to_GList(struct dump_dir *dd, void *arg)
{
    GList **list = arg;
    *list = g_list_prepend(*list, xstrdup(dd->dd_dirname));
    return 0;
}