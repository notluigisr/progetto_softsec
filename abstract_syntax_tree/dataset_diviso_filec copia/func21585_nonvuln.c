lys_find_path(const struct lys_module *cur_module, const struct lys_node *cur_node, const char *path)
{
    struct ly_set *ret;
    int rc;

    if ((!cur_module && !cur_node) || !path) {
        return NULL;
    }

    rc = resolve_schema_nodeid(path, cur_node, cur_module, &ret, 1, 1);
    if (rc == -1) {
        return NULL;
    }

    return ret;
}